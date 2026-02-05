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

// forks
pthread_mutex_t *forks;

// create a mutex to ensure right count
pthread_mutex_t counterMutex;

int main(int argc, char* argv[]){

    // gets arguments
    N = atoi(argv[1]);

    // alloc memory
    forks = malloc(sizeof(pthread_mutex_t) * N);
    pthread_t *philosopherThread = malloc(sizeof(pthread_t) * N);
    int *philosopherId = malloc(sizeof(int) * N);

    // init mutexs
    pthread_mutex_init(&counterMutex, NULL);

    // init in separate for's to ensure all thread init together
    for(int i = 0; i < N; i++){
        pthread_mutex_init((forks + i), NULL);
        *(philosopherId + i) = i;
    }

    for(int i = 0; i < N; i++){
        pthread_create((philosopherThread + i), NULL, philosopher, (philosopherId + i));
    }

    // kill deadlock after 15 seconds
    sleep(10);

    // cancel all threads and mutex
    for(int i = 0; i < N; i++){
        pthread_cancel(*(philosopherThread + i));
    }

    printf("%d\n", soupEaten);

    pthread_mutex_destroy(&counterMutex);

    return 0;
}