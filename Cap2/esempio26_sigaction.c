#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h> // sigaction . c
void handler(int signo)
{
    printf("signal received \n");
}
int main()
{
    struct sigaction sa;      // Define sigaction struct
    sa.sa_handler = handler;  // Assign handler to struct field
    sigemptyset(&sa.sa_mask); // Define an empty mask
    sigaction(SIGUSR1, &sa, NULL);
    kill(getpid(), SIGUSR1);
}