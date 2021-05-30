// sigpending . c
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
sigset_t mod, pen;

void handler(int signo)
{
    printf("SIGUSR1 received \n");
    sigpending(&pen);
    if (!sigismember(&pen, SIGUSR1))
        printf("SIGUSR1 not pending \n");
    exit(0);
}

int main()
{
    signal(SIGUSR1, handler);
    sigemptyset(&mod);
    sigaddset(&mod, SIGUSR1);
    sigprocmask(SIG_BLOCK, &mod, NULL);
    kill(getpid(), SIGUSR1); // sent but it 's blocked ...
    sigpending(&pen);
    if (sigismember(&pen, SIGUSR1))
        printf("SIGUSR1 pending \n");
    sigprocmask(SIG_UNBLOCK, &mod, NULL);
    while (1);
}