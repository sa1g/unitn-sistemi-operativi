#include <signal.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <stdio.h> // sigaction4 . c

void handler(int signo, siginfo_t *info, void *empty)
{
    printf("Signal received from %d \n", *(info));
}
int main()
{
    struct sigaction sa;
    sa.sa_sigaction = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags |= SA_SIGINFO;   // Use sa_sigaction
    sa.sa_flags |= SA_RESETHAND; // Restore default handler after exiting custom one sigactio
    while (1);
}
/*
$ ./ sigaction4 . out
# On new window / terminal
$ echo $$ ; kill -10 <PID > # custom
$ kill -10 <PID > # default
*/