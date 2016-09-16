#ifndef _AKI_HEADER_H
#define _AKI_HEADER_H

#include <stdio.h>
#include <complex.h>
#include <fftw3.h>

//functions used

void fftshift(complex float *data, int count);
void ifftshift(complex float *data, int count);
complex float *conjugate(complex float *in,complex float *out,int n);
char getch();

//********************************//
/*
getch() is not an inbuilt function in Linux as conio.h is not defined in Linux c99 .So created getch() function seperately
*/

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
It is static function which cannot be accessed outside this file.
swap() function is used in fftshift to use accordingly.  
*/
static void swap(complex float *v1, complex float *v2)
{
    complex float tmp = *v1;
    *v1 = *v2;
    *v2 = tmp;
}


void fftshift(complex float *data, int count)
{
    int k = 0;
    int c = (int) floor((float)count/2);
    // For odd and for even numbers of element.We are useing different algorithm Here.
    if (count % 2 == 0)//This is for Even Count
    {
        for (k = 0; k < c; k++)
            swap(&data[k], &data[k+c]);
    }
    else // This is for Odd Count
    {
        complex float tmp = data[0];
        for (k = 0; k < c; k++)
        {
            data[k] = data[c + k + 1];
            data[c + k + 1] = data[k + 1];
        }
        data[c] = tmp;
    }
}

void ifftshift(complex float *data, int count) //This is used for Circular shift of Complex values.
{
    int k = 0;
    int c = (int) floor((float)count/2);
    if (count % 2 == 0)
    {
        for (k = 0; k < c; k++)
            swap(&data[k], &data[k+c]);
    }
    else
    {
        complex float tmp = data[count - 1];
        for (k = c-1; k >= 0; k--)
        {
            data[c + k + 1] = data[k];
            data[k] = data[c + k];
        }
        data[c] = tmp;
    }
}

/*
This Function is used for doing Conjugation for Each Channel Values.
We are using conj() function defined in complex.h header but this function is mainly used to get Proper value as Out vector. 
*/
complex float *conjugate(complex float *in,complex float *out,int n)
{
int i;

for(i=0;i<n;i++)
{

complex float z = in[i];
complex float z2 = conj(z);

out[i] = z2;

}

return out;

}

#endif
