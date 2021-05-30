#include <sys/ipc.h>
#include <stdio.h>
#include <sys/msg.h> // persistent . c
void main()
{
    key_t queue1Key = ftok("/tmp/unique", 1);
    int queueId = msgget(queue1Key, 0777 | IPC_CREAT | IPC_EXCL);
    perror("Error :");
}