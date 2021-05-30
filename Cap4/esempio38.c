#include <stdio.h>// pipe . c
#include <unistd.h>
void main()
{
    int fd[2];
    int esito = pipe(fd); // Create unnamed pipe
    if (esito == 0)
    {
        write(fd[1], "writing", 8); // Write to pipe using fd [1]
        char buf[50];
        int c = read(fd[0], &buf, 50); // Read from pipe using fd [0]
        printf("Read '%s' (%d)\n", buf, c);
    }
}