#ifndef FFT2D_H
#define FFT2D_H

#include "image.h"
#include "carray.h"

void FFT2D(CArray *arr, int direction);
void *fftw_xmalloc(size_t size);

#endif
