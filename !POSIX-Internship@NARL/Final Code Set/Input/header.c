#include <stdio.h>

//Data Header (128 bytes)

char getch(){
    #include <unistd.h>   //_getch*/
    #include <termios.h>  //_getch*/
    char buf=0;
    struct termios old={0};
    fflush(stdout);
    if(tcgetattr(0, &old)<0)
        perror("tcsetattr()");
    old.c_lflag&=~ICANON;
    old.c_lflag&=~ECHO;
    old.c_cc[VMIN]=1;
    old.c_cc[VTIME]=0;
    if(tcsetattr(0, TCSANOW, &old)<0)
        perror("tcsetattr ICANON");
    if(read(0,&buf,1)<0)
        perror("read()");
    old.c_lflag|=ICANON;
    old.c_lflag|=ECHO;
    if(tcsetattr(0, TCSADRAIN, &old)<0)
        perror ("tcsetattr ~ICANON");
    printf("%c\n",buf);
    return buf;
 }


/*
#include <termios.h>
#include <stdio.h>

static struct termios old, new;

// Initialize new terminal i/o settings 
void initTermios(int echo) 
{
  tcgetattr(0, &old); // grab old terminal i/o settings 
  new = old; // make new settings same as old settings 
  new.c_lflag &= ~ICANON; // disable buffered i/o 
  new.c_lflag &= echo ? ECHO : ~ECHO; // set echo mode 
  tcsetattr(0, TCSANOW, &new); // use these new terminal i/o settings now 
}

// Restore old terminal i/o settings 
void resetTermios(void) 
{
  tcsetattr(0, TCSANOW, &old);
}

// Read 1 character - echo defines echo mode 
char getch_(int echo) 
{
  char ch;
  initTermios(echo);
  ch = getchar();
  resetTermios();
  return ch;
}

// Read 1 character without echo 
char getch(void)
{
  return getch_(0);
}

*/

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

/*

struc Data
{

float data[51200]

};

*/

int n=0;

int main()
{

int i,j,count=0,flag=0;

FILE *fp;

struct Header s;

fp=fopen("15AU2015SASHT1.r1","rb");

FILE *f = fopen("out.txt", "w");

//n=0;

/*

while(1)
{

fread(&s,sizeof(s),1,fp);

if(feof(fp))
{
break;
}

*/
fread(&s,sizeof(s),1,fp);

/*

//for(j=0;j<2;j++)
//{

printf("\nThe No. of Range bins is:%d\n",s.nrgb);
printf("\nThe No. of FFT points is:%d\n",s.nfft);

//getch();
//getchar();

*/
/*
for(i=0;i<512000;i++)
{
printf("\nThe value of %d FFT point is:%f\n",i,s.data[i]);
}
*/

//************************************//

//************************************//

fprintf(f, "Channel 1 I data");
fprintf(f, "real = [ ");

for (n=n ; n<51200 ; n++) 
{
      fprintf(f, "%f  ", s.data[n]);
}
    
fprintf(f, "];\n");

fprintf(f, "Channel 1 Q data");
fprintf(f, "Imaginary = [ ");

for (n=n ; n<2*51200 ;n++) 
{
      fprintf(f, "%f ", s.data[n]);
}

fprintf(f, "];\n");



//************************************//

//************************************//

fprintf(f, "Channel 2 I data");
fprintf(f, "real = [ ");

for (n=n ; n<3*51200 ; n++) 
{
      fprintf(f, "%f  ", s.data[n]);
}
    
fprintf(f, "];\n");

fprintf(f, "Channel 2 Q data");
fprintf(f, "Imaginary = [ ");

for (n=n ; n<4*51200 ;n++) 
{
      fprintf(f, "%f ", s.data[n]);
}

fprintf(f, "];\n");

//************************************//

//************************************//

fprintf(f, "Channel 3 I data");
fprintf(f, "real = [ ");

for (n=n ; n<5*51200 ; n++) 
{
      fprintf(f, "%f  ", s.data[n]);
}
    
fprintf(f, "];\n");

fprintf(f, "Channel 3 Q data");
fprintf(f, "Imaginary = [ ");

for (n=n ; n<6*51200 ;n++) 
{
      fprintf(f, "%f ", s.data[n]);
}

fprintf(f, "];\n");

//************************************//

//************************************//

fprintf(f, "Channel 4 I data");
fprintf(f, "real = [ ");

for (n=n ; n<7*51200 ; n++) 
{
      fprintf(f, "%f  ", s.data[n]);
}
    
fprintf(f, "];\n");

fprintf(f, "Channel 4 Q data");
fprintf(f, "Imaginary = [ ");

for (n=n ; n<8*51200 ;n++) 
{
      fprintf(f, "%f ", s.data[n]);
}

fprintf(f, "];\n");

//************************************//

//************************************//

fprintf(f, "Channel 5 I data");
fprintf(f, "real = [ ");

for (n=n ; n<9*51200 ; n++) 
{
      fprintf(f, "%f  ", s.data[n]);
}
    
fprintf(f, "];\n");

fprintf(f, "Channel 5 Q data");
fprintf(f, "Imaginary = [ ");

for (n=n ; n<10*51200 ;n++) 
{
      fprintf(f, "%f ", s.data[n]);
}

fprintf(f, "];\n");



//************************************//

//flag++;
/*
if (flag == 5 )
{
count++;
}*/



count++;

//}

printf("Total Frames in the file is: %d\n",count);

fclose(fp);
return 0;
}



