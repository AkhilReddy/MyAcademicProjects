#include "intlog2.h"

/*
 * Returns power of 2 closest to `n`.
 */
unsigned int intlog2(unsigned int n)
{
    unsigned int p2 = 0;
    while (n >>= 1) {
        p2 += 1;
    }
    return p2;
}
