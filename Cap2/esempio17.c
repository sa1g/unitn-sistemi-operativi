#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void myHandler(int sigNum)
{
    printf("Child terminated !\n ");
}
// child . c
int main()
{
    signal(SIGCHLD, myHandler);
    int child = fork();
        
    if (!&child)
    {
        return 0; // terminate child
    }
    while (wait(NULL) > 0);
}