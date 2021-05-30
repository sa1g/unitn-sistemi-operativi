#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h> // kill . c

void myHandler(int sigNum)
{
    printf("[%d] ALARM !\n", getpid());
}

int main()
{
    signal(SIGALRM, myHandler);
    int child = fork();
    if (!child)
    {
        while (1); // this is the child
    }

    printf("[%d] sending alarm to %d in 1s \n", getpid(), child);
    sleep(1);
    kill(child, SIGALRM); // send ALARM, child's handler reacts
            //remember that kill() is used to send alarms.
    printf("[%d] sending SIGTERM to %d in 1s \n", getpid(), child);
    sleep(1);
    kill(child, SIGTERM); // send TERM : default is to terminate
    
    while (wait(NULL) > 0);
}