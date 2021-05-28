#include <unistd.h> 
#include <stdio.h>
#include <fcntl.h>
void main()
{
    char buf[50];
    int fd = open("file.txt", O_RDWR); // file exists
    read(fd, buf, 50);
    printf("Content: %s \n", buf);
    int cpy = dup(fd);                 // Create cpy of file descriptor
    dup2(cpy, 22);                     // Copy cpy to descriptor 22( close 22 if opened )
    lseek(cpy, 0, SEEK_SET);           // move I / O on all 3 file descriptors !
    write(22, " This is a file ", 15); // Write starting from 0 - pos }
}