#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include <pthread.h>

// global vars
extern int N; 
extern int soupEaten;
extern pthread_mutex_t *forks;
extern pthread_mutex_t counterMutex;

// philosoher function
void* philosopher(void *arg);

#endif