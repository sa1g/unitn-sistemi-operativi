#include <signal.h> //sigSet.c
int main()
{
    sigset_t mod, old;
    sigfillset(&mod);           // Add all signals to the blocked list
    sigemptyset(&mod);          // Remove all signals from blocked list
    sigaddset(&mod, SIGALRM);   // Add SIGALRM to blocked list
    sigismember(&mod, SIGALRM); // is SIGALRM in blocked list ?
    sigdelset(&mod, SIGALRM);   // Remove SIGALRM from blocked list
    // Update the current mask with the signals in ' mod '
    sigprocmask(SIG_BLOCK, &mod, &old);
}

/*
$ gcc sigprocmask.c -o sigprocmask.out
$ ./sigprocmask.out
# On new window/terminal
$ kill -10 <PID> # ok
$ kill -10 <PID> # blocked
*/