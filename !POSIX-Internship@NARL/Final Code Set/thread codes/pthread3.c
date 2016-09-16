#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Sum is computed by background thread
//long long sum = 0;

//structure to be returned from thread as we cannot return args directs from func. which are created inside func. 
struct sum_runner_struct{
long long limit;
long long answer;
};

//Thread function to generate sum of 0 to N

void* sum_runner(void* arg)
{
   struct sum_runner_struct *limit_ptr = (struct sum_runner_struct*) arg;
   long long limit = limit_ptr->limit; 
   
   long long sum = 0;
   
   for (long long i =0 ;i <= limit ;i++)
   {
    sum += i;
   }

    limit_ptr->answer = sum;

   // sum is a global variable. So other thread can access

   pthread_exit(0);
}


int main(int argc , char **argv)
{

  long long sum=0;
  
  if(argc < 2)
  {
  printf("Usage: %s <num1> <num2> <num3> <num4> .... <num..>\n",argv[0]);
  exit(-1);
  }

  //long long limit = atoll(argv[1]); //atoll ==> ascii to long long from argv[] to limit
  
  long long num_args = argc -1;

  struct sum_runner_struct args[num_args];
  // Thread ID:
  pthread_t tids[num_args];


  for( int i=0; i < num_args ; i++)
  {
  
   // Create attributes for each thread
  args[i].limit = atoll(argv[i+1]); 
  
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_create(&tids[i], &attr, sum_runner, &args[i]);
  
  }

  // Wait until threads are done its work
  for( int i=0; i < num_args ; i++)
  {
  
  pthread_join(tids[i], NULL);
  printf("sum is %lld\n",args[i].answer);
  sum = sum + args[i].answer;

  }

  printf("sum is %lld\n",sum); 
 
  return 0;

}

/*
Note:

pthread_self() function will give the thread id of current thread.

pthread_t pthread_self(void);

The pthread_self() function returns the Pthread handle of the calling thread. The pthread_self() function does NOT return the integral thread of the calling thread. You must use pthread_getthreadid_np() to return an integral identifier for the thread.

pthread_id_np_t   tid;
pthread_t         self;
self = pthread_self();
pthread_getunique_np(&self, &tid);

*/
