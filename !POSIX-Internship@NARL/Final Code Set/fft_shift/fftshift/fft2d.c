#include <fftw3.h>

#include "die.h"
#include "fft2d.h"

void *fftw_xmalloc(size_t size)
{
    if (!size)
        die("Tried to allocate zero bytes");

    void *ret = fftw_malloc(size);

    if (!ret)
        die("Could not allocate memory");

    return ret;
}

/*
 * Perform in-place 2D FFT.
 */
void FFT2D(CArray *arr, int direction)
{
    #ifndef NO_FFTW_COMPLEX
        fftw_plan p;
        p = fftw_plan_dft_2d(arr->rows, arr->cols, (fftw_complex *)arr->data, (fftw_complex *)arr->data,
                ((direction == -1) ? FFTW_BACKWARD : FFTW_FORWARD), FFTW_ESTIMATE);
        fftw_execute(p);
        fftw_destroy_plan(p);
    #else
        fftw_complex *in, *out;
        fftw_plan p;
        unsigned int i, j;

        in = (fftw_complex*) fftw_xmalloc(sizeof(fftw_complex) * arr->rows * arr->cols);
        out = (fftw_complex*) fftw_xmalloc(sizeof(fftw_complex) * arr->rows * arr->cols);
        for (i = 0; i < arr->rows; ++i)
        {
            for (j = 0; j < arr->cols; ++j)
            {
                in[n * i + j][0] = creal(carray_get(arr, i, j));
                in[n * i + j][1] = cimag(carray_get(arr, i, j));
            }
        }
        p = fftw_plan_dft_2d(n, m, in, out,
                ((direction == -1) ? FFTW_BACKWARD : FFTW_FORWARD), FFTW_ESTIMATE);
        fftw_execute(p);
        fftw_destroy_plan(p);

        for (i = 0; i < arr->rows; ++i)
        {
            for (j = 0; j < arr->cols; ++j)
            {
                creal_set(carray_get(arr, i, j), out[n * i + j][0]);
                cimag_set(carray_get(arr, i, j), out[n * i + j][1]);
                if (direction == -1)
                {
                    creal_set(carray_get(arr, i, j), creal(carray_get(arr, i, j)) / arr->rows * arr->cols);
                    cimag_set(carray_get(arr, i, j), cimag(carray_get(arr, i, j)) / arr->rows * arr->cols);
                }
            }
        }
        fftw_free(in);
        fftw_free(out);
    #endif
}
