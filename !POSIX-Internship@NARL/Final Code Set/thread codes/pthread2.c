#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Sum is computed by background thread
long long sum = 0;

//Thread function to generate sum of 0 to N

void* sum_runner(void* arg)
{
   long long *limit_ptr = (long long*) arg;
   long long limit = *limit_ptr; 

   
   for (long long i =0 ;i <= limit ;i++)
   {
    sum += i;
   }

   // sum is a global variable. So other thread can access

   pthread_exit(0);
}


int main(int argc , char **argv)
{

  if(argc < 2)
  {
  printf("Usage: %s <num1> <num2> <num3> <num4> .... <num..>\n",argv[0]);
  exit(-1);
  }

  long long limit = atoll(argv[1]); //atoll ==> ascii to long long from argv[] to limit
  
  long long num_args = argc -1;

  // Thread ID:
  pthread_t tids[num_args];


  for( int i=0; i < num_args ; i++)
  {
   // Create attributes for each thread
  pthread_attr_t attr;
  pthread_attr_init(&attr);

  pthread_create(&tids[i], &attr, sum_runner, &limit);
  
  }

  // Wait until threads are done its work
  for( int i=0; i < num_args ; i++)
  {
  
  pthread_join(tids[i], NULL);

  }

  printf("sum is %lld\n",sum); 
 
  return 0;

}
