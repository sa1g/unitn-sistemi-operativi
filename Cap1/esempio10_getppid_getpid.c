#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main(void)
{
    pid_t process_id;         // variable to store calling function 's process id
    pid_t p_process_id;       // variable to store parent function 's process id
    process_id = getpid();    // getpid () - will return process id of calling function
    p_process_id = getppid(); // getppid () - will return process id of parent function
    // printing the process ids
    printf("The process id :%d \n", process_id);
    printf("The process id of parent function :%d\n", p_process_id);
    return 0;
}
/*
OUTPUT :
The process id : 31120
The process id of parent function : 31119
*/