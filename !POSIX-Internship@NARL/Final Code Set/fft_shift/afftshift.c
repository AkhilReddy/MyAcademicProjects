#include <stdio.h>
#include <complex.h>

int n;         // FFT output vector length
int n2;
int i;
complex x[n];  // you might typedef your own complex type
complex tmp;

n2 = n / 2;    // half of vector length
  
for (i = 0; i < n2; i++)
{
     tmp     = x[i];
     x[i]    = x[i+n2];
     x[i+n2] = tmp;
}
