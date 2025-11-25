#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "semaphores.h"
#include <sys/mman.h>

void queue_init(Queue **q, size_t size) 
{
    // Allocate shared memory for the queue structure
    Queue *shared_q = mmap(NULL, sizeof(Queue), PROT_READ | PROT_WRITE, 
        MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (shared_q == MAP_FAILED) 
    {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    // Allocate shared memory for the buffer
    shared_q->buffer = mmap(NULL, size * sizeof(int), PROT_READ | PROT_WRITE, 
        MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (shared_q->buffer == MAP_FAILED) 
    {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    shared_q->capacity = size;
    shared_q->size = 0;
    shared_q->head = 0;
    shared_q->tail = 0;
    sem_init(&shared_q->sem, 1, 1);

    // Copy the shared queue pointer to the provided pointer
    *q = shared_q;
}

void queue_destroy(Queue **q) 
{
    // Free shared memory for the buffer
    if (munmap((*q)->buffer, (*q)->capacity * sizeof(int)) == -1) 
    {
        perror("munmap");
        exit(EXIT_FAILURE);
    }

    // Free shared memory for the queue structure
    if (munmap(*q, sizeof(Queue)) == -1) 
    {
        perror("munmap");
        exit(EXIT_FAILURE);
    }

    sem_destroy(&(*q)->sem);
    free(*q);
    *q = NULL;
}

int queue_try_push(Queue *q, int value)
{
    bool pushed = false;
    sem_wait(&q->sem);

    if (q->size < q->capacity) 
    {
        q->buffer[q->tail] = value;
        q->tail = (q->tail + 1) % q->capacity;
        q->size++;
        pushed = true;
    }

    sem_post(&q->sem);
    return pushed ? 0 : -1;
}

int queue_try_pop(Queue *q, int *value) 
{
    bool popped = false;
    sem_wait(&q->sem);

    if (q->size > 0) 
    {
        *value = q->buffer[q->head];
        q->head = (q->head + 1) % q->capacity;
        q->size--;
        popped = true;
    }

    sem_post(&q->sem);
    return popped ? 0 : -1;
}
