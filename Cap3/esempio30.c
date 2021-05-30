#include <stdio.h>
#include <unistd.h> 
#include <sys/wait.h> // setpgid . c
void main()
{
            //printf("%d FatherID %d\n", getpid(), getpgid(0));
    int isChild = !fork(); // new child
            //printf("%d isChild %d\n", isChild, getpid());
    printf("PID %d GID %d\n", getpid(), getpgid(0));
    if (isChild)
    {
        isChild = !fork(); // new child
            //printf("%d isChildNew %d\n", isChild, getpid());
        if (!isChild)
            setpgid(0, getpid()); // Become group leader
        fork();                   // new child
        printf("PID %d GID %d\n", getpid(), getpgid(0));
    }
            //printf("waiting\n");
    while (wait(NULL) > 0);
}