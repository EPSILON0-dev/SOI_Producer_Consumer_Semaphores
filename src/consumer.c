#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "semaphores.h"

void consumer_process(int id, Queue *q) 
{
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
            printf("[CONS %d (%5d)] Queue %c is empty\n", 
                id, getpid(), id + 'A');
        }

        #if SLOW_OPERATION != 0
        usleep(MIN_DELAY_US + rand() % (MAX_DELAY_US - MIN_DELAY_US + 1));
        #endif
    }
}
