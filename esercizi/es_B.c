/**
 * @file es_B.c
 * @author Paolo Coletta
 * Implementa un programma in C che simula il problema del produttore-consuatore utilizzando semafori per la sincronizzazione dei thread produttore
 * e consumatore
 */

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t mySemaphore;

void* threadProducer(void* arg);
void* threadConsumer(void* arg);
void manufacture();
void buyAndConsume();

int main(){

    pthread_t threadP, threadC;
    sem_init(&mySemaphore,0,0);

    pthread_create(&threadP,NULL,threadProducer,NULL);
    pthread_create(&threadC,NULL,threadConsumer,NULL);


    pthread_join(threadP,NULL);
    pthread_join(threadC,NULL);

    sem_destroy(&mySemaphore);


    return 0;
}

void manufacture(){
    printf("Manufacturing...\n\nManufacturing completed and product sold..\n");
}

void buyAndConsume(){
    printf("Buying product...\n\nProduct bought and consuming it.\n\n");
}

void* threadProducer(void* arg){
    manufacture();
    sem_post(&mySemaphore);
    pthread_exit(NULL);
}

void* threadConsumer(void* arg){
    sem_wait(&mySemaphore);
    buyAndConsume();
    pthread_exit(NULL);
}