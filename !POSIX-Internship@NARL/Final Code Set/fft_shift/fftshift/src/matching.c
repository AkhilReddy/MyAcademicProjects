#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "consts.h"
#include "correlation.h"
#include "fft2d.h"
#include "find_scale_and_rotation.h"
#include "hipass_filter.h"
#include "image.h"
#include "intermediate_event.h"
#include "intlog2.h"
#include "log_polar.h"
#include "matching.h"
#include "matching_result.h"

inline void load_image_to_match(char const * image_path, Image **image_to_match, char verbose, IECallback *callback)
{
    if (verbose >= VERBOSE_DEBUG)
    {
        fprintf(stderr, "  * Matching image %s\n", image_path);
    }
    assert(load_image_greyscale(image_path, image_to_match) == 0);
    assert((*image_to_match)->height == (*image_to_match)->width);
    if (callback)
    {
        send_event(IE_IMAGE_LOADED, *image_to_match, NULL, callback, NULL);
    }
}

inline void load_template(char const * template_path, Image **template_image, char verbose, IECallback *callback)
{
    if (verbose >= VERBOSE_DEBUG)
    {
        fprintf(stderr, "\n  > Template %s\n", template_path);
    }
    /* Load the template image */
    assert(load_image_greyscale(template_path, template_image) == 0);
    if (callback)
    {
        send_event(IE_TEMPLATE_LOADED, NULL, *template_image, callback, NULL);
    }
}

/*
 * Match an image at `image_path` with templates at `template_paths`.
 * `n_templates` must be equal to the number of templates in `template_paths`.
 */
unsigned int match_image(char const * image_path, const char ** template_paths,
        unsigned int n_templates, char verbose, IECallback *callback)
{
    CArray *fft_image    = carray_alloc(MAXDIM, MAXDIM);
    CArray *fft_template = carray_alloc(MAXDIM, MAXDIM);
    CArray *correlation  = carray_alloc(MAXDIM, MAXDIM);

    Image *image_to_match = NULL,
          *template_image = NULL,
          *template_scaled = NULL,
          *template_rotated = NULL;

    MatchingResult *best_match = matching_result_alloc();
    MatchingResult *current_match = matching_result_alloc();
    MatchingResult *tmp_match;

    unsigned int ti, fft_size, roti;

    load_image_to_match(image_path, &image_to_match, verbose, callback);

    /* For each template */
    for (ti = 0; ti < n_templates; ++ti)
    {
        /* Assume current match is best */
        current_match->template_index = ti;
        load_template(template_paths[ti], &template_image, verbose, callback);

        /* Find scale and rotation */
        find_scale_and_rotation(
            image_to_match,
            template_image,
            fft_image,
            fft_template,
            current_match, /* OUT */
            verbose);

        /* Scale template */
        template_scaled = malloc_image(
            ceil(current_match->scale * template_image->height), /* height */
            ceil(current_match->scale * template_image->width) /* width */
            );
        scale_image(
            template_image,
            template_scaled, /* OUT */
            current_match->scale,
            verbose);

        /* Try both `rotation` and `180 + rotation` */
        /* XXX: refactor ridiculous loop */
        for (roti = 0; roti < 2; ++roti)
        {
            current_match->rotation = ((roti == 0) ? current_match->rotation : current_match->rotation + 180);
            current_match->rotation = current_match->rotation > 360 ? current_match->rotation - 360 : current_match->rotation;

            fft_size = MAX(
                MAX(template_scaled->height, template_scaled->width),
                MAX(image_to_match->width, image_to_match->height)
            );

            carray_set_size(correlation, fft_size, fft_size);
            carray_set_size(fft_image, fft_size, fft_size);
            carray_set_size(fft_template, fft_size, fft_size);

            if (current_match->rotation > ROT_EPS)
            {
                /* Rotate the already scaled template */
                template_rotated = malloc_image(
                    template_scaled->height,
                    template_scaled->width
                );
                rotate_image(
                    template_scaled,
                    template_rotated, /* OUT */
                    current_match->rotation,
                    verbose);

                /* Populate COMPLEX arrays with the image data for FFT input */
                fill_complex_image_and_template(
                    image_to_match,
                    fft_image,
                    template_rotated,
                    fft_template);
            }
            else
            {
                ++roti; /* Skip second iteration */
                fill_complex_image_and_template(
                    image_to_match,
                    fft_image, /* OUT */
                    template_scaled,
                    fft_template); /* OUT */
            }

            /* Forward FFT the padded image and the template */
            FFT2D(fft_image, 1);
            FFT2D(fft_template, 1);

            /* Compute phase-correlation */
            phcorr2d(
                fft_image,
                fft_template,
                correlation); /* OUT */

            /* Inverse transform correlation */
            FFT2D(correlation, -1);

            current_match->max_correlation = maxcorr2d(
                correlation,
                fft_size-1,
                fft_size-1,
                &current_match->shift_x, /* OUT */
                &current_match->shift_y /* OUT */
            );

            if (verbose >= VERBOSE_DEBUG)
            {
                fprintf(stderr,
                    "correlation peak @(%d, %d)=%f\n",
                    current_match->shift_x,
                    current_match->shift_y,
                    current_match->max_correlation
                );
            }

            /* Global max */
            if (current_match->max_correlation > best_match->max_correlation)
            {
                tmp_match = best_match;
                best_match = current_match;
                current_match = tmp_match;
            }
            free_image(template_scaled);
        }
        free_image(template_image);
    }

    #if 0
    if (callback)
    {
        fprintf(stderr, "best_match scale @ %08lx: %f\n", (unsigned long int)&best_match, best_match->scale);
        send_event(IE_BEST_MATCH, NULL, tmaximage, callback, (void*)&best_match);
        send_event(IE_LOG_POLAR1, tmaximage_logpolar, NULL, callback, (void*)&best_match);
        send_event(IE_LOG_POLAR2, NULL, tmaxtemplate_logpolar, callback, (void*)&best_match);
        send_event(IE_FFT1, tmaxfft1, NULL, callback, (void*)&best_match);
        send_event(IE_FFT2, NULL, tmaxfft2, callback, (void*)&best_match);
        send_event(IE_CORR, maxlog_polar_fft_correlationimg, NULL, callback, (void*)&best_match);
    }
    #endif

    if (verbose >= VERBOSE_DEBUG)
    {
        fprintf(stderr, "max correlation: %f\n", best_match->max_correlation);
    }

    if (best_match->template_index != (unsigned int)-1)
    {
        fprintf(stdout, "%s => %s\n", image_path, template_paths[best_match->template_index]);
    }
    else
    {
        fprintf(stderr, "Error: no match\n");
    }
    ti = best_match->template_index;
    free(best_match);
    free(current_match);

    carray_free(fft_image);
    carray_free(fft_template);
    carray_free(correlation);

    free_image(image_to_match);

    return ti;
}
