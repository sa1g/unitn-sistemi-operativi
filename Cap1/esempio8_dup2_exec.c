#include <stdio.h> // execvpDup.c
#include <fcntl.h>
#include <unistd.h>

void main()
{
    int outfile = open("/tmp/out.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    dup2(outfile, 1);                         // copy outfile to FD 1
    char *argv[] = {"./time.out", NULL}; // time . out
    execvp(argv[0], argv);                    // Replace current process
}