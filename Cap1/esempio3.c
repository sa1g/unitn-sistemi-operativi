#include <unistd.h>
#include <stdio.h>
void main()
{
    char s[100]; //array di caratteri su cui scrivere il path
    chdir(" .. "); // Change working dir
    printf(" %s \n ", getcwd(s, 100)); // Print current working dir
}