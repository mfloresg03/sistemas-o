#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFF_SIZE   5       /* total number of slots */
#define NP          3       /* total number of producers */
#define NC          3       /* total number of consumers */
#define NITERS      4       /* number of items produced/consumed */

typedef struct {
    int buf[BUFF_SIZE];   /* shared var */
    int in;               /* buf[in%BUFF_SIZE] is the first empty slot */
    int out;              /* buf[out%BUFF_SIZE] is the first full slot */
    sem_t full;           /* keep track of the number of full spots */
    sem_t empty;          /* keep track of the number of empty spots */
    sem_t mutex;          /* enforce mutual exclusion to shared data */
} sbuf_t;

sbuf_t shared;

void *Producer(void *arg)
{
    int i, item, index;

    index = (int)(size_t)arg;

    for (i = 0; i < NITERS; i++) {

        /* Produce item */
        item = i;   

        /* Prepare to write item to buf */

        /* If there are no empty slots, wait */
        sem_wait(&shared.empty);
        /* If another thread uses the buffer, wait */
        sem_wait(&shared.mutex);
        
        shared.buf[shared.in] = item;
        shared.in = (shared.in + 1) % BUFF_SIZE;
        printf("[P%d] Producing %d ...\n", index, item); 
        fflush(stdout);

        /* Release the buffer */
        sem_post(&shared.mutex);
        /* Increment the number of full slots */
        sem_post(&shared.full);

        /* Interleave producer and consumer execution */
        if (i % 2 == 1) sleep(1);
    }
    return NULL;
}

void *Consumer(void *arg)
{
    int i, item, index;

    index = (int)(size_t)arg;

    for (i = 0; i < NITERS; i++) {

        /* If there are no full slots, wait */
        sem_wait(&shared.full);
        /* If another thread uses the buffer, wait */
        sem_wait(&shared.mutex);

        /* Read item from buf */
        item = shared.buf[shared.out];
        shared.out = (shared.out + 1) % BUFF_SIZE;
        printf("-----> [C%d] consumed %d\n", index, item); 
        fflush(stdout);

        /* Release the buffer */
        sem_post(&shared.mutex);
        /* Increment the number of empty slots */
        sem_post(&shared.empty);

        /* Interleave execution */
        if (i % 2 == 1) sleep(1);
    }
    return NULL;
}

int main()
{
    pthread_t idP[NP], idC[NC];
    int index;

    // Inicializar índices del búfer
    shared.in = 0;
    shared.out = 0;

    // Inicialización de semáforos (Figura 5.13 de Stallings)
    sem_init(&shared.full, 0, 0);
    sem_init(&shared.empty, 0, BUFF_SIZE);
    sem_init(&shared.mutex, 0, 1);

    // Crear hilos productores
    for (index = 0; index < NP; index++)
    {  
       pthread_create(&idP[index], NULL, Producer, (void*)(size_t)index);
    }

    // Crear hilos consumidores
    for (index = 0; index < NC; index++)
    {  
       pthread_create(&idC[index], NULL, Consumer, (void*)(size_t)index);
    }

    // Esperar a que terminen todos los hilos productores
    for (index = 0; index < NP; index++)
    {
       pthread_join(idP[index], NULL);
    }

    // Esperar a que terminen todos los hilos consumidores
    for (index = 0; index < NC; index++)
    {
       pthread_join(idC[index], NULL);
    }

    // Destruir semáforos
    sem_destroy(&shared.full);
    sem_destroy(&shared.empty);
    sem_destroy(&shared.mutex);

    return 0;
}

