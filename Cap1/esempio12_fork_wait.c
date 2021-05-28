#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h> //fork2.c
int main()
{
    int fid = fork(), wid, st, r; // Generate child (fid), waitId, 
    srand(time(NULL));            // Initialise random
    r = rand() % 256;             // Get random
    if (fid == 0)
    {
        // If it is child
        printf("Child... (%d)\n", r);
        fflush(stdout);
        sleep(3); // Pause execution for 3 seconds
        printf("\tdone!\n ");
        exit(r); // Terminate with random signal
    }
    else
    {
        // If it is parent
        printf("Parent...");
        wid = wait(&st); // wait for ONE child to terminate
        printf("child's id : %d == %d (st=%d)\n", fid, wid, WEXITSTATUS(st));
    }
}   