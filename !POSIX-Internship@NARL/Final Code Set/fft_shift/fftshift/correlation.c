#include <assert.h>
#include <fftw3.h>
#include <math.h>

#include "correlation.h"

/*
 * Computes the phase-correlation of two images using FFT.
 *
 * INPUT:
 *  `a` and `b`: the images to correlate. They must be the same size.
 *  `c`: where to put the result
 *  `h` and `w`: the dimensions of `a`, `b`, and `c`
 *  The dimensions could be less than the smallest dimension for partial processing.
 *
 * RETURN VALUE:
 *  None.
 *
 * OUTPUT:
 *  Saved in `c`
 *
 * SIDE EFFECTS:
 *  Saves the result of the correlation in `c`
 */
inline void phcorr2d(CArray *a, CArray *b, CArray *c)
{
    unsigned int i, j;
    double normfactor;
    assert((a->rows == b->rows) && (b->rows == c->rows));
    assert((a->cols == b->cols) && (b->cols == c->cols));

    /* Multiply F(a) by the complex conjugate of F(b)
     * as per the Cross-Correlation theorem:
     * https://ccrma.stanford.edu/~jos/log/Correlation_Theorem.html
     * http://en.wikipedia.org/wiki/Fourier_transform#Cross-correlation_theorem
     * Divide by |F(a)F(b)| to get phase correlation as defined in
     * http://iopscience.iop.org/0004-637X/706/2/1605/fulltext/
     * */
    for(i = 0; i < a->rows; ++i)
    {
        for(j = 0; j < a->cols; ++j)
        {
            creal_set(carray_get(c, i, j), creal(carray_get(a, i, j)) * creal(carray_get(b, i, j)) + cimag(carray_get(a, i, j)) * cimag(carray_get(b, i, j)));
            cimag_set(carray_get(c, i, j), cimag(carray_get(a, i, j)) * creal(carray_get(b, i, j)) - cimag(carray_get(b, i, j)) * creal(carray_get(a, i, j)));

            normfactor = sqrt(creal(carray_get(c, i, j)) * creal(carray_get(c, i, j)) + cimag(carray_get(c, i, j)) * cimag(carray_get(c, i, j))) + EPSILON;

            creal_set(carray_get(c, i, j), creal(carray_get(c, i, j)) / normfactor);
            cimag_set(carray_get(c, i, j), cimag(carray_get(c, i, j)) / normfactor);

            assert(creal(carray_get(a, i, j)) == creal(carray_get(a, i, j)));
            assert(creal(carray_get(c, i, j)) == creal(carray_get(c, i, j)));
        }
    }
}

inline void corr2d(CArray *a, CArray *b, CArray *c)
{
    unsigned int i, j;
    assert((a->rows == b->rows) && (b->rows == c->rows));
    assert((a->cols == b->cols) && (b->cols == c->cols));

    /* Multiply F(a) by the complex conjugate of F(b)
     * as per the Cross-Correlation theorem:
     * https://ccrma.stanford.edu/~jos/log/Correlation_Theorem.html
     * http://en.wikipedia.org/wiki/Fourier_transform#Cross-correlation_theorem
     * Divide by |F(a)F(b)| to get phase correlation as defined in
     * http://iopscience.iop.org/0004-637X/706/2/1605/fulltext/
     * */
    for(i = 0; i < a->rows; ++i)
    {
        for(j = 0; j < a->cols; ++j)
        {
            creal_set(carray_get(c, i, j), creal(carray_get(a, i, j)) * creal(carray_get(b, i, j)) + cimag(carray_get(a, i, j)) * cimag(carray_get(b, i, j)));
            cimag_set(carray_get(c, i, j), cimag(carray_get(a, i, j)) * creal(carray_get(b, i, j)) - cimag(carray_get(b, i, j)) * creal(carray_get(a, i, j)));
        }
    }
}

inline double maxcorr2d(CArray *c,
        unsigned int max_shift_h, unsigned int max_shift_w,
        unsigned int *x, unsigned int *y)
{
    unsigned int n, m, maxcor2x, maxcor2y;
    double maxcor2 = 0.0;
    double cor2;

    assert(max_shift_h < c->rows);
    assert(max_shift_w < c->cols);

    maxcor2x = maxcor2y = 0;
    for(n = 0; n <= max_shift_h; ++n)
    {
        #if DEBUG_CORR2D
        printf("[%d] ", n);
        #endif
        for(m = 0; m <= max_shift_w; ++m)
        {
            #if DEBUG_CORR2D
            printf("%f ", creal(carray_get(c, n, m)));
            #endif
            if ((cor2 = creal(carray_get(c, n, m))) > maxcor2)
            {
                maxcor2x = n;
                maxcor2y = m;
                maxcor2 = cor2;
            }
        }
        #if DEBUG_CORR2D
        printf("\n");
        #endif
    }

    if (x != NULL)
    {
        *x = maxcor2x;
    }
    if (y != NULL)
    {
        *y = maxcor2y;
    }

    return maxcor2;
}
