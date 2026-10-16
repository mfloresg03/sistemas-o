#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MSGSZ 128

typedef struct msgbuf {
    long mtype;
    int client_id;
    char mtext[MSGSZ];
} message_buf;

int main() {
    int msqid;
    key_t key = 1234;
    message_buf sbuf, rbuf;

    if ((msqid = msgget(key, 0666)) < 0) {
        perror("msgget");
        exit(1);
    }

    // Enviar peticion al servidor en mtype = 1
    sbuf.mtype = 1;
    sbuf.client_id = 1;
    strcpy(sbuf.mtext, "Peticion desde Cliente 1");

    if (msgsnd(msqid, &sbuf, sizeof(message_buf) - sizeof(long), IPC_NOWAIT) < 0) {
        perror("msgsnd");
        exit(1);
    }
    printf("Cliente 1 envio peticion al servidor...\n");

    // Recibir respuesta exclusivamente en mtype = 10 (Canal Privado 1)
    if (msgrcv(msqid, &rbuf, sizeof(message_buf) - sizeof(long), 10, 0) < 0) {
        perror("msgrcv");
        exit(1);
    }

    printf("Cliente 1 recibio respuesta privada: '%s'\n", rbuf.mtext);

    return 0;
}
