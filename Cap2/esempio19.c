#include <signal.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // bash . c

void myHandler(int sigNum)
{
    printf("[%d] ALARM!\n", getpid());
    exit(0);
}
int main()
{
    signal(SIGALRM, myHandler);
    printf("I am %d \n", getpid());
    while (1);
}

/*
$ gcc bash . c -o bash . out
$ ./ bash . out
# On new window / terminal
$ kill -14 <PID >

in pratica si esegue il programma che stampa il proprio PID e
continua ad eseguire; lo si uccide col comando kill -14 <PID> da
terminale

DA MAN: significato di kill -14 
SIGALRM P1990 Term Timer signal from alarm (2)
*/