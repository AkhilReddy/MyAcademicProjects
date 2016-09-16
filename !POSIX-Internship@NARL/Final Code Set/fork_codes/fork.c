#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>


int main(int argc,char *argv[])
{
printf("Present Linux Process number is %d\n", (int) getpid());

pid_t pid = fork();
printf("Process returned with PID: %d\n", (int) pid);

printf("Linux Process number is %d\n", (int) getpid());

return 0;
}
