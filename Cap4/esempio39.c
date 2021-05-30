#include <stdio.h> // readPipe . c
#include <unistd.h>
void main()
{
    int fd[2];
    char buf[50];
    int esito = pipe(fd); // Create unnamed pipe
    if (esito == 0)
    {
        write(fd[1], "writing", 8);  // Writes to pipe
        int r = read(fd[0], &buf, 50); // Read from pipe
        printf("Last read %d. Received : '%s'\n", r, buf);
        // close ( fd [1]); // hangs when commented
        r = read(fd[0], &buf, 50); // Read from pipe
        printf("Last read %d. Received : '%s'\n", r, buf);
    }
}