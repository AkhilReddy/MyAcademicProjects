#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//long long sum = 0;
//Thread function to generate sum of 0 to N

void* sum_runner(void* arg)
{
   long long *limit_ptr = (long long*) arg;
   long long limit = *limit_ptr; 
   free(arg);
   
   long long sum = 0;

   for (long long i =0 ;i <= limit ;i++)
   {
    sum += i;
   }

   //Pass back data in dynamically allocated memory
   long long *answer = malloc(sizeof(*answer));
   
   *answer = sum;
   
   pthread_exit(answer);
}


int main(int argc , char **argv)
{

  if(argc < 2)
  {
  printf("Usage: %s <num>\n",argv[0]);
  exit(-1);
  }
   
  
  long long *limit = malloc(sizeof(*limit));
  *limit = atoll(argv[1]); //atoll ==> ascii to long long from argv[] to limit
  
  // Thread ID:
  pthread_t tid;

  // Create attributes
  pthread_attr_t attr;
  pthread_attr_init(&attr);

  pthread_create(&tid, &attr, sum_runner, limit);


  // Wait until thread is done its work
  long long *result; 
  pthread_join(tid, (void **)&result); // int pthread_join(pthread_t thread, void **retval);
  //**retreval ==> pointer to pointer i.e &(pointer).So is &result.Now we need to typecast pointer to pointer to (void **)
  printf("sum is %lld\n",*result); 
 
  free(result);
  return 0;

}
