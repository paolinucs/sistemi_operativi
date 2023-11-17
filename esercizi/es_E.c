/**
 * Creare un semaforo a conteggio che supporti un numero massimo di permessi e veda l'incremento e il decremento del contatore attraverso le operazioni wait e signal.
 * Suggerimento: Utilizza una variabile contatore e implementa le funzioni wait e signal per gestire l'incremento e il decremento del contatore rispettivamente.
 * Controlla i limiti massimi e minimi del contatore per evitare sovraccarichi o valori negativi.
 */
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX_VALUE 5

sem_t mySemaphore;
int activeThreads;

void* doSomething(void* arg);

int main(){
    sem_init(&mySemaphore, 0, MAX_VALUE);

    pthread_t threads[60];

    for(int index = 0; index < sizeof(threads)/sizeof(pthread_t); index++){
        pthread_create(&threads[index], NULL, doSomething, NULL);
    }

    for(int index = 0; index < sizeof(threads)/sizeof(pthread_t); index++){
        pthread_join(threads[index], NULL);
    }

    sem_destroy(&mySemaphore);

    return 0;
}

void* doSomething(void* arg){
       while(1){

        printf("Current Active Threads: %d\n",activeThreads);

        if (activeThreads < MAX_VALUE) {
            sem_wait(&mySemaphore);
            activeThreads++;

            printf("Doing something..\n");

            // Aggiungi un ritardo prima di rilasciare il semaforo
            sleep(5); // Ritardo di 5 secondi

            sem_post(&mySemaphore);
            activeThreads--;
            printf("Task completed.\n");
            break;

            sleep(3); // Riposa per 3 secondi
        } else {
            printf("Semaforo al massimo. In attesa...\n");
            sleep(10); // Attendi per un breve periodo prima di riprovare
        }
    }
    pthread_exit(NULL);
}
