#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h> // fifoWriter . c
    void main(int argc, char *argv[])
{
    int fd;
    char *fifoName = "/tmp/fifo1";
    char str1[80], *str2 = "I'm a writer";
    mkfifo(fifoName, S_IRUSR | S_IWUSR); // Create pipe if doesn 't exist
    fd = open(fifoName, O_WRONLY);       // Open FIFO for write only
    write(fd, str2, strlen(str2) + 1);   // write and close
    close(fd);
    fd = open(fifoName, O_RDONLY); // Open FIFO for Read only
    read(fd, str1, sizeof(str1));  // Read from FIFO
    printf("Reader is writing : %s \n", str1);
    close(fd);
}