#ifndef COMPLEX_NUM_H
#define COMPLEX_NUM_H

#include <math.h>
#ifdef NO_FFTW_COMPLEX
    #define creal(c) (c).real
    #define cimag(c) (c).imag
    #define creal_set(c, v) (c).real = v
    #define cimag_set(c, v) (c).imag = v
#else
    #include <fftw3.h>
    #define creal(c) (c)[0]
    #define cimag(c) (c)[1]
    #define creal_set(c, v) (c)[0] = v
    #define cimag_set(c, v) (c)[1] = v
#endif

#define cabs(c) (sqrt(creal(c) * creal(c) + cimag(c) * cimag(c)))

#ifdef NO_FFTW_COMPLEX
    typedef struct {
        double real;
        double imag;
    } COMPLEX;
#else
    typedef fftw_complex COMPLEX;
#endif

#endif
