#include <signal.h>
#include <unistd.h>
#include <stdio.h> // pause . c

void myHandler(int sigNum)
{
    printf("Continue!\n");
}

int main()
{
    printf("%d\n", getpid());
    signal(SIGCONT, myHandler); //Alarm clock
    signal(SIGUSR1, myHandler); //Continue!
    pause();
}

/*
$ gcc pause . c -o pause . out
$ ./ pause . out
# On new window / terminal
$ kill -18/ -10 <PID >
*/