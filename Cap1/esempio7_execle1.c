#include <unistd.h> // execle1 . out
#include <stdio.h>
void main()
{
    char *env[] = {"CIAO = hello world", NULL};
    execle("./esempio7_execle2", "par1", "par2", NULL, env); // sostituisce il processo attuale passando env (array) con CIAO = hello
    printf (" This is execle1 n");
}