#include <assert.h>

#include "carray.h"
#include "complex_num.h"
#include "correlation.h"
#include "debug.h"
#include "fft2d.h"
#include "fftshift.h"
#include "find_scale_and_rotation.h"
#include "helpers.h"
#include "hipass_filter.h"
#include "intlog2.h"
#include "log_polar.h"

inline unsigned int compute_fft_size(Image *image_to_match, Image *template_image)
{
    return 1 << intlog2(MAX(
        MAX(image_to_match->height, image_to_match->width),
        MAX(template_image->height, template_image->width))
    );
}

/*
 * A function for finding the scale and rotation between 2 images.
 *
 */
void find_scale_and_rotation(Image *image_to_match, Image *template_image,
        CArray *fft_image, CArray *fft_template, MatchingResult *matching_result, char verbose)
{
    unsigned int scale, rotation, fft_size = compute_fft_size(image_to_match, template_image);
    double corrpeak;
    assert(fft_size > 0);

    carray_set_size(fft_image, fft_size, fft_size);
    carray_set_size(fft_template, fft_size, fft_size);
    fill_complex_image_and_template(image_to_match, fft_image, template_image, fft_template);

    /* Apply FFFT to both image and template */
    FFT2D(fft_image, 1);
    FFT2D(fft_template, 1);

    CArray *LOGA    = carray_alloc(fft_size, fft_size);
    CArray *LOGB    = carray_alloc(fft_size, fft_size);
    CArray *LOGCORR = carray_alloc(fft_size, fft_size);
    CArray *SA      = carray_alloc(fft_size, fft_size);
    CArray *SB      = carray_alloc(fft_size, fft_size);

    fftshift(fft_image, SA);
    fftshift(fft_template, SB);

    hipass_filter(SA);
    hipass_filter(SB);

    matching_result->image_fft = image_from_complex_abs(SA);
    matching_result->template_fft = image_from_complex_abs(SB);

    /* Translate spectra to polar coordinates */
    log_polar_transform(SA, LOGA);
    log_polar_transform(SB, LOGB);

    matching_result->image_logpolar = image_from_complex_abs(LOGA);
    matching_result->template_logpolar = image_from_complex_abs(LOGB);

    FFT2D(LOGA, 1);
    FFT2D(LOGB, 1);

    phcorr2d(LOGB, LOGA, LOGCORR);

    FFT2D(LOGCORR, -1);

    matching_result->log_polar_fft_correlation = image_from_complex_abs(LOGCORR);

    corrpeak = maxcorr2d(LOGCORR, fft_size-1, fft_size-1, &scale, &rotation);

    if (verbose >= VERBOSE_DEBUG)
    {
        fprintf(stderr, "ds=%d, dr=%d corrpeak=%f\n", scale, rotation, creal(carray_get(LOGCORR, scale, rotation)));
    }

    if (scale > fft_size / 2)
    {
        // Pattern has to be scaled down.
        scale = fft_size - scale + 1;
        matching_result->scale = 1.0 / exp(log(fft_size / 2) * scale) / (fft_size - 1);
    }
    else
    {
        // Pattern has to be scaled up.
        matching_result->scale = exp(log(fft_size / 2) * scale / (fft_size - 1));
    }

    if (matching_result->scale < SCALE_MIN || matching_result->scale > SCALE_MAX)
    {
      matching_result->scale = 1.0;
    }

    matching_result->rotation = (360 - (360 * rotation / fft_size));

    if (verbose >= VERBOSE_DEBUG)
    {
        fprintf(stderr, "ds=%d, dr=%d\n", scale, rotation);
        fprintf(stderr, "=> scale=%f, rotation=%f / %f \n",
                matching_result->scale, matching_result->rotation,
                180 + matching_result->rotation);
    }

    carray_free(LOGA);
    carray_free(LOGB);
    carray_free(LOGCORR);
    carray_free(SA);
    carray_free(SB);
}
