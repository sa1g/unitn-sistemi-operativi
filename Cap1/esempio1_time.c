#include <stdlib.h>
#include <stdio.h>
#include <time.h>
int main()
{
    time_t seconds;
    seconds = time(NULL);
    printf("Ore dal 1 Gennaio 1970 = % ld \n", seconds / 3600);
    return (0);
}