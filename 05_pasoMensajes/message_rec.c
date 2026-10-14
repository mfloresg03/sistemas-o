#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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
    message_buf rbuf;

    if ((msqid = msgget(key, 0666)) < 0)
    {
        perror("Error en msgget (¿ejecutaste primero el emisor?)");
        exit(1);
    }

    printf("Esperando mensaje en la cola %d...\n", msqid);

    if (msgrcv(msqid, &rbuf, MSGSZ, 1, 0) < 0)
    {
        perror("Error en msgrcv");
        exit(1);
    }

    printf("Mensaje recibido: %s\n", rbuf.mtext);
    return 0;
}
