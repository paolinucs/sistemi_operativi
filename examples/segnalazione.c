#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t semaphore;


// Le funzioni create per essere eseguite da pthread devono avere un tipo di ritorno void*
// per poter essere utilizzate correttamente come argomento per la creazione dei thread.
// In realtà, void* viene spesso utilizzato in C per passare dati tra funzioni o thread.

// Potresti chiederti: "Perché dobbiamo usare void*?"
// Questo tipo di dato generico consente di passare qualsiasi tipo di dato come argomento
// e di trasformarlo in un puntatore void, un puntatore generico.
// Quando la funzione è eseguita come un thread, potrebbe ricevere un puntatore a dati specifici
// tramite il parametro arg e restituire eventualmente un puntatore a un dato specifico, se necessario.
void* threadA_fun(void* arg){
    printf("Thread A legge una riga da un file (a1)\n");
    //sem_post viene utilizzato per indicare al semaforo che l'operazione è stata completata
    sem_post(&semaphore);
    pthread_exit(NULL);
}

void* threadB_fun(void* arg){
    sem_wait(&semaphore);
    printf("Thread B visualizza la riga a video (b1)\n");
    pthread_exit(NULL);
}


int main(){

    pthread_t threadA, threadB;

    //Inizializzazione del semaforo
    sem_init(&semaphore,0,0);

    //Creazione dei thread
    pthread_create(&threadA,NULL,threadA_fun,NULL);
    pthread_create(&threadB,NULL,threadB_fun,NULL);

    // pthread_join è una funzione bloccante,
    // il che significa che il thread chiamante (il thread principale in questo caso)
    // attende che il thread specificato completi la sua esecuzione prima di procedere oltre la chiamata
    // pthread_join. Se il thread specificato non termina mai la sua esecuzione,
    // il programma principale rimarrà bloccato in attesa indefinita, situazione nota come deadlock.

    pthread_join(threadA,NULL);
    pthread_join(threadB,NULL);

    sem_destroy(&semaphore);




    return 0;
}