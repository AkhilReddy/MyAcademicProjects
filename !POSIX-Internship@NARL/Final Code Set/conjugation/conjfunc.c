#include <stdio.h>
#include <complex.h>

 
double complex *conjugate(double complex *in,double complex *out,int n)
{
int i;

for(i=0;i<n;i++)
{

double complex z = in[i];
double complex z2 = conj(z);

out[i] = z2;

}

return out;

}
