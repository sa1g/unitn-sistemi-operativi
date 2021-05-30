#include <signal.h>
#include <stdio.h> // return . c

void myHandler(int sigNum) {}

int main()
{   
    printf("DFL : %p \n", signal(SIGINT, SIG_IGN));
    printf("IGN : %p \n", signal(SIGINT, myHandler));
    printf("Custom : %p == %p \n ", signal(SIGINT, SIG_DFL), myHandler);
}