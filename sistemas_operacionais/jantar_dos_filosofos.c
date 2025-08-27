#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>

#define self (i + 5 - 1) % 5
#define left i
#define right i + 1 % 5
#define range rand() % 1000000

// sem_t semphi[5];
sem_t sem[5];
sem_t s;
// sem_t semforks[5];

void wait(){
    int c = 0, n = range;
    while(c < n) c++;
}

void take(int i){
    int l=0, r=0;
    sem_wait(&s);
    while(l && r){
        sem_getvalue(&sem[left], &l);       
        sem_getvalue(&sem[left], &r);
    }
        
    sem_post(&s);
}

void think(int i){
    printf("Filósofo %c está pensando...\n", 'A' + i);
    wait();
    printf("Filósofo %c terminou de pensar\n", 'A' + i);
}

void *philosopher(void *pi){
    int i = (int) pi;
    think(i);
    printf("Filósofo %c está com fome\n", 'A' + i);
    take(i);
    return NULL;
}

int main(){
    printf("%d\n", range);

    // Inicia os semáforos 
    sem_init(&s, 0, 1);
    for(int i=0; i<5; i++){
        sem_init(&sem[i], 0, 1);
        // sem_init(&semphi[i], 0, 1);
        // sem_init(&semforks[i], 0, 1);
    }

    // Cria as threads, executa os filósofos e junta as threads
    pthread_t threads[5];
    for(int i=0; i<5; i++)
        pthread_create(&threads[i], NULL, philosopher, i);
    for(int i=0; i<5; i++)
        pthread_join(threads[i], NULL);
    
    // Destrói os semáforos 
    for(int i=0; i<5; i++){
        sem_destroy(&semphi[i]);
        sem_destroy(&semforks[i]);
    }
    return 0;
}