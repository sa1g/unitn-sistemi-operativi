// input . out
#include <stdio.h>
#include <unistd.h>
void main()
{
    char msg[50];
    int n = 3;
    while ((n--) > 0)
    {
        int c = read(0, msg, 50);
        if (c > 0)
        {
            msg[c] = 0;
            fprintf(stdout, "Read : '%s' (%d)\n", msg, c);
        };
    };
};
// $ ./output.out | ./input.out