#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include <pthread.h>

// global vars
extern int N; 
extern volatile int programa_rodando;
extern int soupEaten;
extern double waitingTime;
extern pthread_mutex_t *forks;
extern pthread_mutex_t counterMutex;
extern pthread_mutex_t waitTimeMutex;

// philosoher function
void* philosopher(void *arg);

#endif
