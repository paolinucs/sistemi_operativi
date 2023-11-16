# Utilizzo dei Semafori in C con pthread

I semafori sono strumenti di sincronizzazione utilizzati per gestire l'accesso concorrente a risorse condivise da più thread. In C, la libreria `semaphore.h` fornisce le funzioni per utilizzare i semafori. 

## Funzionamento dei Semafori

Un semaforo può essere considerato come un contatore intero che può essere modificato solo da due operazioni atomiche: `wait` (decremento) e `post` (incremento).

- `wait`: Decrementa il valore del semaforo. Se il valore è maggiore di zero, il thread continua l'esecuzione. Altrimenti, se il valore è zero, il thread viene messo in attesa.
- `post`: Incrementa il valore del semaforo, eventualmente risvegliando un thread in attesa.

## Integrazione con pthread

Per utilizzare i semafori con i thread pthread, è necessario includere le librerie necessarie e gestire correttamente i semafori all'interno dei thread.

### Inizializzazione dei Semafori

```c
    #include <pthread.h>
    #include <semaphore.h>
    #include <stdio.h>

    sem_t semaphore;

    void* thread_function(void* arg) {
        // Blocca il semaforo
        sem_wait(&semaphore);

        // Sezione critica
        printf("Inizio sezione critica\n");
        // ... operazioni critiche ...
        printf("Fine sezione critica\n");

        // Sblocca il semaforo
        sem_post(&semaphore);

        return NULL;
    }

    int main() {
        // Inizializzazione del semaforo
        sem_init(&semaphore, 0, 1);

        pthread_t thread_id;
        pthread_create(&thread_id, NULL, thread_function, NULL);

        // Attendi il completamento del thread
        pthread_join(thread_id, NULL);

        // Distruggi il semaforo
        sem_destroy(&semaphore);

        return 0;
    }

```


### Operazioni sui Semafori

- `sem_init (sem_t *sem, int pshared, unsigned int value)`: Inizializza il semaforo sem con il valore value. Se pshared è 0, il semaforo è condiviso tra i thread del processo corrente.
    
- `sem_wait(sem_t *sem)`: Decrementa il valore del semaforo. Se il valore è zero, il thread viene messo in attesa.
    
- `sem_post(sem_t *sem)`: Incrementa il valore del semaforo, eventualmente risvegliando un thread in attesa.
    
- `sem_destroy(sem_t *sem)`: Distrugge il semaforo.




