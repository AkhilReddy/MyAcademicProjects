#include "fftshift.h"

void fftshift(CArray *in, CArray *out)
{
    unsigned int i, j, ii, jj, xshift, yshift;
    xshift = in->rows / 2;
    yshift = in->cols / 2;

    for (i = 0; i < in->rows; i++) {
        ii = (i + xshift) % in->rows;
        for (j = 0; j < in->cols; j++) {
            jj = (j + yshift) % in->cols;
            creal_set(carray_get(out, ii, jj), creal(carray_get(in, i, j)));
            cimag_set(carray_get(out, ii, jj), cimag(carray_get(in, i, j)));
        }
    }
}
