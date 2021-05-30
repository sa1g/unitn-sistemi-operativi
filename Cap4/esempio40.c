#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h> // uni . c
void main()
{
    int fd[2];
    char buf[50];
    pipe(fd); // Create unnamed pipe
    int p2 = !fork();
    if (p2)
    {
        close(fd[1]);
        int r = read(fd[0], &buf, 50); // Read from pipe
        close(fd[0]);
        printf("Buf : '%s'\n", buf);
    }
    else
    {
        close(fd[0]);
        write(fd[1], "writing", 8); // Writes to pipe
        close(fd[1]);
    }
    while (wait(NULL) > 0);
}