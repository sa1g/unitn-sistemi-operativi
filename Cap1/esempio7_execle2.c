#include <stdio.h> // execle2 . out
#include <stdlib.h>
void main(int argc, char **argv)
{
    printf("This is execv2 with par : %s and %s. CIAO =%s \n", argv[0], argv[1], getenv("CIAO"));
}