//
//  threadpool.h
//  ThreadPool
//
//  Created by Gal Argov Sofer on 2/4/18.
//  Copyright © 2018 Gal Argov Sofer. All rights reserved.
//

#ifndef threadpool_h
#define threadpool_h

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
    #endif
    /* =================================== API ======================================= */
    #define MAX_THREADS 5
    #define MAX_QUEUE 100

    typedef void*(*functionPtr)(void*);
    typedef struct threadpool_t threadpool_t;
    
    // Enums
    typedef enum {
        threadpool_invalid        = -1,
        threadpool_lock_failure   = -2,
        threadpool_queue_full     = -3,
        threadpool_shutdown       = -4,
        threadpool_thread_failure = -5
    } threadpool_error_t;
    
    // Prototypes
    typedef struct threadpool_t* pool;
    threadpool_t *threadpool_create(unsigned long long thread_count, unsigned long long queue_size, int flags);
    int threadpool_add(threadpool_t * pool, void *(function)(void *), void * argument);
    int threadpool_destroy(threadpool_t *pool, int flags);
    int threadpool_free(threadpool_t * pool);
    int threadpool_num_threads_working(threadpool_t * pool);
    void *threadpool_thread(void * threadpool);
    
    #ifdef __cplusplus
}
#endif

#endif /* threadpool_h */
