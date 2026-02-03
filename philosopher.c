#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *philosopher(void *arg) {
    int id = *(int*)arg;
    int left = id;
    int right = (id + 1) % N;
    while (1) {
        // think
        
        // pick forks (strategy)
        pthread_mutex_lock(&forks[left]);
        pthread_mutex_lock(&forks[right]);

        // eat
        pthread_mutex_unlock(&forks[right]);
        pthread_mutex_unlock(&forks[left]);
    }

    return NULL;
}