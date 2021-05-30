#include <stdio.h>
#include <errno.h>
#include <math.h>
int main()
{
    double x;
    double value;
    x = 2.000000;
    value = log(x);
    if (errno == ERANGE)
    {
        printf("Log (%f) is out of range \n", x);
    }
    else
    {
        printf("Log (%f) = % f \n", x, value);
    }
    x = 1.000000;
    value = log(x);
    if (errno == ERANGE)
    {
        printf("Log (%f) is out of range \n", x);
    }
    else
    {
        printf(" Log (%f) = %f \n", x, value);
    }
    x = 0.000000;
    value = log(x);
    if (errno == ERANGE)
    {
        printf(" Log (% f ) is out of range \n", x);
    }
    else
    {
        printf(" Log (%f) = %f \n", x, value);
    }
    return 0;
}
/*
OUTPUT :
Log (2.000000) = 0.693147
Log (1.000000) = 0.000000
Log (0.000000) is out of range
*/