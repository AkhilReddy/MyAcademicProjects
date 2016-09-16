

/* 
 * Computes the discrete Fourier transform (DFT) of the given complex vector, storing the result back into the vector.
 * The vector can have any length. This is a wrapper function. Returns 1 (true) if successful, 0 (false) otherwise (out of memory).
 */
int transform(float real[], float imag[], size_t n);

/* 
 * Computes the inverse discrete Fourier transform (IDFT) of the given complex vector, storing the result back into the vector.
 * The vector can have any length. This is a wrapper function. This transform does not perform scaling, so the inverse is not a true inverse.
 * Returns 1 (true) if successful, 0 (false) otherwise (out of memory).
 */
int inverse_transform(float real[], float imag[], size_t n);

/* 
 * Computes the discrete Fourier transform (DFT) of the given complex vector, storing the result back into the vector.
 * The vector's length must be a power of 2. Uses the Cooley-Tukey decimation-in-time radix-2 algorithm.
 * Returns 1 (true) if successful, 0 (false) otherwise (n is not a power of 2, or out of memory).
 */
int transform_radix2(float real[], float imag[], size_t n);

/* 
 * Computes the discrete Fourier transform (DFT) of the given complex vector, storing the result back into the vector.
 * The vector can have any length. This requires the convolution function, which in turn requires the radix-2 FFT function.
 * Uses Bluestein's chirp z-transform algorithm. Returns 1 (true) if successful, 0 (false) otherwise (out of memory).
 */
int transform_bluestein(float real[], float imag[], size_t n);

/* 
 * Computes the circular convolution of the given real vectors. Each vector's length must be the same.
 * Returns 1 (true) if successful, 0 (false) otherwise (out of memory).
 */
int convolve_real(const float x[], const float y[], float out[], size_t n);

/* 
 * Computes the circular convolution of the given complex vectors. Each vector's length must be the same.
 * Returns 1 (true) if successful, 0 (false) otherwise (out of memory).
 */
int convolve_complex(const float xreal[], const float ximag[], const float yreal[], const float yimag[], float outreal[], float outimag[], size_t n);

