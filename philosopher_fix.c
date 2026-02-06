#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

// import global vars
#include "philosopher.h"

// import threads
#include <pthread.h>

clock_t start, end;

void *philosopher(void *arg) {

    // define forks
    int id = *(int*)arg;
    int left = id;
    int right = (id + 1) % N;

    // loop until thread is destroyed
    while (1) {

        start = clock();

        // forks
        if (id % 2 == 0) {
            // even philosopher (left first)
            pthread_mutex_lock(&forks[left]);
            pthread_mutex_lock(&forks[right]);
        } else {
            // odd philosopher (right first)
            pthread_mutex_lock(&forks[right]);
            pthread_mutex_lock(&forks[left]);
        }

        end = clock();

        pthread_mutex_lock(&waitTimeMutex);
        waitingTime += ((double)(end - start)) / CLOCKS_PER_SEC;
        pthread_mutex_unlock(&waitTimeMutex);

        // eat
        pthread_mutex_lock(&counterMutex);
        soupEaten++;
        pthread_mutex_unlock(&counterMutex);
        
        // unlock forks (inverse logic)
        if (id % 2 == 0) {
            pthread_mutex_unlock(&forks[right]);
            pthread_mutex_unlock(&forks[left]);
        } else {
            pthread_mutex_unlock(&forks[left]);
            pthread_mutex_unlock(&forks[right]);
        }

    }

    pthread_mutex_destroy(&counterMutex);
    return NULL;
}