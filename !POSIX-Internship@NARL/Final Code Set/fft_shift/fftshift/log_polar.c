#include <assert.h>
#include <math.h>
#include <stdio.h>

#include "image.h"
#include "log_polar.h"

/*
 * Transform the COMPLEX matrix `in` to log-polar coordinates and write the
 * result in `out`.
 * Uses nearest neighbour.
 */
void log_polar_transform(CArray *in, CArray *out)
{
    unsigned int N = in->rows;
#if 1
    assert(N > 1);

    unsigned i, j, xx, yy;
    double maxsc, theta, theta_step, rho;

    theta_step = 2 * M_PI / (N - 1);
    maxsc = log10(N / 2.0);

#if DEBUG_POLAR
    Image *samples = malloc_image(N, N);
    for (i = 0; i < N; ++i)
    {
        for (j = 0; j < N; ++j)
        {
            samples->data[i][j] = 255.0;
        }
    }
#endif

    for (i = 0; i < N; ++i)
    {
        rho = pow(10.0, i * maxsc/(N - 1));
        for(j = 0; j < N; ++j)
        {
            theta = j*theta_step;
            xx = lround(rho*sin(theta) + N / 2);
            yy = lround(rho*cos(theta) + N / 2);

            if (xx < N && yy < N)
            {
#if DEBUG_POLAR
                samples->data[xx][yy] = 0.0;
#endif
                creal_set(carray_get(out, i, j), creal(carray_get(in, xx, yy)));
                cimag_set(carray_get(out, i, j), cimag(carray_get(in, xx, yy)));
            } else {
                creal_set(carray_get(out, i, j), 0.0);
                cimag_set(carray_get(out, i, j), 0.0);
            }
        }
    }
#if DEBUG_POLAR
            write_image("LOG_SAMPLING.bmp", samples);
#endif
#endif

#if 0
    unsigned x, y, xx, yy;
    double r;
    double maxr = log(1.0*N/2);
    double theta = 0.0;
    double theta_delta = 2*M_PI / (N -1);

#if DEBUG_POLAR
    Image *samples = malloc_image(N, N);
#endif

    for(x=0; x<N; ++x)
    {
        r = x * maxr/N;
        for(y=0; y<N; ++y)
        {
            theta = y * theta_delta;
            xx = N/2 + lround(exp(r) * cos(theta));
            yy = N/2 + lround(exp(r) * sin(theta));
            if(xx>=0 && xx<N && yy>=0 && yy<N)
            {
                creal_set(out[x][y], creal(in[xx][yy]));
                cimag_set(out[x][y], cimag(in[xx][yy]));
#if DEBUG_POLAR
                samples->data[xx][yy] = 255.0;
#endif
            }
            else
            {
                creal_set(out[x][y], 0.0);
                cimag_set(out[x][y], 0.0);
            }
        }
    }
#if DEBUG_POLAR
            write_image("LOG_SAMPLING.bmp", samples->data, samples->height, samples->width);
#endif
#endif


#if 0
    unsigned int u, v;
    double radius, tita, x, y;
    double twopi = 2 * M_PI;
    COMPLEX *sample;
    assert(N > 0);
    assert(in != out);

    #if DEBUG_POLAR
    unsigned char ** X = malloc_2d_chars(N, N);
    for(u=0; u<N; ++u)
    {
        for(v=0; v<N; ++v)
        {
            X[u][v] = 0;
        }
    }
    #endif

    for(u=0; u<N; ++u)
    {
        /*
         * Logarithmic scale for the radius.
         */
        radius = pow(N/2, (1.0*u/(N-1)));
        for(v=0; v<N; ++v)
        {
            tita = twopi * v / N;

            x = N/2.0 + radius * sin(tita);
            y = N/2.0 + radius * cos(tita);

            if (x>N-1 || y>N-1)
            {
                creal_set(out[u][v], 0.0);
                cimag_set(out[u][v], 0.0);
            }
            else {
                sample = &in[(unsigned int)floor(x)][(unsigned int)floor(y)];

                #if DEBUG_POLAR
                X[(unsigned int)floor(x)][(unsigned int)floor(y)] = 255.0;
                #endif

                creal_set(out[u][v], sample->real);
                assert(creal(out[u][v]) == creal(out[u][v]));
                cimag_set(out[u][v], sample->imag);
            }
        }
    }

    #if DEBUG_POLAR
    write_image("LOG_POLAR_SAMPLING.bmp", X, N, N);
    #endif
#endif
}

