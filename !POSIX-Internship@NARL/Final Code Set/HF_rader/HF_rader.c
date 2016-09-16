/*

To Work:

gcc HF_rader.c fft.c -pthread -lm (-std=c99)

*/



#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>

#include "aki_header.h"

#define CCOUNT 51200

#define CVAL 5

struct channel_input
{

float *array1;
float *array2;
complex float *channelval;
complex float *channel1conj;

};

void* channel_runner(void* arg)
{

   printf("**************##########***************\n");
   struct channel_input *limit_ptr = (struct channel_input*) arg;
    
   float *array1 = limit_ptr->array1;
   float *array2 = limit_ptr->array2;
   int status,n,j;

//Performing FFT

size_t m = CCOUNT;

status = transform(array1,array2,m);

printf("Status after doing fft transform  for channel 1 is : %d\n",status);

//Converting to Complex FFT

complex float *channel1;
channel1=(complex float *) malloc(CCOUNT*sizeof(complex float));

for (j=0 ; j<CCOUNT ; j++) 
{
      *(channel1+j) = *(array1+j) + *(array2+j)*I;
}

printf("Completed converting into complex FFT for Channel 1 ...\n");

//Performing FFT Shift

int count = CCOUNT;

fftshift(channel1, count);

printf("Completed Performing FFT Shift...\n");

limit_ptr->channelval = channel1;

//Performing Conjugation
complex float *channel1conj;
channel1conj=(complex float *) malloc(CCOUNT*sizeof(complex float));

channel1conj = conjugate(channel1,channel1conj,count);

limit_ptr->channel1conj = channel1conj ;

printf("Completed Performing Conjugation to FFT Shift...\n");

pthread_exit(0);

/*
cleanup:
free(channel1conj);
free(channel1);
free(limit_ptr);
*/

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

float *arrayI[5];
float *arrayQ[5];

//Channel 1 I data

float *array1;
array1=(float *) malloc(CCOUNT*sizeof(float));

for (n ; n<CCOUNT ; n++) 
{
      *(array1+n) = s.data[n];
}

arrayI[0] = array1;

//Channel 1 Q data

float *array2;
array2=(float *) malloc(CCOUNT*sizeof(float));

for (n,j=0 ; n<2*CCOUNT ; n++,j++) 
{
      *(array2+j) = s.data[n];
}

arrayQ[0] = array2;

//Channel 2 I data

float *array3;
array3=(float *) malloc(CCOUNT*sizeof(float));

for (n,j=0 ; n<3*CCOUNT ; n++,j++) 
{
      *(array3+j) = s.data[n];
}

arrayI[1] = array3;

//Channel 2 Q data

float *array4;
array4=(float *) malloc(CCOUNT*sizeof(float));

for (n,j=0 ; n<4*CCOUNT ; n++,j++) 
{
      *(array4+j) = s.data[n];
}

arrayQ[1] = array4;

//Channel 3 I data

float *array5;
array5=(float *) malloc(CCOUNT*sizeof(float));

for (n,j=0 ; n<5*CCOUNT ; n++,j++) 
{
      *(array5+j) = s.data[n];
}

arrayI[2] = array5;

//Channel 3 Q data

float *array6;
array6=(float *) malloc(CCOUNT*sizeof(float));

for (n,j=0 ; n<6*CCOUNT ; n++,j++) 
{
      *(array6+j) = s.data[n];
}

arrayQ[2] = array6;

//Channel 4 I data

float *array7;
array7=(float *) malloc(CCOUNT*sizeof(float));

for (n,j=0 ; n<7*CCOUNT ; n++,j++) 
{
      *(array7+j) = s.data[n];
}

arrayI[3] = array7;

//Channel 4 Q data

float *array8;
array8=(float *) malloc(CCOUNT*sizeof(float));

for (n,j=0 ; n<8*CCOUNT ; n++,j++) 
{
      *(array8+j) = s.data[n];
}

arrayQ[3] = array8;

//Channel 5 I data

float *array9;
array9=(float *) malloc(CCOUNT*sizeof(float));

for (n,j=0  ; n<9*CCOUNT ; n++,j++) 
{
      *(array9+j) = s.data[n];
}

arrayI[4] = array9;

//Channel 5 Q data

float *array10;
array10=(float *) malloc(CCOUNT*sizeof(float));

for (n,j=0 ; n<10*CCOUNT ; n++,j++) 
{
      *(array10+j) = s.data[n];
}

arrayQ[4] = array10;

//Multi-Thrading

  // num_args = 5
 struct channel_input args[CVAL];
  // Thread ID:
  pthread_t tids[CVAL];

  for(i=0; i < CVAL ; i++)
  {
  
   // Create attributes for each thread
  args[i].array1 = arrayI[i]; 
  args[i].array2 = arrayQ[i];

  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_create(&tids[i], &attr, channel_runner, &args[i]);
  
  }

  complex float *complexCresult[5];
  complex float *complexresult[5];

  // Wait until threads are done its work
  for( i=0; i < CVAL ; i++)
  {

  pthread_join(tids[i], NULL);
  complexresult[i] = args[i].channelval;
  complexCresult[i] = args[i].channel1conj;

  }

//Calculating S Value

int r = 5, c = 5;
complex float *** Sval;
Sval = (complex float ***)malloc(r*sizeof(complex float**));

for (i = 0; i< r; i++) 
{

   Sval[i] = (complex float **) malloc(c*sizeof(complex float *));

   for (j = 0; j < c; j++) 
   {

   Sval[i][j] = (complex float *)malloc(CCOUNT*sizeof(complex float));
   }

}
 
int k;


for(i=0;i<CVAL;i++)
{
  for(j=0;j<CVAL;j++)
  {
    if(i==j)
    {
    break;
    }

    for (k=0 ; k<CCOUNT ; k++) 
    {
     *(Sval[i][j] + k) = ((*(complexresult[i] + k))*(*(complexCresult[j] + k)))/(csqrtf((*(complexresult[i] + k))*(*(complexCresult[i] + k)))*csqrtf((*(complexresult[j] + k))*(*(complexCresult[j] + k))));
    }
      
  }
}

//Frame Counter

counter++;
}

return 0;

}
