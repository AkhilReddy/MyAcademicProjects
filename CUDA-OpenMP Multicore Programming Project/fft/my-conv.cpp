#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include <cufft.h>

#define SIGNAL_SIZE        50
#define FILTER_KERNEL_SIZE 11

typedef float2 Complex;
Complex ComplexAdd(Complex, Complex);
Complex ComplexScale(Complex, float);
Complex ComplexMul(Complex, Complex);
void ComplexPointwiseMulAndScale(Complex*, const Complex*, int, float);

void Convolve(const Complex*, int, const Complex*, int, Complex*);           // Filtering functions

int PadData(const Complex*, Complex**, int,const Complex*, Complex**, int);  // Padding functions

void runTest(int argc, char** argv);

int main(int argc, char** argv)
{
    runTest(argc, argv );
}

/*
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

    
    ComplexPointwiseMulAndScale<<<32, 256>>>(d_signal, kernel, new_size, 1.0f / new_size);

    cufftExecC2C(plan, (cufftComplex *)d_signal, (cufftComplex *)d_signal, CUFFT_INVERSE);

    Complex* h_convolved_signal = h_padded_signal;
    cudaMemcpy(h_convolved_signal, d_signal, mem_size,cudaMemcpyDeviceToHost);


    Complex* h_convolved_signal_ref = (Complex*)malloc(sizeof(Complex) * SIGNAL_SIZE);

   

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

*/

void runTest(int argc, char** argv)
{
    printf("Program is starting...\n");

    Complex* h_signal = (Complex*)malloc(sizeof(Complex) * SIGNAL_SIZE);                     //  Here We are allocating host memory for the signal
    for (unsigned int i = 0; i < SIGNAL_SIZE; ++i)                                           // Initalize the memory for the signal
	 {
        h_signal[i].x = rand() / (float)RAND_MAX;
        h_signal[i].y = 0;
    }

    Complex* h_filter_kernel = (Complex*)malloc(sizeof(Complex) * FILTER_KERNEL_SIZE);      // Allocate host memory for the filter
    
    for (unsigned int i = 0; i < FILTER_KERNEL_SIZE; ++i)                                  // Initalize the memory for the filter
	 {
        h_filter_kernel[i].x = rand() / (float)RAND_MAX;
        h_filter_kernel[i].y = 0;
    }

    Complex* h_padded_signal;                                                              // Pad signal and filter kernel
    Complex* h_padded_filter_kernel;
    int new_size = PadData(h_signal, &h_padded_signal, SIGNAL_SIZE,h_filter_kernel, &h_padded_filter_kernel, FILTER_KERNEL_SIZE);
    int mem_size = sizeof(Complex) * new_size;

   
    Complex* d_signal;                                                                     // Allocate device memory for signal
    cudaMalloc((void**)&d_signal, mem_size);                                              
   
    cudaMemcpy(d_signal, h_padded_signal, mem_size,cudaMemcpyHostToDevice);                // Copy host memory to device

   
    Complex* d_filter_kernel;
    cudaMalloc((void**)&d_filter_kernel, mem_size);                                         // Allocate device memory for filter kernel

   
    cudaMemcpy(d_filter_kernel, h_padded_filter_kernel, mem_size,cudaMemcpyHostToDevice);    // Copy host memory to device

    
    cufftHandle plan;
    cufftPlan1d(&plan, new_size, CUFFT_C2C, 1);                                                  // CUFFT plan

   
                             /* From Here on wording We are Transforming signal and kernel */   
   
    
    printf("Transforming signal cufftExecC2C\n"); 
	                                           
    cufftExecC2C(plan, (cufftComplex *)d_signal, (cufftComplex *)d_signal, CUFFT_FORWARD);
    cufftExecC2C(plan, (cufftComplex *)d_filter_kernel, (cufftComplex *)d_filter_kernel, CUFFT_FORWARD);

    
    printf("Launching ComplexPointwiseMulAndScale<<< >>>\n");
	                                                                                  
	 //Function  -- 2
    ComplexPointwiseMulAndScale<<<32, 256>>>(d_signal, d_filter_kernel, new_size, 1.0f / new_size);  // Multiply the coefficients together and normalize the result

    printf("Transforming signal back cufftExecC2C\n");                                               // Transform signal back
    cufftExecC2C(plan, (cufftComplex *)d_signal, (cufftComplex *)d_signal, CUFFT_INVERSE);
    
                              
										
										                                                                       // Transform signal back
    Complex* h_convolved_signal = h_padded_signal;
    cudaMemcpy(h_convolved_signal, d_signal, mem_size,cudaMemcpyDeviceToHost);

 
    Complex* h_convolved_signal_ref = (Complex*)malloc(sizeof(Complex) * SIGNAL_SIZE);                // Allocate host memory for the convolution result

    //Function -- 1
    Convolve(h_signal, SIGNAL_SIZE,h_filter_kernel, FILTER_KERNEL_SIZE,h_convolved_signal_ref);        // Convolve on the host

    
    cufftDestroy(plan);                                                                                  //Destroy CUFFT from Mem
                                                                                                         // cleanup memory

    
    free(h_signal);
    free(h_filter_kernel);
    free(h_padded_signal);
    free(h_padded_filter_kernel);
    free(h_convolved_signal_ref);
    cudaFree(d_signal);
    cudaFree(d_filter_kernel);

}

// Pad data
int PadData(const Complex* signal, Complex** padded_signal, int signal_size,const Complex* filter_kernel, Complex** padded_filter_kernel, int filter_kernel_size)
{
    int minRadius = filter_kernel_size / 2;
    int maxRadius = filter_kernel_size - minRadius;
    int new_size = signal_size + maxRadius;

    // Pad signal
    Complex* new_data = (Complex*)malloc(sizeof(Complex) * new_size);
    memcpy(new_data + 0, signal,signal_size * sizeof(Complex));
    memset(new_data + signal_size,0, (new_size - signal_size) * sizeof(Complex));
    *padded_signal = new_data;

    // Pad filter
    new_data = (Complex*)malloc(sizeof(Complex) * new_size);
    memcpy(new_data +0, filter_kernel + minRadius,maxRadius * sizeof(Complex));
    memset(new_data + maxRadius,0, (new_size - filter_kernel_size) * sizeof(Complex));
    memcpy(new_data + new_size - minRadius,filter_kernel,minRadius * sizeof(Complex));
    *padded_filter_kernel = new_data;

    return new_size;
}

void Convolve(const Complex* signal, int signal_size,const Complex* filter_kernel, int filter_kernel_size,Complex* filtered_signal)
{
    int minRadius = filter_kernel_size / 2;
    int maxRadius = filter_kernel_size - minRadius;
                                                                         // Loop over output element indices
    for (int i = 0; i < signal_size; ++i) 
	 {
        filtered_signal[i].x = filtered_signal[i].y = 0;
                                                                        // Loop over convolution indices
        for (int j = - maxRadius + 1; j <= minRadius; ++j) 
		  {
            int k = i + j;
            if (k >= 0 && k < signal_size)
                filtered_signal[i] = ComplexAdd(filtered_signal[i], ComplexMul(signal[k], filter_kernel[minRadius - j]));
        }
    }
}

Complex ComplexAdd(Complex a, Complex b)      // Complex addition
{
    Complex c;
    c.x = a.x + b.x;
    c.y = a.y + b.y;
    return c;
}

Complex ComplexScale(Complex a, float s)  // Complex scale
{
    Complex c;
    c.x = s * a.x;
    c.y = s * a.y;
    return c;
}

Complex ComplexMul(Complex a, Complex b)    // Complex multiplication
{
    Complex c;
    c.x = a.x * b.x - a.y * b.y;
    c.y = a.x * b.y + a.y * b.x;
    return c;
}

void ComplexPointwiseMulAndScale(Complex* a, const Complex* b, int size, float scale)   // Complex pointwise multiplication
{
    const int numThreads = blockDim.x * gridDim.x;
    const int threadID = blockIdx.x * blockDim.x + threadIdx.x;
    for (int i = threadID; i < size; i += numThreads)
        a[i] = ComplexScale(ComplexMul(a[i], b[i]), scale);
}
