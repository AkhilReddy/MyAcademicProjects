#ifndef CORRELATION_H
#define CORRELATION_H

#include "carray.h"

#define DEBUG_CORR2D 0
#define EPSILON 0.02

inline void corr2d(CArray *a, CArray *b, CArray *c);
inline void phcorr2d(CArray *a, CArray *b, CArray *c);
inline double maxcorr2d(CArray *c,
        unsigned int max_shift_h, unsigned int max_shift_w,
        unsigned int *x, unsigned int *y);

#endif
