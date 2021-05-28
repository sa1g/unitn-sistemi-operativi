// comando : int system ( const char * string )
#include <stdlib.h> //system.c
#include <stdio.h>
void main()
{
    // / bin / sh -c string
    int outcome = system("echo ciao"); // execute command in shell
    printf("%d \n", outcome);
    outcome = system("if [ [ $PWD < \"ciao\" ] ]; then echo min ; fi ");
    printf("%d \n", outcome);
}