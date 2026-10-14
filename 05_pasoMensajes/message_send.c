#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MSGSZ 128

typedef struct msgbuf
{
    long mtype;
    char mtext[MSGSZ];
} message_buf;

int main()
{
    int msqid;
    key_t key = 1234;
    message_buf sbuf;

    if ((msqid = msgget(key, IPC_CREAT | 0666)) < 0)
    {
        perror("msgget");
        exit(1);
    }

    sbuf.mtype = 1;
    strcpy(sbuf.mtext, "Are you hearing me?");

    if (msgsnd(msqid, &sbuf, strlen(sbuf.mtext) + 1, IPC_NOWAIT) < 0)
    {
        perror("msgsnd");
        exit(1);
    }

    printf("Mensaje enviado con exito.\n");
    return 0;
}
