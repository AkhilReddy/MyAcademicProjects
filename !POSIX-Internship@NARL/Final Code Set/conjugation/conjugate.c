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

int main ()
{

double complex *p;
int i,n;

double complex in[3]={1.0 + 3.0*I,2.0 + 2.0*I,3.0 + 2.0*I};
double complex out[3];

p = conjugate(in,out,3);

for ( i = 0; i < 3; i++ )
{
printf( "*(p + %d) : %d\n", i, *(p + i));
}
return 0;
}
