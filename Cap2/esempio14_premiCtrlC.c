#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void sighandler(int signum)
{
    printf(" Caught signal %d , coming out ...\n ", signum);
    exit(1);
}

int main()
{
    signal(SIGINT, sighandler);
    while (1)
    {
        printf(" Going to sleep for a second ...\n ");
        sleep(1);
    }
    return (0);
}

/*
OUTPUT:
    Going to sleep for a second...
    Going to sleep for a second...
    Going to sleep for a second...
    Going to sleep for a second...
    Going to sleep for a second...
    Caught signal 2, coming out...
*/