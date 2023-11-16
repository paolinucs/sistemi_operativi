/**Esercizio 1:
 * Scrivere un programma in C che utilizzi due thread e un semaforo per garantire che il secondo thread inizi l'esecuzione solo dopo
 * che il primo thread abbia completato la sua esecuzione
 * **/

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>


sem_t mySemaphore;

void* firstThreadExecution(void* arg){
    printf("First thread operation has been executed.\n");
    sem_post(&mySemaphore);
    pthread_exit(NULL);
}

void* secondThreadExecution(void* arg){
    sem_wait(&mySemaphore);
    printf("Second thread operation has been executed.\n");
    pthread_exit(NULL);
}


int main(){

    pthread_t firstThread, secondThread;
    
    //inizializzazione del semaforo
    sem_init(&mySemaphore,0,0);

    pthread_create(&firstThread,NULL,firstThreadExecution,NULL);
    pthread_create(&secondThread, NULL,secondThreadExecution, NULL);

    pthread_join(firstThread,NULL);
    pthread_join(secondThread,NULL);

    sem_destroy(&mySemaphore);



    return 0;
}