#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h> // sigaction2 . c
void handler(int signo)
{
    printf("signal %d received \n ", getpid());
    sleep(2);
    printf("Signal done \n");
}
int main()
{
    printf("Process id : %d \n ", getpid());
    struct sigaction sa;
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGUSR1, &sa, NULL);
    while (1)
        ;
}

/*
$ ./ sigaction2 . out
# On new window / terminal
$ kill -10 <PID > ; sleep 1
&& kill -12 <PID >
*/