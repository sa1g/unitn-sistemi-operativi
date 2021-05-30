#include <sys/stat.h> 
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h> //fifo.c
void main()
{
    char *fifoName = "/tmp/fifo1";
    mkfifo(fifoName, S_IRUSR | S_IWUSR);
    // Create pipe if doesn 't exist
    perror("Created?");
    if (fork() == 0)
    {
        open(fifoName, O_RDONLY); // Open pipe in read only ... stuck !
        printf("Open read \n");
    }
    else
    {
        sleep(1);
        open(fifoName, O_WRONLY); // Open pipe in write only
        printf("Open write \n");
    }
}