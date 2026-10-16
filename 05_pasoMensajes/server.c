#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MSGSZ 128

typedef struct msgbuf {
    long mtype;
    int client_id; // Identificador del cliente (1 o 2)
    char mtext[MSGSZ];
} message_buf;

int main() {
    int msqid;
    key_t key = 1234;
    message_buf rbuf, sbuf;

    // Crear la cola de mensajes
    if ((msqid = msgget(key, IPC_CREAT | 0666)) < 0) {
        perror("msgget");
        exit(1);
    }

    printf("Servidor iniciado. Esperando peticiones en la cola...\n");

    // Procesa peticiones de ambos clientes
    for (int i = 0; i < 2; i++) {
        // Recibe mensaje genérico a la escucha en mtype = 1
        if (msgrcv(msqid, &rbuf, sizeof(message_buf) - sizeof(long), 1, 0) < 0) {
            perror("msgrcv");
            exit(1);
        }

        printf("Servidor recibio mensaje de Cliente %d: '%s'\n", rbuf.client_id, rbuf.mtext);

        // Define el canal privado de respuesta según el client_id
        if (rbuf.client_id == 1) {
            sbuf.mtype = 10; // Canal privado Cliente 1
            strcpy(sbuf.mtext, "Hola Cliente 1, esta es tu respuesta privada");
        } else if (rbuf.client_id == 2) {
            sbuf.mtype = 20; // Canal privado Cliente 2
            strcpy(sbuf.mtext, "Hola Cliente 2, esta es tu respuesta privada");
        }

        // Envía la respuesta dirigida al mtype privado
        if (msgsnd(msqid, &sbuf, sizeof(message_buf) - sizeof(long), IPC_NOWAIT) < 0) {
            perror("msgsnd");
            exit(1);
        }
        printf("Servidor respondio al Cliente %d en mtype %ld\n", rbuf.client_id, sbuf.mtype);
    }

    return 0;
}
