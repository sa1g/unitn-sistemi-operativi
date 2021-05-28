#include <fcntl.h> // execute with sudo ! // chown . c
#include <unistd.h>
#include <sys/stat.h>
void main()
{
    int fd = open("file.txt", O_RDONLY);
    fchown(fd, 1000, 1000);                             // Change owner to root : root, il proprietario:gruppo
    //chmod("file", S_IRUSR | S_IRGRP | S_IROTH); // Permission to r / r / r 
    chmod("file.txt", 0744); // Permission to rwx / rwx / rwx
    //funziona anche con la notazione numerica (piu semplice). 
}