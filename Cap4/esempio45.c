#include <sys/stat.h> 
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h> // fifoReader . c
    void main(int argc, char *argv[])
{
    int fd;
    char *fifoName = "/tmp/fifo1";
    mkfifo(fifoName, S_IRUSR | S_IWUSR); // Create pipe if doesn ’t exist
    char str1[80], *str2 = "I'm a reader";
    fd = open(fifoName, O_RDONLY); // Open FIFO for read only
    read(fd, str1, 80);            // read from FIFO and close it
    close(fd);
    printf("Writer is writing : %s \n", str1);
    fd = open(fifoName, O_WRONLY);     // Open FIFO for write only
    write(fd, str2, strlen(str2) + 1); // Write and close
    close(fd);
}