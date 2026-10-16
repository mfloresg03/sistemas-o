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
    message_buf sbuf, rbuf;
    size_t buf_length;

    // 1. Acceder a la cola
    if ((msqid = msgget(key, 0666)) < 0)
    {
        perror("msgget");
        exit(1);
    }

    // 2. Recibe el primer mensaje "Are you hearing me?" (mtype = 1)
    if (msgrcv(msqid, &rbuf, MSGSZ, 1, 0) < 0)
    {
        perror("msgrcv (1)");
        exit(1);
    }
    printf("Process 2 recibio: %s\n", rbuf.mtext);

    // 3. Responde "Loud and clear" (mtype = 2)
    sbuf.mtype = 2;
    strcpy(sbuf.mtext, "Loud and clear");
    buf_length = strlen(sbuf.mtext) + 1;

    if (msgsnd(msqid, &sbuf, buf_length, IPC_NOWAIT) < 0)
    {
        perror("msgsnd (2)");
        exit(1);
    }
    printf("Process 2 envio: %s\n", sbuf.mtext);

    // 4. Recibe la replica "I can hear you too" (mtype = 3)
    if (msgrcv(msqid, &rbuf, MSGSZ, 3, 0) < 0)
    {
        perror("msgrcv (3)");
        exit(1);
    }
    printf("Process 2 recibio: %s\n", rbuf.mtext);

    return 0;
}
