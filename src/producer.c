#include "semaphores.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

void producer_process(int id, Queue *qa, Queue *qb)
{
    srand(time(NULL) + id);
    bool next_queue = false;
    pid_t pid = getpid();

    for ( ;; ) 
    { 
        int value = rand() % 100;
        int result;

        if (next_queue) 
        {
            result = queue_try_push(qb, value);
        } 
        else 
        {
            result = queue_try_push(qa, value);
        }

        if (result == 0)
        {
            printf("[PROD %d (%5d)] Placed %d on queue %c\n", 
                id, pid, value, next_queue + id * 2 + 'A');
        }
        next_queue = !next_queue;

        #if SLOW_OPERATION != 0
        usleep(MIN_DELAY_US + rand() % (MAX_DELAY_US - MIN_DELAY_US + 1));
        #endif
    }
}
