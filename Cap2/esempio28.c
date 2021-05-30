#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h> // sigaction3 . c
void handler(int signo)
{
    printf("signal %d received \n", getpid());
    sleep(2);
    printf("Signal done \n");
}
int main()
{
    printf("Process id: %d \n", getpid());
    struct sigaction sa;
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sigaddset(&sa.sa_mask, SIGUSR2); // Block SIGUSR2 in handler
    sigaction(SIGUSR1, &sa, NULL);
    while (1);
}
/*
$ ./ sigaction3 . out
# On new window / terminal
$ kill -10 <PID > ; sleep 1
&& kill -12 <PID >
*/