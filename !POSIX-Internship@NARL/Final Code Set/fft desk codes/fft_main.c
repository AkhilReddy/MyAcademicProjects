#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define PI	M_PI	
#define TWOPI	(2.0*PI)

void four1(double data[], int nn, int isign)
{
    int n, mmax, m, j, istep, i;
    double wtemp, wr, wpr, wpi, wi, theta;
    double tempr, tempi;
    
    n = nn << 1;
    j = 1;
    for (i = 1; i < n; i += 2) {
	if (j > i) {
	    tempr = data[j];     data[j] = data[i];     data[i] = tempr;
	    tempr = data[j+1]; data[j+1] = data[i+1]; data[i+1] = tempr;
	}
	m = n >> 1;
	while (m >= 2 && j > m) {
	    j -= m;
	    m >>= 1;
	}
	j += m;
    }
    mmax = 2;
    while (n > mmax) {
	istep = 2*mmax;
	theta = TWOPI/(isign*mmax);
	wtemp = sin(0.5*theta);
	wpr = -2.0*wtemp*wtemp;
	wpi = sin(theta);
	wr = 1.0;
	wi = 0.0;
	for (m = 1; m < mmax; m += 2) {
	    for (i = m; i <= n; i += istep) {
		j =i + mmax;
		tempr = wr*data[j]   - wi*data[j+1];
		tempi = wr*data[j+1] + wi*data[j];
		data[j]   = data[i]   - tempr;
		data[j+1] = data[i+1] - tempi;
		data[i] += tempr;
		data[i+1] += tempi;
	    }
	    wr = (wtemp = wr)*wpr - wi*wpi + wr;
	    wi = wi*wpr + wtemp*wpi + wi;
	}
	mmax = istep;
    }
}


int main(int argc, char * argv[])
{
	int i;
	int Nx;
	int NFFT;
	double *x;
	double *X;

	/* generate a ramp with 10 numbers */
	Nx = 10;
	printf("Nx = %d\n", Nx);
	x = (double *) malloc(Nx * sizeof(double));
	for(i=0; i<Nx; i++)
	{
		x[i] = i;
	}

	/* calculate NFFT as the next higher power of 2 >= Nx */
	NFFT = (int)pow(2.0, ceil(log((double)Nx)/log(2.0)));
	printf("NFFT = %d\n", NFFT);

	/* allocate memory for NFFT complex numbers (note the +1) */
	X = (double *) malloc((2*NFFT+1) * sizeof(double));

	/* Storing x(n) in a complex array to make it work with four1. 
	This is needed even though x(n) is purely real in this case. */
	for(i=0; i<Nx; i++)
	{
		X[2*i+1] = x[i];
		X[2*i+2] = 0.0;
	}
	/* pad the remainder of the array with zeros (0 + 0 j) */
	for(i=Nx; i<NFFT; i++)
	{
		X[2*i+1] = 0.0;
		X[2*i+2] = 0.0;
	}

	printf("\nInput complex sequence (padded to next highest power of 2):\n");
	for(i=0; i<NFFT; i++)
	{
		printf("x[%d] = (%.2f + j %.2f)\n", i, X[2*i+1], X[2*i+2]);
	}

	/* calculate FFT */
	four1(X, NFFT, 1);

	printf("\nFFT:\n");
	for(i=0; i<NFFT; i++)
	{
		printf("X[%d] = (%.2f + j %.2f)\n", i, X[2*i+1], X[2*i+2]);
	}

	/* calculate IFFT */
	four1(X, NFFT, -1);

	/* normalize the IFFT */
	for(i=0; i<NFFT; i++)
	{
		X[2*i+1] /= NFFT;
		X[2*i+2] /= NFFT;
	}

	printf("\nComplex sequence reconstructed by IFFT:\n");
	for(i=0; i<NFFT; i++)
	{
		printf("x[%d] = (%.2f + j %.2f)\n", i, X[2*i+1], X[2*i+2]);
	}

	getchar();
}

