#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include <cufft.h>

#define SIZE        50
#define AKI_SIZE 11

typedef float2 Complex;
Complex ComplexAdd(Complex, Complex);
Complex ComplexScale(Complex, float);
Complex ComplexMul(Complex, Complex);
void ComplexPointwiseMulAndScale(Complex*, const Complex*, int, float);

void Convolve(const Complex*, int, const Complex*, int, Complex*);

int PadData(const Complex*, Complex**, int,const Complex*, Complex**, int);

void runTest(int argc, char** argv);

int main(int argc, char** argv)
{
    runTest(argc, argv);
}


void runTest(int argc, char** argv)
{
    Complex* h_signal = (Complex*)malloc(sizeof(Complex) * SIZE);
    for (unsigned int i = 0; i < SIZE; ++i) {
        h_signal[i].x = rand() / (float)RAND_MAX;
        h_signal[i].y = 0;
    }

    Complex* kernel = (Complex*)malloc(sizeof(Complex) * AKI_SIZE);
    for (unsigned int i = 0; i < AKI_SIZE; ++i) {
        kernel[i].x = rand() / (float)RAND_MAX;
        kernel[i].y = 0;
    }

    int mem_size = sizeof(Complex) * new_size;

    Complex* signal;
    cudaMalloc((void**)&signal, mem_size);
    
    cudaMemcpy(d_signal, h_padded_signal, mem_size,
               cudaMemcpyHostToDevice);


    cufftExecC2C(plan, (cufftComplex *)d_signal, (cufftComplex *)d_signal, CUFFT_FORWARD);
    cufftExecC2C(plan, (cufftComplex *)d_filter_kernel, (cufftComplex *)kernel, CUFFT_FORWARD);

    //Function  -- 2
    ComplexPointwiseMulAndScale<<<32, 256>>>(d_signal, kernel, new_size, 1.0f / new_size);

    cufftExecC2C(plan, (cufftComplex *)d_signal, (cufftComplex *)d_signal, CUFFT_INVERSE);

    Complex* h_convolved_signal = h_padded_signal;
    cudaMemcpy(h_convolved_signal, d_signal, mem_size,cudaMemcpyDeviceToHost);


    Complex* h_convolved_signal_ref = (Complex*)malloc(sizeof(Complex) * SIGNAL_SIZE);

   
	//Function -- 1
	 Convolve(h_signal, SIGNAL_SIZE,
             h_filter_kernel, FILTER_KERNEL_SIZE,
             h_convolved_signal_ref);

    cufftDestroy(plan);
    
    
    free(h_signal);
    free(h_filter_kernel);
    free(h_padded_signal);
    free(h_padded_filter_kernel);
    free(h_convolved_signal_ref);
    cudaFree(d_signal);
    cudaFree(d_filter_kernel);

}

void Convolve(const Complex* signal, int signal_size,const Complex* kernel, int kernel_size,Complex* f_signal)
{
    int minRadius = kernel_size / 2;
    int maxRadius = kernel_size - minRadius;
   
    for (int i = 0; i < signal_size; ++i) 
	 {
        f_signal[i].x = f_signal[i].y = 0;

        for (int j = - maxRadius + 1; j <= minRadius; ++j) 
		  {
            int k = i + j;
            if (k >= 0 && k < signal_size)
                f_signal[i] = ComplexAdd(f_signal[i], ComplexMul(signal[k], kernel[minRadius - j]));
        }
    }
}

Complex ComplexAdd(Complex a, Complex b)
{
    Complex c;
    c.x = a.x + b.x;
    c.y = a.y + b.y;
    return c;
}

Complex ComplexScale(Complex a, float s)
{
    Complex c;
    c.x = s * a.x;
    c.y = s * a.y;
    return c;
}

Complex ComplexMul(Complex a, Complex b)
{
    Complex c;
    c.x = a.x * b.x - a.y * b.y;
    c.y = a.x * b.y + a.y * b.x;
    return c;
}

void ComplexPointwiseMulAndScale(Complex* a, const Complex* b, int size, float scale)
{
    const int numThreads = blockDim.x * gridDim.x;
    const int threadID = blockIdx.x * blockDim.x + threadIdx.x;
    for (int i = threadID; i < size; i += numThreads)
        a[i] = ComplexScale(ComplexMul(a[i], b[i]), scale);
}
