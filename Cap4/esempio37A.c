// output . out
#include <stdio.h>
#include <unistd.h>
void main()
{
    for (int i = 0; i < 3; i++)
    {
        sleep(2);
        fprintf(stdout, "Written in buffer");
        fflush(stdout);
    };
};

