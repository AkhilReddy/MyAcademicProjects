#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>

#include "aki_header.h"

#define CCOUNT 51200

struct channel_input
{
float *array1;
float *array2;
};

void* channel_runner(void* arg)
{
   
   printf("**************##########***************\n");
   struct channel_input *limit_ptr = (struct channel_input*) arg;
    
   float *array1 = limit_ptr->array1;
   float *array2 = limit_ptr->array2;

//Performing FFT

size_t m = CCOUNT;

status = transform(array1,array2,m);

printf("Status after doing fft transform  for channel 1 is : %d\n",status);

//Converting to Complex FFT

complex float *channel1;
channel1=(complex float *) malloc(CCOUNT*sizeof(complex float));

for (n=0 ; n<CCOUNT ; n++) 
{
      *(channel1+n) = *(array1+n) + *(array2+n)*I;
}

printf("Completed converting into complex FFT for Channel 1 ...\n");

//Performing FFT Shift

int count = CCOUNT;

fftshift(channel1, count);

printf("Completed Performing FFT Shift...\n");

//Performing Conjugation
complex float *channel1conj;
channel1conj=(complex float *) malloc(CCOUNT*sizeof(complex float));

channel1conj = conjugate(channel1,channel1conj,count);

printf("Completed Performing Conjugation to FFT Shift...\n");

pthread_exit(channel1conj);

cleanup:
free(channel1conj);
free(channel1);
free(limit_ptr);

}


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

//Channel 1 I data

float *array1;
array1=(float *) malloc(CCOUNT*sizeof(float));

for (n=n ; n<CCOUNT ; n++) 
{
      *(array1+n) = s.data[n];
}

//Channel 1 Q data

float *array2;
array2=(float *) malloc(CCOUNT*sizeof(float));

for (n,j=0 ; n<2*CCOUNT ; n++,j++) 
{
      *(array2+j) = s.data[n];
}

//Performing FFT

size_t m = CCOUNT;

status = transform(array1,array2,m);

printf("Status after doing fft transform  for channel 1 is : %d\n",status);

//Converting to Complex FFT

complex float *channel1;
channel1=(complex float *) malloc(CCOUNT*sizeof(complex float));

for (n=0 ; n<CCOUNT ; n++) 
{
      *(channel1+n) = *(array1+n) + *(array2+n)*I;
}

printf("Completed converting into complex FFT for Channel 1 ...\n");

//Performing FFT Shift

int count = CCOUNT;

fftshift(channel1, count);

printf("Completed Performing FFT Shift...\n");

//Performing Conjugation
complex float *channel1conj;
channel1conj=(complex float *) malloc(CCOUNT*sizeof(complex float));

channel1conj = conjugate(channel1,channel1conj,count);

printf("Completed Performing Conjugation to FFT Shift...\n");

counter++;
}

return 0;

}
