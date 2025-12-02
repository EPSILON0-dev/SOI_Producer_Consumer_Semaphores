#include <unistd.h>
#include <sys/wait.h>
#include "semaphores.h"

int main(int argc, char *argv[]) 
{
    Args args = parse_args(argc, argv);

    // Setup PIDs
    pid_t pids[N_CONS + N_PORD];

    // Create the queues
    Queue *queues[N_QUEUES];
    for (int i = 0; i < N_QUEUES; i++) 
    {
        queue_init(&queues[i], args.queue_length);
    }

    // Spawn producers
    for (int i = 0; i < N_PORD; i++) 
    {
        if ((pids[i] = fork()) == 0) 
        {
            producer_process(i, queues[i * 2 + 0], queues[i * 2 + 1], args);
            return 0;
        }
    }

    // Spawn consumers
    for (int i = 0; i < N_CONS; i++) 
    {
        if ((pids[N_PORD + i] = fork()) == 0) 
        {
            consumer_process(i, queues[i], args);
            return 0;
        }
    }

    // Wait for all child processes
    for (int i = 0; i < N_CONS + N_PORD; i++) 
    {
        waitpid(pids[i], NULL, 0);
    }

    return 0;
}
