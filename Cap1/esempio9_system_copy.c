// comando : int system ( const char * string )
#include <stdlib.h> //system.c
#include <stdio.h>
void main()
{
    // / bin / sh -c string
    int outcome = system("cd /home/$USER/abadakadabra"); // execute command in shell
    printf("%d \n", outcome);
    outcome = system("mkdir abadakadabra");
    printf("%d \n", outcome);
    outcome = system("rm -rf abadakadabra");
    printf("%d \n", outcome);
    outcome = system("echo $USER");
    printf("%d \n", outcome);
}