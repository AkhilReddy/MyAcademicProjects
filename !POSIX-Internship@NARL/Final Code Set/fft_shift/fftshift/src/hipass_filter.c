#include <math.h>

#include "hipass_filter.h"

/*
 * Apply a high-pass filter.
 *
 */
void hipass_filter(CArray *a)
{
    unsigned int i, j;
    double f, eta, neta, res_ht, res_wd;

    res_ht = 1.0 / (a->rows - 1);
    res_wd = 1.0 / (a->cols - 1);

    for (i = 0; i < a->rows; ++i)
    {
        neta = cos(M_PI * (-0.5 + res_ht * i));

        for (j = 0; j < a->cols; ++j)
        {
            eta = cos(M_PI * (-0.5 + res_wd * j));
            f = (1.0 - eta*neta) * (2.0 - eta*neta);
            creal_set(carray_get(a, i, j), cabs(carray_get(a, i, j)) * f);
            cimag_set(carray_get(a, i, j), 0);
        }
    }
}
