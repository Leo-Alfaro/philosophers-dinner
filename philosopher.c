#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// import global vars
#include "philosopher.h"

// import threads
#include <pthread.h>

void *philosopher(void *arg) {

    // define forks
    int id = *(int*)arg;
    int left = id;
    int right = (id + 1) % N;

    // loop until thread is destroyed
    while (1) {
        // picks left forks
        pthread_mutex_lock(&forks[left]);

        // ensure deadlock happens - ensure fork is being using when other try to use
        sleep(1);

        // picks right forks 
        pthread_mutex_lock(&forks[right]);

        // eat
        pthread_mutex_lock(&counterMutex);
        soupEaten++;
        pthread_mutex_unlock(&counterMutex);
        
        // unlock forks
        pthread_mutex_unlock(&forks[right]);
        pthread_mutex_unlock(&forks[left]);
    }

    return NULL;
}