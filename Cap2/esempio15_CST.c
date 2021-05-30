#include <signal.h> // sigCST . c
#include <stdio.h>

void myHandler(int sigNum)
{
    printf("CTRL + Z\n");
    exit(2);
}

int main()
{
    signal(SIGTSTP, myHandler);
    while (1);
}

/*
$ gcc sig[CST|DFL|IGN].c -o sig.out
$ ./sig.out
$ <CTRL+Z>
*/