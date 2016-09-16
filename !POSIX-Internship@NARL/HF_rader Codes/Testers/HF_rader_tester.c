#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>

#include "aki_header.h"

#define CCOUNT 51200

//Data Header (128 bytes)

struct Header
{
short int Radar_Type; //. For 30MHz = 1,53MHz=2
short int baudlength; // Baud length of transmission
short int nrgb; // No. of Range bins
short int nfft; // No. of FFT points
short int ncoh; // No. of Coherent integrations
short int nicoh; // No. of Incoherent integrations
short int ipp; // Inter pulse period
short int pwd; // Pulse width in micro seconds
short int cflg; // Code flag
short int nwin; // No. of observation windows
short int w1start; // Window1 start
short int w1len; // Window1 length
short int w2start; // Window2 start – not used
short int w2len; // Window2 length – not used
short int year; // Year
short int month; // Month
short int day; // Day
short int hour; // Hour
short int min; // Minute
short int sec; // Seconds
short int nbeams; // No of beams in a beam scan cycle
short int beam; // Beam position (current)
short int scancycle; // Number of the beam scan cycle in progress
short int attn; // Receiver attenuation level – not used
short int w3start; // 3rd window of observation– not used
short int w3len; // 3rd window length– not used
short int simrange1; // Simulated signal range
short int txpower; // TX power
short int winfn; // Window fn. used for FFT
short int noofpulses; // No of pulses in transmission – not used
short int dtype; // Data type
short int pulsedelay[9]; // Pulse delay from starting – not used
short int stc_win; // STC window length – not used
short int pulsedelay10; // Tenth pulse delay – not used
short int pulsedelay11; // Eleventh pulse delay – not used
short int simrange2; // Simulated signal - 2 range – not used
short int stc_win_start; // STC window start – not used
short int noOfFreq; // No of frequencies used in Tx seq. of IPP – not used
float txIFFreq[4]; // IF values used in Transmission – not used
short int operationMode; // Whether DBS/SDI etc. – not used
short int adptiveRefRange; // Adaptive reference range – not used
short int adaptiveRefLevel; // % of the maximum – not used
char commentCode; // comments of 256 type can be stored. Currently used to store RADAR Mode
char comment[13 ]; // Sht file name
float data[512000];
};

int main()
{

int i,j,counter=0,flag=0,status;

FILE *fp;

struct Header s;

fp=fopen("15AU2015SASHT1.r1","rb");

//Main Loop Starts Here

while(1)
{

int n=0;

if(counter == 1)
{
break;
}

fread(&s,sizeof(s),1,fp);

if(feof(fp))
{
break;
}

FILE *f = fopen("HF1testdata.txt", "a");

size_t m = CCOUNT;

//Channel 1 I data

float *array1;
array1=(float *) malloc(CCOUNT*sizeof(float));

for (n ; n<CCOUNT ; n++) 
{
      *(array1+n) = s.data[n];
}

fprintf(f, "Channel 1 I data");
fprintf(f, "real = [ ");

for ( i=6144;i<6656;i++) 
{
      fprintf(f, "%f  ", *(array1+i));
}
    
fprintf(f, "];\n\n");

printf("value of n: %d\n",n);


//Channel 1 Q data

float *array2;
array2=(float *) malloc(CCOUNT*sizeof(float));

for (n,j=0 ; n<2*CCOUNT ; n++,j++) 
{
      *(array2+j) = s.data[n];
}

fprintf(f, "Channel 1 Q data");
fprintf(f, "Imaginary = [ ");

for (i=6144;i<6656;i++) 
{
      fprintf(f, "%f  ", *(array2+i));
}
    
fprintf(f, "];\n\n");

printf("value of n: %d\n",n);

status = transform(array1,array2,m);

FILE *f2 = fopen("HF1ffttestdata.txt", "a");

fprintf(f2, "Channel 1 I data");
fprintf(f2, "real = [ ");

for ( i=6144;i<6656;i++) 
{
      fprintf(f2, "%f  ", *(array1+i));
}
    
fprintf(f2, "];\n\n");

fprintf(f2, "Channel 1 Q data");
fprintf(f2, "Imaginary = [ ");

for (i=6144;i<6656;i++) 
{
      fprintf(f2, "%f  ", *(array2+i));
}
    
fprintf(f2, "];\n\n");

printf("Status after doing fft transform is : %d\n",status);

//Converting to Complex FFT
complex float *channel1;
channel1=(complex float *) malloc(CCOUNT*sizeof(complex float));

i=0;
printf("value of n: %d\n",n);

for (i ; i<CCOUNT ; i++) 
{
      *(channel1+i) = *(array1+i) + *(array2+i)*I;
}

FILE *f3 = fopen("HFfftcomplexdata.txt", "a"); 
 
fprintf(f3, "Channel 1 data in Complex Format: \n");
fprintf(f3, "[ ");

for (i=6144;i<6656;i++) 
{
      fprintf(f3, "%f + i%f\n", creal(*(channel1+i)), cimag(*(channel1+i))); 
}
    
fprintf(f3, "];\n\n");

printf("Completed converting into complex FFT...\n");

//Performing FFT Shift

int count = CCOUNT;

fftshift(channel1, count);

fprintf(f3, "Channel 1 data in Complex Format after FFT shift: \n");
fprintf(f3, "[ ");

for (i=6144;i<6656;i++) 
{
      fprintf(f3, "%f + i%f\n", creal(*(channel1+i)), cimag(*(channel1+i))); 
}
    
fprintf(f3, "];\n\n");

printf("Completed Performing FFT Shift...\n");

//Performing Conjugation
complex float *channel1conj;
channel1conj=(complex float *) malloc(CCOUNT*sizeof(complex float));

channel1conj = conjugate(channel1,channel1conj,count);

fprintf(f3, "Channel 1 conjugate data in Complex Format after FFT shift and Conjugation: \n");
fprintf(f3, "[ ");

for (i=6144;i<6656;i++) 
{
      fprintf(f3, "%f + i%f\n", creal(*(channel1conj+i)), cimag(*(channel1conj+i))); 
}

fprintf(f3, "];\n\n");    

////////////////////////////////////////////////////////////////////////////

//Channel 2 I data

printf("\nChannel 2\n\n");

float *array3;
array3=(float *) malloc(CCOUNT*sizeof(float));

for (n,j=0; n<3*CCOUNT ; n++,j++) 
{
      *(array3+j) = s.data[n];
}

fprintf(f, "Channel 2 I data");
fprintf(f, "real = [ ");

for ( i=6144;i<6656;i++) 
{
      fprintf(f, "%f  ", *(array3+i));
}
    
fprintf(f, "];\n\n");

printf("value of n: %d\n",n);


//Channel 2 Q data

float *array4;
array4=(float *) malloc(CCOUNT*sizeof(float));

for (n,j=0 ; n<4*CCOUNT ; n++,j++) 
{
      *(array4+j) = s.data[n];
}

fprintf(f, "Channel 2 Q data");
fprintf(f, "Imaginary = [ ");

for (i=6144;i<6656;i++) 
{
      fprintf(f, "%f  ", *(array4+i));
}
    
fprintf(f, "];\n\n");

printf("value of n: %d\n",n);


status = transform(array3,array4,m);

fprintf(f2, "Channel 2 I data");
fprintf(f2, "real = [ ");

for ( i=6144;i<6656;i++) 
{
      fprintf(f2, "%f  ", *(array3+i));
}
    
fprintf(f2, "];\n\n");

fprintf(f2, "Channel 2 Q data");
fprintf(f2, "Imaginary = [ ");

for (i=6144;i<6656;i++) 
{
      fprintf(f2, "%f  ", *(array4+i));
}
    
fprintf(f2, "];\n\n");

printf("Status after doing fft transform is : %d\n",status);

//Converting to Complex FFT
complex float *channel2;
channel2=(complex float *) malloc(CCOUNT*sizeof(complex float));

i=0;
printf("value of n: %d\n",n);

for (i ; i<CCOUNT ; i++) 
{
      *(channel2+i) = *(array3+i) + *(array4+i)*I;
}
 

fprintf(f3, "\nChannel 2 data in Complex Format: \n");
fprintf(f3, "[ ");

for (i=6144;i<6656;i++) 
{
      fprintf(f3, "%f + i%f\n", creal(*(channel2+i)), cimag(*(channel2+i))); 
}
    
fprintf(f3, "];\n\n");

printf("Completed converting into complex FFT...\n");

//Performing FFT Shift

fftshift(channel2, count);

fprintf(f3, "\nChannel 2 data in Complex Format after FFT shift: \n");
fprintf(f3, "[ ");

for (i=6144;i<6656;i++) 
{
      fprintf(f3, "%f + i%f\n", creal(*(channel2+i)), cimag(*(channel2+i))); 
}
    
fprintf(f3, "];\n\n");

printf("Completed Performing FFT Shift...\n");

//Performing Conjugation
complex float *channel2conj;
channel2conj=(complex float *) malloc(CCOUNT*sizeof(complex float));

channel2conj = conjugate(channel2,channel2conj,count);

fprintf(f3, "Channel 2 conjugate data in Complex Format after FFT shift and Conjugation: \n");
fprintf(f3, "[ ");

for (i=6144;i<6656;i++) 
{
      fprintf(f3, "%f + i%f\n", creal(*(channel2conj+i)), cimag(*(channel2conj+i))); 
}

fprintf(f3, "];\n\n"); 

////////////////////////////////////////////////////////////////////////////////////

//Channel 3 I data

float *array5;
array5=(float *) malloc(CCOUNT*sizeof(float));

for (n,j=0; n<5*CCOUNT ; n++,j++) 
{
      *(array5+j) = s.data[n];
}

fprintf(f, "Channel 3 I data");
fprintf(f, "real = [ ");

for (i=6144;i<6656;i++) 
{
      fprintf(f, "%f  ", *(array5+i));
}
    
fprintf(f, "];\n\n");

printf("value of n: %d\n",n);


//Channel 2 Q data

float *array6;
array6=(float *) malloc(CCOUNT*sizeof(float));

for (n,j=0 ; n<6*CCOUNT ; n++,j++) 
{
      *(array6+j) = s.data[n];
}

fprintf(f, "Channel 3 Q data");
fprintf(f, "Imaginary = [ ");

for (i=6144;i<6656;i++) 
{
      fprintf(f, "%f  ", *(array6+i));
}
    
fprintf(f, "];\n\n");

printf("value of n: %d\n",n);


status = transform(array5,array6,m);

fprintf(f2, "Channel 3 I data");
fprintf(f2, "real = [ ");

for (i=6144;i<6656;i++) 
{
      fprintf(f2, "%f  ", *(array5+i));
}
    
fprintf(f2, "];\n\n");

fprintf(f2, "Channel 3 Q data");
fprintf(f2, "Imaginary = [ ");

for (i=6144;i<6656;i++) 
{
      fprintf(f2, "%f  ", *(array6+i));
}
    
fprintf(f2, "];\n\n");

printf("Status after doing fft transform is : %d\n",status);

//Converting to Complex FFT
complex float *channel3;
channel3=(complex float *) malloc(CCOUNT*sizeof(complex float));

i=0;
printf("value of n: %d\n",n);

for (i ; i<CCOUNT ; i++) 
{
      *(channel3+i) = *(array5+i) + *(array6+i)*I;
}
 

fprintf(f3, "\nChannel 3 data in Complex Format: \n");
fprintf(f3, "[ ");

for (i=6144;i<6656;i++) 
{
      fprintf(f3, "%f + i%f\n", creal(*(channel3+i)), cimag(*(channel3+i))); 
}
    
fprintf(f3, "];\n\n");

printf("Completed converting into complex FFT...\n");

//Performing FFT Shift

fftshift(channel3, count);

fprintf(f3, "Channel 3 data in Complex Format after FFT shift: \n");
fprintf(f3, "[ ");

for (i=6144;i<6656;i++) 
{
      fprintf(f3, "%f + i%f\n", creal(*(channel3+i)), cimag(*(channel3+i))); 
}
    
fprintf(f3, "];\n\n");

printf("Completed Performing FFT Shift...\n");

//Performing Conjugation
complex float *channel3conj;
channel3conj=(complex float *) malloc(CCOUNT*sizeof(complex float));

channel3conj = conjugate(channel3,channel3conj,count);

fprintf(f3, "Channel 3 conjugate data in Complex Format after FFT shift and Conjugation: \n");
fprintf(f3, "[ ");

for (i=6144;i<6656;i++) 
{
      fprintf(f3, "%f + i%f\n", creal(*(channel3conj+i)), cimag(*(channel3conj+i))); 
}

fprintf(f3, "];\n\n");

////////////////////////////////////////////////////////////////////////////////////

//Channel 4 I data

float *array7;
array7=(float *) malloc(CCOUNT*sizeof(float));

for (n,j=0; n<7*CCOUNT ; n++,j++) 
{
      *(array7+j) = s.data[n];
}

fprintf(f, "Channel 4 I data");
fprintf(f, "real = [ ");

for (i=6144;i<6656;i++) 
{
      fprintf(f, "%f  ", *(array7+i));
}
    
fprintf(f, "];\n\n");

printf("value of n: %d\n",n);


//Channel 4 Q data

float *array8;
array8=(float *) malloc(CCOUNT*sizeof(float));

for (n,j=0 ; n<8*CCOUNT ; n++,j++) 
{
      *(array8+j) = s.data[n];
}

fprintf(f, "Channel 4 Q data");
fprintf(f, "Imaginary = [ ");

for (i=6144;i<6656;i++) 
{
      fprintf(f, "%f  ", *(array8+i));
}
    
fprintf(f, "];\n\n");

printf("value of n: %d\n",n);


status = transform(array7,array8,m);

fprintf(f2, "Channel 4 I data");
fprintf(f2, "real = [ ");

for (i=6144;i<6656;i++) 
{
      fprintf(f2, "%f  ", *(array7+i));
}
    
fprintf(f2, "];\n\n");

fprintf(f2, "Channel 4 Q data");
fprintf(f2, "Imaginary = [ ");

for (i=6144;i<6656;i++) 
{
      fprintf(f2, "%f  ", *(array8+i));
}
    
fprintf(f2, "];\n\n");

printf("Status after doing fft transform is : %d\n",status);

//Converting to Complex FFT
complex float *channel4;
channel4=(complex float *) malloc(CCOUNT*sizeof(complex float));

i=0;
printf("value of n: %d\n",n);

for (i ; i<CCOUNT ; i++) 
{
      *(channel4+i) = *(array7+i) + *(array8+i)*I;
}
 

fprintf(f3, "Channel 4 data in Complex Format: \n");
fprintf(f3, "[ ");

for (i=6144;i<6656;i++) 
{
      fprintf(f3, "%f + i%f\n", creal(*(channel4+i)), cimag(*(channel4+i))); 
}
    
fprintf(f3, "];\n\n");

printf("Completed converting into complex FFT...\n");

//Performing FFT Shift

fftshift(channel4, count);

fprintf(f3, "Channel 4 data in Complex Format after FFT shift: \n");
fprintf(f3, "[ ");

for (i=6144;i<6656;i++) 
{
      fprintf(f3, "%f + i%f\n", creal(*(channel4+i)), cimag(*(channel4+i))); 
}
    
fprintf(f3, "];\n\n");

printf("Completed Performing FFT Shift...\n");

//Performing Conjugation
complex float *channel4conj;
channel4conj=(complex float *) malloc(CCOUNT*sizeof(complex float));

channel4conj = conjugate(channel4,channel4conj,count);

fprintf(f3, "Channel 4 conjugate data in Complex Format after FFT shift and Conjugation: \n");
fprintf(f3, "[ ");

for (i=6144;i<6656;i++) 
{
      fprintf(f3, "%f + i%f\n", creal(*(channel4conj+i)), cimag(*(channel4conj+i))); 
}

fprintf(f3, "];\n\n");

////////////////////////////////////////////////////////////////////////////////////

//Channel 5 I data

float *array9;
array9=(float *) malloc(CCOUNT*sizeof(float));

for (n,j=0; n<9*CCOUNT ; n++,j++) 
{
      *(array9+j) = s.data[n];
}

fprintf(f, "Channel 5 I data");
fprintf(f, "real = [ ");

for ( i=6144;i<6656;i++) 
{
      fprintf(f, "%f  ", *(array9+i));
}
    
fprintf(f, "];\n\n");

printf("value of n: %d\n",n);


//Channel 5 Q data

float *array10;
array10=(float *) malloc(CCOUNT*sizeof(float));

for (n,j=0 ; n<10*CCOUNT ; n++,j++) 
{
      *(array10+j) = s.data[n];
}

fprintf(f, "Channel 5 Q data");
fprintf(f, "Imaginary = [ ");

for (i=6144;i<6656;i++) 
{
      fprintf(f, "%f  ", *(array10+i));
}
    
fprintf(f, "];\n\n");

printf("value of n: %d\n",n);


status = transform(array9,array10,m);

fprintf(f2, "Channel 5 I data");
fprintf(f2, "real = [ ");

for ( i=6144;i<6656;i++) 
{
      fprintf(f2, "%f  ", *(array9+i));
}
    
fprintf(f2, "];\n\n");

fprintf(f2, "Channel 5 Q data");
fprintf(f2, "Imaginary = [ ");

for (i=6144;i<6656;i++) 
{
      fprintf(f2, "%f  ", *(array10+i));
}
    
fprintf(f2, "];\n\n");

printf("Status after doing fft transform is : %d\n",status);

//Converting to Complex FFT
complex float *channel5;
channel5=(complex float *) malloc(CCOUNT*sizeof(complex float));

i=0;
printf("value of n: %d\n",n);

for (i ; i<CCOUNT ; i++) 
{
      *(channel5+i) = *(array9+i) + *(array10+i)*I;
}
 

fprintf(f3, "Channel 5 data in Complex Format: \n");
fprintf(f3, "[ ");

for (i=6144;i<6656;i++) 
{
      fprintf(f3, "%f + i%f\n", creal(*(channel5+i)), cimag(*(channel5+i))); 
}
    
fprintf(f3, "];\n\n");

printf("Completed converting into complex FFT...\n");

//Performing FFT Shift

fftshift(channel5, count);

fprintf(f3, "Channel 5 data in Complex Format after FFT shift: \n");
fprintf(f3, "[ ");

for (i=6144;i<6656;i++) 
{
      fprintf(f3, "%f + i%f\n", creal(*(channel5+i)), cimag(*(channel5+i))); 
}
    
fprintf(f3, "];\n\n");

printf("Completed Performing FFT Shift...\n");

//Performing Conjugation
complex float *channel5conj;
channel5conj=(complex float *) malloc(CCOUNT*sizeof(complex float));

channel5conj = conjugate(channel5,channel5conj,count);

fprintf(f3, "Channel 5 conjugate data in Complex Format after FFT shift and Conjugation: \n");
fprintf(f3, "[ ");

for (i=6144;i<6656;i++) 
{
      fprintf(f3, "%f + i%f\n", creal(*(channel5conj+i)), cimag(*(channel5conj+i))); 
}

fprintf(f3, "];\n\n");

////////////////////////////////////////////////////////////////////////////////////
        
    
fprintf(f3, "\n\n\n************************FRAME END********************\n\n");

printf("Completed Performing Conjugation to FFT Shift...\n");

FILE *f4 = fopen("HFsvalue.txt", "a"); 

//S value Calculation
fprintf(f4, "Channel 1 S Values with corresponding other Channel Conjugates: \n");
fprintf(f4, "\n\nS12:");
fprintf(f4, "[ ");

for(i=6144;i<6656;i++)
{
//fprintf(f4, "S12: \n\n");
//S12
complex float *S12;
S12=(complex float *) malloc(CCOUNT*sizeof(complex float));

*(S12+i) = (*(channel1+i))*(*(channel2conj+i))/(csqrtf((*(channel1+i))*(*(channel1conj+i))))*(csqrtf((*(channel2+i))*(*(channel2conj+i))));

 fprintf(f4, "%f + i%f\n", creal(*(S12+i)), cimag(*(S12+i)));


//S13

fprintf(f4, "\n\nS13: \n\n");
complex float *S13;
S13=(complex float *) malloc(CCOUNT*sizeof(complex float));

*(S13+i) = (*(channel1+i))*(*(channel3conj+i))/(csqrtf((*(channel1+i))*(*(channel1conj+i))))*(csqrtf((*(channel3+i))*(*(channel3conj+i))));

 fprintf(f4, "%f + i%f\n", creal(*(S13+i)), cimag(*(S13+i)));

fprintf(f4, "\n\nS14: \n\n");
//S14
complex float *S14;
S14=(complex float *) malloc(CCOUNT*sizeof(complex float));

*(S14+i) = (*(channel1+i))*(*(channel4conj+i))/(csqrtf((*(channel1+i))*(*(channel1conj+i))))*(csqrtf((*(channel4+i))*(*(channel4conj+i))));

 fprintf(f4, "%f + i%f\n", creal(*(S14+i)), cimag(*(S14+i)));

fprintf(f4, "\n\nS15: \n\n");
//S15
complex float *S15;
S15=(complex float *) malloc(CCOUNT*sizeof(complex float));

*(S15+i) = (*(channel1+i))*(*(channel5conj+i))/(csqrtf((*(channel1+i))*(*(channel1conj+i))))*(csqrtf((*(channel5+i))*(*(channel5conj+i))));

 fprintf(f4, "%f + i%f\n", creal(*(S15+i)), cimag(*(S15+i)));


}

fprintf(f4, "];\n\n");

counter++;

}

return 0;

}
