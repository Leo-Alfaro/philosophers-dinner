#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include <pthread.h>

extern int N; 
extern pthread_mutex_t *forks;

void *philosopher(void *arg);

#endif