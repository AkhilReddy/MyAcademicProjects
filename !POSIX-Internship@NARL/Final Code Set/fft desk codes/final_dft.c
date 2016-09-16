#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 
#define N 16
#define PI2 6.2832

float S1[N],S2[N];

float * DftR(float s[])
{
	int k,n;
    static float Xre[N];
    for (k=0 ; k<N ; ++k)
    {
        Xre[k] = 0;
        for (n=0 ; n<N ; ++n) // Calculating Real part of X[k]
        {
          Xre[k] += s[n] * cos(n * k * PI2 / N);
        }

	}
    return Xre;

}

float * DftI(float s[])
{
	int k,n;
    static float Xim[N];
	for(k=0;k<N;k++)
	{
		Xim[k] = 0;
        for (n=0 ; n<N ; ++n) // Calculating Imaginary part of X[k]
        {
          Xim[k] -= s[n] * sin(n * k * PI2 / N);
        }
        //P[k] = Xre[k]*Xre[k] + Xim[k]*Xim[k]; // final Power at kth frequency
    }

	return Xim;
}

float * random()
{
	int n;
    static float x[N];
    srand(time(0));
    for (n=0 ; n<N ; ++n) // Here We are just generating Random Data for x[n]
     {
     x[n] = ((2.0 * rand()) / RAND_MAX) - 1.0;
     }
     return x;
}
 
int main()
{
    int n, k;             
    float A[N],B[N];          
    float A1[N], A2[N],B1[N], B2[N];          

    A[N]=radom_func();
    B[N]=radom_func();

    A1[N] = dft_real(A[N]);
    A2[N] = dft_img(A[N]);

    B1[N] = dft_real(B[N]);
    B2[N] = dft_img(B[N]);
    
     for (k=0 ; k<N ; ++k)
    {

    S1[k] = ((A1[k]*B1[k] - A2[k]*B2[k])/((A1[k]^2+A2[k]^2)*(B1[k]^2+B2[k]^2)));

    }
    
     for (k=0 ; k<N ; ++k)
    {

    S2[k] = ((A1[k]*B2[k] + A2[k]*B1[k])/((A1[k]^2+A2[k]^2)*(B1[k]^2+B2[k]^2)));

    }

    FILE *f = fopen("dftplots.m", "w"); 
    fprintf(f, "n = [0:%d];\n", N-1);

    fprintf(f, "A = [ ");
    for (n=0 ; n<N ; ++n) 
     {
      fprintf(f, "%f ", A[n]);
     }
    fprintf(f, "];\n");


    
    fprintf(f, "B = [ ");
    for (n=0 ; n<N ; ++n) 
     {
      fprintf(f, "%f ", B[n]);
     }
    fprintf(f, "];\n");



    fprintf(f, "A1 = [ ");
    for (k=0 ; k<N ; ++k) 
     {
      fprintf(f, "%f ", A1[k]);
     }
    fprintf(f, "];\n");



    fprintf(f, "A2 = [ ");
    for (k=0 ; k<N ; ++k) 
     {
      fprintf(f, "%f ", A2[k]);
     }
    fprintf(f, "];\n");

    
    fprintf(f, "B1 = [ ");
    for (k=0 ; k<N ; ++k) 
     {
      fprintf(f, "%f ", B1[k]);
     }
    fprintf(f, "];\n");



    fprintf(f, "B2 = [ ");
    for (k=0 ; k<N ; ++k) 
     {
      fprintf(f, "%f ", B2[k]);
     }
    fprintf(f, "];\n");


    
     fprintf(f, "S1 = [ ");
    for (k=0 ; k<N ; ++k) 
     {
      fprintf(f, "%f ", S1[k]);
     }
    fprintf(f, "];\n");



    fprintf(f, "S2 = [ ");
    for (k=0 ; k<N ; ++k) 
     {
      fprintf(f, "%f ", S2[k]);
     }
    fprintf(f, "];\n");


    fprintf(f, "S = [ ");
    for (k=0 ; k<N ; ++k) 
     {
      fprintf(f, "%f +i %f", S1[k],S2[k]);
     }
    fprintf(f, "];\n");
    
    fprintf(f, "subplot(3,1,1)\nplot(n,x)\n");
    fprintf(f, "xlim([0 %d])\n", N-1);
    fprintf(f, "subplot(3,1,2)\nplot(n,Xre,n,Xim)\n");
    fprintf(f, "xlim([0 %d])\n", N-1);
    fprintf(f, "subplot(3,1,3)\nstem(n,P)\n");
    fprintf(f, "xlim([0 %d])\n", N-1);
    fclose(f);
     
    return 0;
}
    



