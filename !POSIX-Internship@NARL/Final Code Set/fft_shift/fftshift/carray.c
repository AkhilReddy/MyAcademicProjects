#include <assert.h>
#include <stdlib.h>

#include "carray.h"
#include "xmalloc.h"

CArray* carray_alloc(unsigned int rows, unsigned int cols)
{
    CArray *arr = xmalloc(sizeof(CArray));
    arr->data = xmalloc(sizeof(COMPLEX) * rows * cols);
    arr->rows = arr->row_cap = rows;
    arr->cols = arr->col_cap = cols;
    return arr;
}

void carray_free(CArray *arr)
{
    free(arr->data);
    free(arr);
}

void carray_set_size(CArray *arr, unsigned int rows, unsigned int cols)
{
    assert(rows <= arr->row_cap);
    assert(cols <= arr->col_cap);
    arr->rows = rows;
    arr->cols = cols;
}

void carray_fill(CArray *arr, double real, double imag)
{
    unsigned int i, j;
    for(i = 0; i < arr->rows; ++i)
    {
        for(j = 0; j < arr->cols; ++j)
        {
            creal_set(carray_get(arr, i, j), real);
            cimag_set(carray_get(arr, i, j), imag);
        }
    }
}
