#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h> // ipcCreation . c
void main()
{
    remove("/tmp/unique");                        // Remove file
    key_t queue1Key = ftok("/tmp/unique", 1);     // Get unique key -> fail
    creat("/tmp/unique", 0777);                   // Create file
    queue1Key = ftok("/tmp/unique", 1);           // Get unique key -> ok
    int queueId = msgget(queue1Key, 0777 | IPC_CREAT); // Create queue -> ok
    queueId = msgget(queue1Key, 0777);                 // Get queue -> ok
    msgctl(queue1Key, IPC_RMID, NULL);                 // Remove non existing queue -> fail
    msgctl(queueId, IPC_RMID, NULL);                   // Remove queue -> ok
    queueId = msgget(queue1Key, 0777);                 // Get non existing queue -> fail
    queueId = msgget(queue1Key, 0777 | IPC_CREAT);     // Create queue -> ok
    queueId = msgget(queue1Key, 0777 | IPC_CREAT);     // Get queue -> ok
    queueId = msgget(queue1Key, 0777 | IPC_CREAT | IPC_EXCL);
    /* Create already existing queue*/
}