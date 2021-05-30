#include <signal.h>
#include <unistd.h>
#include <stdio.h> //sigprocmask.c
sigset_t mod, old;
int i = 0;
void myHandler(int signo)
{
    printf("signal received \n");
    i++;
}
int main()
{
    printf("my id = %d \n", getpid());
    signal(10, myHandler);
    sigemptyset(&mod);
    sigaddset(&mod, SIGUSR1);
    while (1)
        if (i == 1)
            sigprocmask(SIG_BLOCK, &mod, &old);
}

/*
$ gcc sigprocmask . c -o sigprocmask . out
$ ./ sigprocmask . out
# On new window / terminal
$ kill -10 <PID > # ok
$ kill -10 <PID > # blocked
*/