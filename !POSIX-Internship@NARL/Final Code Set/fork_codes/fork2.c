#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

void DoSomeWorkFunction(void)
{
const int NUM_Times = 5;

for(int i=0; i< NUM_Times ;i++)
{
sleep(rand() % 5);
printf("Yes..!!! I am done with pass %d\n",i);
}

}


int main(int argc,char *argv[])
{
printf("Present Linux Process number is %d\n", (int) getpid());

pid_t pid = fork();
printf("Process returned with PID: %d\n", (int) pid);


if (pid < 0)
{
perror("Fork Failed..!!");
}
else if (pid == 0)
{ 
printf("I am Child with PID: %d\n", (int) getpid());
//sleep(5);
DoSomeWorkFunction();
printf("Child is exiting....\n");
exit(0);
}
else
{
printf("I am Parent with PID: %d\n", (int) getpid());
}

printf("All outside code is Parent\n");
printf("I am Parent and I am waiting for the child to exit...\n");
wait(NULL);
printf("Parent is Exiting ...!!!\n");

return 0;
}
