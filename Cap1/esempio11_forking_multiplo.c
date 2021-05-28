#include <stdio.h> //fork1.c
#include <unistd.h>
int main()
{
    fork();
    fork();
    fork();
    printf("hello \n");
    return 0;
}