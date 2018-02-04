//
//  main.cpp
//  ThreadPool
//
//  Created by Gal Argov Sofer on 2/4/18.
//  Copyright © 2018 Gal Argov Sofer. All rights reserved.
//

#include <sys/time.h>

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <assert.h>
#include <iostream>
#include <vector>
#include <time.h>

#include "threadpool.h"
#include "log.h"
//#include "func.h"

// Global variables
int done = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;


// Prototypes
//void *threadpool_thread(void *threadpool);
typedef void*(*function)(void*);

// Functions
void* threadRun(void* arg)
{
    pthread_mutex_lock(&lock);
    pthread_cond_wait(&cond, &lock);
    Log((char*)"threadRun function run");
    printf("threadRun function run\n");
    done++;
    pthread_mutex_unlock(&lock);
    return NULL;
}

void parseLine(unsigned long long * N, unsigned long long * T, unsigned long long * F, unsigned long long * I, const char *argv[]){
    *N = atoi(argv[1]);
    *T = atoi(argv[2]);
    *F = atoi(argv[3]);
    *I = atoi(argv[4]);
}

void* MontePI(void* arg) {
    int * p_niter = (int*)arg;
    int niter = *p_niter;
    double pi = 0;
    int count=0,i;
    double x,y,z;
    
    srand(static_cast<unsigned int>(time(NULL)));

    for ( i=0; i < niter; i++) {
        x = (double)rand()/RAND_MAX;
        y = (double)rand()/RAND_MAX;
        z = x*x+y*y;
        if (z<=1) count++;
    }
    
    pi = count/niter*4;
    pthread_mutex_lock(&lock);
    done++;
    pthread_mutex_unlock(&lock);
    
    return (void *)arg;
}


// Main Application
int main(int argc, const char * argv[]) {
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if (argc != 5) {
        printf("USAGE: ./Main  <NumberOfAvailableThreads> <NumberOfThreadsPerTask> <MaximunNumberOfTasks> <NumberOfIteretaion>\n");
        return 0;
    }

    struct timeval start, end;
    double elapsed;
    gettimeofday(&start, NULL);

    unsigned long long THREAD = 0;    // Number of available threads.
    unsigned long long T = 0;    // Number of threads per task.
    unsigned long long QUEUE = 0;    // Maximun number of tasks.
    unsigned long long I = 0;    // Number of iteretaion (niter in monte carlo).
    
    parseLine(&THREAD, &T, &QUEUE, &I, argv);

    threadpool_t *pool;
    
    pthread_mutex_init(&lock, NULL);
    
    assert((pool = threadpool_create(THREAD, QUEUE, 0)) != NULL);
    fprintf(stderr, "Pool started with %llu threads and queue size of %llu\n", THREAD, QUEUE);
    
    while (threadpool_add(pool, MontePI, &I) == 0) {
        pthread_mutex_lock(&lock);
        done++;
        pthread_mutex_unlock(&lock);
    }
    
    fprintf(stderr, "Added %d tasks\n", done);
    
    while((done / 2) > done) {
        usleep(10000);
    }
    assert(threadpool_destroy(pool, 0) == 0);
    fprintf(stderr, "Did %d tasks\n", done);

    gettimeofday(&end, NULL);
    elapsed = ((end.tv_sec - start.tv_sec) * 1000) + (end.tv_usec / 1000 - start.tv_usec / 1000);
    printf("%f", elapsed);
    return 0;
}



