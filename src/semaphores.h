#ifndef SEMAPHORES_H
#define SEMAPHORES_H

#include <semaphore.h>

// Configuration defines
#define N_QUEUES 4
#define N_CONS 4
#define N_PORD 2

// Argument struct
typedef struct {
    int queue_length;
    int producer_delay_ms;
    int consumer_delay_ms;
    int producer_randomness_ms;
    int consumer_randomness_ms;
} Args;

Args parse_args(int argc, char *argv[]);

// Queue structure
typedef struct {
    int *buffer;
    int head;
    int tail;
    size_t capacity;
    size_t size;
    sem_t sem;
    sem_t empty;
    sem_t full;
} Queue;

void queue_init(Queue **q, size_t size);
void queue_destroy(Queue **q);
int queue_try_push(Queue *q, int value);
int queue_try_pop(Queue *q, int *value);

// Producer process
void producer_process(int id, Queue *qa, Queue *qb, Args args);

// Consumer process
void consumer_process(int id, Queue *q, Args args);

#endif
