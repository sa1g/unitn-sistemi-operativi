#include <sys/types.h> 
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h> // ipc . c
struct msg_buffer
{
    long mtype;
    char mtext[100];
} msgp, msgp2;
void main()
{
    msgp.mtype = 20;
    strcpy(msgp.mtext, "This is a message");
    key_t queue1Key = ftok("/tmp/unique", 1);
    int queueId = msgget(queue1Key, 0777 | IPC_CREAT | IPC_EXCL);
    int esito = msgsnd(queueId, &msgp, sizeof(msgp.mtext), 0);
    esito = msgrcv(queueId, &msgp2, sizeof(msgp2.mtext), 20, 0);
}