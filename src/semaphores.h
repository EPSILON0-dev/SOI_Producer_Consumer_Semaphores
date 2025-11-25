#ifndef SEMAPHORES_H
#define SEMAPHORES_H

#include <semaphore.h>

// Configuration defines
#define SLOW_OPERATION 1
#define N_QUEUES 4
#define N_CONS 4
#define N_PORD 2
#define QUEUE_SIZE 10
#define MIN_DELAY_US 100000
#define MAX_DELAY_US 500000


// Queue structure
typedef struct {
    int *buffer;
    int head;
    int tail;
    size_t capacity;
    size_t size;
    sem_t sem;
} Queue;

void queue_init(Queue **q, size_t size);
void queue_destroy(Queue **q);
int queue_try_push(Queue *q, int value);
int queue_try_pop(Queue *q, int *value);

// Producer process
void producer_process(int id, Queue *qa, Queue *qb);

// Consumer process
void consumer_process(int id, Queue *q);

#endif
