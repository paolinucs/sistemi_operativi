# Commento esercizio E

Link esercizio: https://github.com/paolinucs/sistemi_operativi/blob/main/esercizi/es_E.c

Per comprendere bene il funzionamento dei semafori consiglio di consultare sia la documentazione scritta da ChatGPT (https://github.com/paolinucs/sistemi_operativi/blob/main/docs/semafori%20in%20C.md) e il video YouTube di Get The Cookie relativo all'argomento.<br>

Questo esercizio l'ho fatto come introduzione ai **semafori contatori**. In breve, a differenza dei semafori binari (che ho utilizzato negli esercizi precedenti), i semafori contatori hanno un vero e proprio contatore interno che può essere incrementato o decrementato grazie alla `sem_wait` e `sem_post` (rispettivamente per decrementare e incrementare).

n.b ho avuto molti grattacapi per implementare il valore massimo di threads da eseguire contemporaneamente, per quello mi sono aiutato con ChatGPT.

### Main

Partiamo dal main():
```c

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
                    
```


Questo può essere visto come il classico main di un problema risolto tramite semafori. Ho inizializzato un semaforo mySemaphore definito globalmente in modo che abbia come valore del contatore il valore massimo dei threads che possono essere eseguiti contemporaneamente.

Successivamente, ho inizializzato una array di 60 threads e grazie a due cicli for li ho sia inizializzati che joinati.

Alla fine dell'esecuzione viene distrutto il semafoto

### funzione doSomething()
```c
    void* doSomething(void* arg){
        while(1){

            printf("Current Active Threads: %d\n",activeThreads);

            if (activeThreads < MAX_VALUE) {
                sem_wait(&mySemaphore);
                activeThreads++;

                printf("Doing something..\n");
                       
                sleep(5); 

                sem_post(&mySemaphore);
                activeThreads--;
                printf("Task completed.\n");
                break;

                sleep(3);
                } else {
                    printf("Semaforo al massimo. In attesa...\n");
                    sleep(10);
                }
                pthread_exit(NULL);
 
                }  
    }

```

La funzione `doSomething()` è l'operazione effettuata dai thread. Inizialmente vengono stampati i thread attivi in base ad una variabile contatore globale dichiarata prima del main del programma. Successivamente viene effettuato un controllo su valore di `activeThreads`.

Viene decrementato il contatore del semaforo e viene incrementato il contatore dei threads impegnati.

Successivamente, viene stampato a schermo "Do something..." e dopo un ritardo di 5 secondi viene effettuata la post del semaforo, incrementando nuovamente il semaforo e successivamente viene decrementato activeThreads.

Infine viene eseguito il `break` del ciclo while nel quale si trovano tutti gli statements.

Nel caso in cui il controllo dovesse fallire, viene mostrato a schermo un messaggio circa la saturazione del semaforo e vengono attesi 10 secondi prima di riprovare.

Il ciclo for infinito da la possibilità a tutti i thread di essere eseguiti correttamente aspettando il loro turno in base al contatore.
