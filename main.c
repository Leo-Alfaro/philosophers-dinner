#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
// import threads
#include <pthread.h>
// import time library
#include <time.h>

// import philosopher function
#include "philosopher.h"

// philosophers
int N; 

// soupEaten
int soupEaten;

// total time spend for all philosphers while waiting
double waitingTime;

// forks
pthread_mutex_t *forks;

// create a mutex to ensure right count
pthread_mutex_t counterMutex;

// create a mutex to sum all waiting times
pthread_mutex_t waitTimeMutex;

// flag to control the while loop
volatile int programa_rodando = 1;

int main(int argc, char* argv[]){

    // gets arguments
    N = atoi(argv[1]);

    // alloc memory
    forks = malloc(sizeof(pthread_mutex_t) * N);
    pthread_t *philosopherThread = malloc(sizeof(pthread_t) * N);
    int *philosopherId = malloc(sizeof(int) * N);

    // init mutexs
    pthread_mutex_init(&counterMutex, NULL);
    pthread_mutex_init(&waitTimeMutex, NULL);

    // init in separate for's to ensure all thread init together
    for(int i = 0; i < N; i++){
        pthread_mutex_init((forks + i), NULL);
        *(philosopherId + i) = i;
    }

    for(int i = 0; i < N; i++){
        pthread_create((philosopherThread + i), NULL, philosopher, (philosopherId + i));
    }

    // kill deadlock after 10 seconds
    sleep(10);

    programa_rodando = 0;
    // ensure that all the threads are gone to end together 
    for(int i = 0; i < N; i++){
        pthread_join(philosopherThread[i], NULL);
    }

    printf("Total de sopas: %d\n", soupEaten);
    printf("Desempenho (sopas por segundo): %.2f\n", (soupEaten/10.0));
    printf("Tempo de espera médio: %f", (soupEaten ? waitingTime/soupEaten : 0.0));

    pthread_mutex_destroy(&counterMutex);
    pthread_mutex_destroy(&waitTimeMutex);
    for(int i = 0; i < N; i++){
        pthread_mutex_destroy(&forks[i]);
    }

    // clean to avoid memory leak
    free(forks);
    free(philosopherThread);
    free(philosopherId);

    return 0;
}
