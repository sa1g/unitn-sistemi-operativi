#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
void myHandler(int sigNum)
{
    printf(" CTRL + Z \n");
}

void main()
{
    signal(SIGINT, SIG_IGN);    // Ignore signal
    signal(SIGCHLD, SIG_DFL);   // Use default handler
    signal(SIGTSTP, myHandler); // Use myHandler
}