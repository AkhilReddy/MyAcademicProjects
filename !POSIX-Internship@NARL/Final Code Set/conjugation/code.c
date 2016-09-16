#include <stdio.h>
#include <complex.h>

#include "header2.h"

int main ()
{

double complex *p;
int i,n;

double complex in[3]={1.0 + 3.0*I,2.0 + 2.0*I,3.0 + 2.0*I};
double complex out[3];

p = conjugate(in,out,3);

for ( i = 0; i < 3; i++ )
{

printf("The conjugate of *(p + %d) : %.1f%+.1fi is %.1f%+.1fi\n",
            i,creal(in[i]), cimag(in[i]), creal(*(p + i)), cimag(*(p + i)));
}
return 0;
}
