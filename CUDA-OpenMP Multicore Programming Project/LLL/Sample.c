/*
gcc -o fopenmp fft_openmp.c
*/
#include<stdio.h>
#include<omp.h> //Thread creation by OS from Krnel side and by get that thread to user code. It takes time, So use parallelisum for large data.

int main()
{

printf("\nWe are going to run parallel program...\n");

printf("\nTotal number of Threads: %d",omp_get_num_threads());


omp_set_num_threads(5); //OR num_threads(5) after parallel directive

#pragma omp parallel //parallel is a directive which specifies OS that Parrall Execution is Starting 
{
printf("\nGreetings Akhil..");
}

long long int s,i; // Shared Vairable by default
//omp_get_thread_num(); we can get the thread num of working thread at the Instinct
//omp_get_num_threads(); We can get total number of threads running Parallelly in the code 

int n=100000;

#pragma omp parallel num_threads(10) default(shared)
#pragma omp for // We parallise only when no.of iteriations exceed n=500.
// To specifiy that these 10 threads share it inside for (loop)
// We need to specify i before to solve synchrnization Problem to access Shared Data
//Index variable i will be private by default
for(i=0;i<n;i++) 
{
//i is Private by default
//private(i)

s=s+i;
}

//Reduction is a clause for "for loop" and can use only after for
printf("\n%lld",s);

#pragma omp parallel num_threads(5) default(shared) private(i)
#pragma omp for reduction(+:s) // reduction is applied only for variables which are updating and shared data is shared by threads(say th1 and th2 as s1 and s2) locally and don't touch global  and at the end it will add both threads local shared data are added and updated to global shared data(S).'+' indicates local copy of 's' is assigned as s.'*' indicates asssigned as 
for(i=0;i<1000;i++)
{
s = s+i;
}

printf("\n\n %lld ",s);

int x=10;

#pragma omp parallel num_threads(5) 
#pragma omp for firstprivate(x) //final x value is not updated,it keeps preassigned value.
for(i=0;i<1000;i++)
{
printf("\n%d",x);
x=i;
}

printf("\n\n %d ",x);

int y =10;

#pragma omp parallel num_threads(5) 
#pragma omp for lastprivate(y) //final y value is updated to y
for(i=0;i<1000;i++)
{
printf("\n%d",y);
y=i;
}

printf("\n\n%d ",y);//Output: 999


//reduction is aplicable for "for loop"

/*
//Task level Parallisum

#pragma omp sections
{

#pragma omp section
{
add();
}

#pragma omp section
{
sub();
}

}

*/

/*
Static Scheduling:

th0 th1 th2| th0 th1 th2 |.... (Each set with 10 steps of allocation), For next sctin of allocation one thread will wait till other thrad are completed to move to next set of allocation.
To stop this we can do by  #pragma omp for schedule(static,10) nowait

*/

int j;

#pragma omp parallel num_threads(3)
{

#pragma omp for schedule(static,10)
for(j=0;j<100;j++)
{
printf("\nIteration %d run by thread  %d",j,omp_get_thread_num());

}

}

int k;

#pragma omp_parallel num_threads(3)
{

#pragma omp for schedule(dynamic,10)
for(k=0;k<100;k++)
{
printf("\nIteration %d run by thread  %d",k,omp_get_thread_num());

}

}



/*
No Wait Clause:
parallised for loop - There will implecit barrier in the for loop ,some threads that finished the job will wait all other to complete the loop.
If we avoid that such type of barrier, We use no wait clause to make this no wait to happen. 

#pragma omp section (3) nowait 
{

  #pragma omp section  
  { 

  } 

  #pragma omp section    
  {

  }
  #pragma omp section 
  {

  }
Any Synchronisation Issue : We solve it and make a proper Execution before going to serial code.
}

Intel vtune Performance Analyser : Which core - thread involved ....

*/

return 0;
}


