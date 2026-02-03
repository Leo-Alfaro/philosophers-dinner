#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include <pthread.h>

extern int N; 
extern pthread_mutex_t *forks;

int philosopher(void *arg);

#endif