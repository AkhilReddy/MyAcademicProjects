#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>

#include "aki_header.h"

#define CCOUNT 51200

//Data Header (128 bytes)

void calc_dft(float inreal[], float inimag[], float outreal[], float outimag[], size_t n) 
{
	int k;
	for (k = 0; k < n; k++) // For each output element
         {  
		float sumreal = 0;
		float sumimag = 0;
		int t;
		for (t = 0; t < n; t++) //For each input element 
                 { 
			float angle = 2 * M_PI * t * k / n;
			sumreal +=  inreal[t] * cos(angle) + inimag[t] * sin(angle);
			sumimag += -inreal[t] * sin(angle) + inimag[t] * cos(angle);
		 }
		outreal[k] = sumreal;
		outimag[k] = sumimag;
	}
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

FILE *f = fopen("HF1testdata2.txt", "a");

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

float *array3;
array3=(float *) malloc(CCOUNT*sizeof(float));

float *array4;
array4=(float *) malloc(CCOUNT*sizeof(float));

calc_dft(array1, array2, array3, array4, m);

FILE *f2 = fopen("HF1ffttestdata2.txt", "a");

fprintf(f2, "Channel 1 I data");
fprintf(f2, "real = [ ");

for ( i=6144;i<6656;i++) 
{
      fprintf(f2, "%f  ", *(array3+i));
}
    
fprintf(f2, "];\n\n");

fprintf(f2, "Channel 1 Q data");
fprintf(f2, "Imaginary = [ ");

for (i=6144;i<6656;i++) 
{
      fprintf(f2, "%f  ", *(array4+i));
}
    
fprintf(f2, "];\n\n");

counter++;
} 

return 0;

}

