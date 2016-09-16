# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <time.h>
# include <omp.h>

int main ( );
void ccopy ( int n, double x[], double y[] );
void cfft2 ( int n, double x[], double y[], double w[], double sgn );
void cffti ( int n, double w[] );
double ggl ( double *ds );
void step ( int n, int mj, double a[], double b[], double c[], double d[], double w[], double sgn );
void timestamp ( );

int main ()
{
  double error;
  int first;
  double flops;
  double fnm1;
  int i;
  int icase;
  int it;
  int ln2;
  int ln2_max = 25;
  double mflops;
  int n;
  int nits = 10000;
  int proc_num;
  static double seed;
  double sgn;
  int thread_num;
  double *w;
  double wtime;
  double *x;
  double *y;
  double *z;
  double z0;
  double z1;

  timestamp ( );
  printf ( "\n" );
  printf ( "FFT_OPENMP\n" );
  printf ( "  Demonstrate an implementation of the Fast Fourier Transform of a complex data vector, using OpenMP for parallel execution.\n" );
  printf ( "  Number of processors available = %d\n", omp_get_num_procs ( ) );
  printf ( "  Number of threads = %d\n", omp_get_max_threads ( ) );
  
  printf ( "\n" );
  printf ( "           N      NITS    Error         Time          Time/Call     MFLOPS\n" );
  seed  = 331.0;
  n = 1;
  
  for ( ln2 = 1; ln2 <= ln2_max; ln2++ )
  {
    n = 2 * n;
    
    w = ( double * ) malloc (     n * sizeof ( double ) );
    x = ( double * ) malloc ( 2 * n * sizeof ( double ) );
    y = ( double * ) malloc ( 2 * n * sizeof ( double ) );
    z = ( double * ) malloc ( 2 * n * sizeof ( double ) );

    first = 1;

    for ( icase = 0; icase < 2; icase++ )
    {
      if ( first ) //As we are doing First one No need to parallise it.
      {
        for ( i = 0; i < 2 * n; i = i + 2 )
        {
          z0 = ggl ( &seed );
          z1 = ggl ( &seed );
          x[i] = z0;
          z[i] = z0;
          x[i+1] = z1;
          z[i+1] = z1;
        }
      } 
      else
      {
# pragma omp parallel shared ( n, x, z ) private ( i, z0, z1 )

# pragma omp for nowait

        for ( i = 0; i < 2 * n; i = i + 2 )
        {
          z0 = 0.0;            
          z1 = 0.0;              
          x[i] = z0;
          z[i] = z0;          
          x[i+1] = z1;
          z[i+1] = z1;        
        }
      }

      cffti ( n, w );

      if ( first )
      {
        sgn = + 1.0;
        cfft2 ( n, x, y, w, sgn );
        sgn = - 1.0;
        cfft2 ( n, y, x, w, sgn );

        fnm1 = 1.0 / ( double ) n;
        error = 0.0;
        for ( i = 0; i < 2 * n; i = i + 2 )
        {
          error = error + pow ( z[i]   - fnm1 * x[i], 2 )+ pow ( z[i+1] - fnm1 * x[i+1], 2 );
        }
        error = sqrt ( fnm1 * error );
        printf ( "%12d  %8d  %12e", n, nits, error );
        first = 0;
      }
      else
      {
        wtime = omp_get_wtime ( ); // WE are getting omp--time than cpu time
        for ( it = 0; it < nits; it++ )
        {
          sgn = + 1.0;
          cfft2 ( n, x, y, w, sgn );
          sgn = - 1.0;
          cfft2 ( n, y, x, w, sgn );
        }
        wtime = omp_get_wtime ( ) - wtime; // WE are getting omp--time than cpu time

        flops = 2.0 * ( double ) nits 
          * ( 5.0 * ( double ) n * ( double ) ln2 );

        mflops = flops / 1.0E+06 / wtime;

        printf ( "  %12e  %12e  %12f\n", wtime, wtime / ( double ) ( 2 * nits ), mflops );
      }
    }
    if ( ( ln2 % 4 ) == 0 ) 
    {
      nits = nits / 10;
    }
    if ( nits < 1 ) 
    {
      nits = 1;
    }
    free ( w );
    free ( x );
    free ( y );
    free ( z );
  }

  printf ( "  Normal end of execution.\n" );
  timestamp ( );

  return 0;
}


void ccopy ( int n, double x[], double y[] )  // CCOPY copies a complex vector.So We can Parallise
{
  int i;

  # pragma omp parallel shared ( n, x, y ) private (i)
  # pragma omp for nowait
  for ( i = 0; i < n; i++ )
  {
    y[i*2+0] = x[i*2+0];
    y[i*2+1] = x[i*2+1];
   }
  return;
}

void cfft2 ( int n, double x[], double y[], double w[], double sgn ) // CFFT2 performs a complex Fast Fourier Transform.
//Input, double SGN, is +1 for a "forward" FFT and -1 for a "backward" FFT. So Parallisation may not work.
{
  int j;
  int m;
  int mj;
  int tgle;

   m = ( int ) ( log ( ( double ) n ) / log ( 1.99 ) );
   mj   = 1;
  tgle = 1;
  step ( n, mj, &x[0*2+0], &x[(n/2)*2+0], &y[0*2+0], &y[mj*2+0], w, sgn );

  if ( n == 2 )
  {
    return;
  }

  for ( j = 0; j < m - 2; j++ )
  {
    mj = mj * 2;
    if ( tgle )
    {
      step ( n, mj, &y[0*2+0], &y[(n/2)*2+0], &x[0*2+0], &x[mj*2+0], w, sgn );
      tgle = 0;
    }
    else
    {
      step ( n, mj, &x[0*2+0], &x[(n/2)*2+0], &y[0*2+0], &y[mj*2+0], w, sgn );
      tgle = 1;
    }
  }
  if ( tgle ) 
  {
    ccopy ( n, y, x );
  }

  mj = n / 2;
  step ( n, mj, &x[0*2+0], &x[(n/2)*2+0], &y[0*2+0], &y[mj*2+0], w, sgn );

  return;
}


void cffti ( int n, double w[] ) //CFFTI sets up sine and cosine tables needed for the FFT calculation. Output, double W[N], a table of sines and cosines.
//So can be Parallised.
{
  double arg;
  double aw;
  int i;
  int n2;
  const double pi = 3.141592653589793;

  n2 = n / 2;
  aw = 2.0 * pi / ( ( double ) n );

# pragma omp parallel shared ( aw, n, w )private ( arg, i )
# pragma omp for nowait

  for ( i = 0; i < n2; i++ )
  {
    arg = aw * ( ( double ) i );
    w[i*2+0] = cos ( arg );
    w[i*2+1] = sin ( arg );
  }
  return;
}

double ggl ( double *seed ) //GGL generates uniformly distributed pseudorandom real numbers in [0,1]. 
//Output, double GGL, the next pseudorandom value.
{
  double d2 = 0.2147483647e10;
  double t;
  double value;

  t = ( double ) *seed;
  t = fmod ( 16807.0 * t, d2 );
  *seed = ( double ) t;
  value = ( double ) ( ( t - 1.0 ) / ( d2 - 1.0 ) );

  return value;
}

void step ( int n, int mj, double a[], double b[], double c[],double d[], double w[], double sgn )//STEP carries out one step of the workspace version of CFFT2.
{
  double ambr;
  double ambu;
  int j;
  int ja;
  int jb;
  int jc;
  int jd;
  int jw;
  int k;
  int lj;
  int mj2;
  double wjw[2];

  mj2 = 2 * mj;
  lj  = n / mj2;

# pragma omp parallel shared ( a, b, c, d, lj, mj, mj2, sgn, w ) private ( ambr, ambu, j, ja, jb, jc, jd, jw, k, wjw )
# pragma omp for nowait

  for ( j = 0; j < lj; j++ )
  {
    jw = j * mj;
    ja  = jw;
    jb  = ja;
    jc  = j * mj2;
    jd  = jc;

    wjw[0] = w[jw*2+0]; 
    wjw[1] = w[jw*2+1];

    if ( sgn < 0.0 ) 
    {
      wjw[1] = - wjw[1];
    }

    for ( k = 0; k < mj; k++ )
    {
      c[(jc+k)*2+0] = a[(ja+k)*2+0] + b[(jb+k)*2+0];
      c[(jc+k)*2+1] = a[(ja+k)*2+1] + b[(jb+k)*2+1];

      ambr = a[(ja+k)*2+0] - b[(jb+k)*2+0];
      ambu = a[(ja+k)*2+1] - b[(jb+k)*2+1];

      d[(jd+k)*2+0] = wjw[0] * ambr - wjw[1] * ambu;
      d[(jd+k)*2+1] = wjw[1] * ambr + wjw[0] * ambu;
    }
  }
  return;
}

void timestamp ( void )//TIMESTAMP prints the current YMDHMS date as a time stamp. // No need to Parallise 
{
# define TIME_SIZE 40

  static char time_buffer[TIME_SIZE];
  const struct tm *tm;
  size_t len;
  time_t now;

  now = time ( NULL );
  tm = localtime ( &now );

  len = strftime ( time_buffer, TIME_SIZE, "%d %B %Y %I:%M:%S %p", tm );

  printf ( "%s\n", time_buffer );

  return;
# undef TIME_SIZE
}
