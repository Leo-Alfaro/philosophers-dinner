#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// import threads
#include <pthread.h>

// import time counter
#include <time.h>

int philosopher(void *arg) {
    // create a mutex to ensure right count
    pthread_mutex_t counterMutex;
    pthread_mutex_init(&counterMutex, null);

    // counter
    int soupEatenCounter = 0;

    int id = *(int*)arg;
    int left = id;
    int right = (id + 1) % N;

    while (1) {
        // picks left forks
        pthread_mutex_lock(&forks[left]);

        // ensure deadlock happens
        sleep(1000);

        // picks right forks 
        pthread_mutex_lock(&forks[right]);


        // eat
        pthread_mutex_lock(&counterMutex);
        soupEatenCounter++;
        pthread_mutex_unlock(&counterMutex);
        
        // unlock forks
        pthread_mutex_unlock(&forks[right]);
        pthread_mutex_unlock(&forks[left]);
    }

    pthread_mutex_destroy(&counterMutex);
    return soupEatenCounter;
}