/**
 * @file es_D.c
 * @author Paolo Coletta
 * 
 * Implementa una barriera utilizzando semafori. 
 * Hai un insieme di processi che devono raggiungere un punto comune prima di poter procedere.
 * Usa i semafori per garantire che i processi si blocchino e si sincronizzino fino a quando tutti non hanno raggiunto la barriera,
 * quindi consenti loro di procedere.
 */


/**
 * Supponiamo di avere N_PROCESS processi che eseguono una funzione che prende in input un numero intero e lo incrementa fino al
 * raggiungimento di una quantità definita MAX_INCREMENT.
 * Solo quando ognuno dei processi avrà raggiunto tale cifra ognuno di essi scriverà "That's it!"
 * 
 * Per fare ciò ho utilizzato un array di semafori dove ognuno (tranne il primo) guarda lo stato del precendente. Ogni semaforo
 * è relativo ad un singolo processo.
 * 
 * **/

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdint.h> //serve per definire tipi interi con precisione specifica. 

#define N_PROCESS 10
#define MAX_INCREMENT 10

//array di semafori definito globalmente
sem_t mySemaphores[N_PROCESS];



void* increment(void* arg);

int main() {

    //inizializzazione dei semafori, il primo viene inizializzato ad 1 per permettere l'inizio delle esecuzioni
    sem_init(&mySemaphores[0], 0, 1);
    for (int index = 1; index < N_PROCESS; index++) {
        sem_init(&mySemaphores[index], 0, 0);
    }

    //viene creato un array di threads
    pthread_t threads[N_PROCESS];


    for (intptr_t i = 0; i < N_PROCESS; i++) {
        pthread_create(&threads[i], NULL, increment, (void*)i); //vengono creati i thread passando come argomento l'indice del processo
    }

    for (int i = 0; i < N_PROCESS; i++) {
        pthread_join(threads[i], NULL); //viene effettuata la pthread_join su tutti i processi
    }

    //si aspetta che l'ultimo semaforo cambi il suo stato
    sem_wait(&mySemaphores[N_PROCESS - 1]);
    //si stampa la stringa finale
    printf("\n\nThat's it!\n");

    for (int i = 0; i < N_PROCESS; i++) {
        sem_destroy(&mySemaphores[i]);
    }

    return 0;
}

void* increment(void* arg) {
    int nProcess = (intptr_t)arg;

    if (nProcess > 0) {
        sem_wait(&mySemaphores[nProcess - 1]);
    }

    int number = 0;
    for (int counter = 0; counter < MAX_INCREMENT; counter++) {
        number++;
        printf("Processo %d: Numero incrementato a %d\n", nProcess, number);

    }


    
    sem_post(&mySemaphores[nProcess]);
   

    pthread_exit(NULL);
}
