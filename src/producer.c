#include "semaphores.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

void producer_process(int id, Queue *qa, Queue *qb, Args args)
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
        else
        {
            printf("[PROD %d (%5d)] Queue %c is full\n", 
                id, pid, next_queue + id * 2 + 'A');
        }
        next_queue = !next_queue;

        usleep((args.producer_delay_ms + rand() % (args.producer_randomness_ms + 1)) * 1000);
    }
}
