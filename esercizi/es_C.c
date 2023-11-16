/**
 * @file es_C.c
 * @author Paolo Coletta
 * Scrivi un programma in C che garantisce l'alternanza tra due thread, stampando "Ping" e "Pong" in ordine.
 */

#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include <semaphore.h>
#define MAX_COUNT 10

sem_t pingPongSemaphore;
bool isPingTurn = true;

void* ping(void* arg);
void* pong(void* arg);

int main() {
    sem_init(&pingPongSemaphore, 0, 1);

    pthread_t pingThread, pongThread;

    pthread_create(&pingThread, NULL, ping, NULL);
    pthread_create(&pongThread, NULL, pong, NULL);

    pthread_join(pingThread, NULL);
    pthread_join(pongThread, NULL);

    sem_destroy(&pingPongSemaphore);

    return 0;
}

void* ping(void* arg) {
    for (int counter = 0; counter < MAX_COUNT; ++counter) {
        sem_wait(&pingPongSemaphore);

        //controllo della variabile booleana isPingTurn
        while (!isPingTurn) {
            sem_post(&pingPongSemaphore);
            sem_wait(&pingPongSemaphore);
        }

        printf("Ping..");
        isPingTurn = false; //imposta isPingTurn su false per indicare che è il turno di Pong
        sem_post(&pingPongSemaphore);
    }
    pthread_exit(NULL);
}

void* pong(void* arg) {
    for (int counter = 0; counter < MAX_COUNT; ++counter) {
        sem_wait(&pingPongSemaphore);

        while (isPingTurn) {
            sem_post(&pingPongSemaphore);
            sem_wait(&pingPongSemaphore);
        }

        printf("Pong!\n");
        isPingTurn = true;
        sem_post(&pingPongSemaphore);
    }
    pthread_exit(NULL);
}
