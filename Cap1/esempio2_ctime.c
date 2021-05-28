#include <stdlib.h>
#include <stdio.h>
#include <time.h>
int main()
{
    time_t curtime;     //variaible temporale
    time(&curtime);     //Return the current time and put it in *TIMER if TIMER is not NULL.
    printf("Tempo attuale = %s ", ctime(&curtime));
    return (0);
}