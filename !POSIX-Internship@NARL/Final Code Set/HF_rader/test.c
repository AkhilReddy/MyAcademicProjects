#include <stdio.h>
#include <stdlib.h>
#include <complex.h>

/*
float array_tester(float array[])
{
int i;
float sum=0;

for(i=0;i<5;i++)
{
sum = sum + *(array+i);
}

return sum;
}

int main()
{
int n=0;
float data[5] = {2,3,4,3,1},sum;
float *array;
array=(float *) malloc(5*sizeof(float));

for (n ; n<5 ; n++) 
{
     *(array + n) = data[n];
}

for (n=0 ; n<5 ; n++) 
{
      printf("%f\n",*(array + n));
       
}

sum = array_tester(array);

printf("Value of Sum: %f \n",sum);

return 0;
}
*/

int main()
{
complex float a = 4 + 3i;
     
float b = __real__ a;          /* b is now 4. */
float c = __imag__ a; 

printf("%f  %f\n",b,c);


return 0;
}
