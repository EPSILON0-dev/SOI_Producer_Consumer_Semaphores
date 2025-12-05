#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "semaphores.h"

void consumer_process(int id, Queue *q, Args args) 
{
    fprintf(stderr, "[CONS %d (%5d)] Starting consumer process\n", id, getpid());

    for ( ;; ) 
    {
        int value;
        if (queue_try_pop(q, &value) == 0)
        {
            printf("[CONS %d (%5d)] Consumed %d from queue %c\n", 
                id, getpid(), value, id + 'A');
        }
        else
        {
            fprintf(stderr, "[CONS %d (%5d)] Queue %c is empty\n", 
                id, getpid(), id + 'A');
        }

        usleep((args.consumer_delay_ms + rand() % (args.consumer_randomness_ms + 1)) * 1000);
    }
}
