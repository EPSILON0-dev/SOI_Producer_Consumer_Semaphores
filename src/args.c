#include "semaphores.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Args parse_args(int argc, char *argv[])
{
    Args args = {
        .queue_length = 10,
        .producer_delay_ms = 100,
        .consumer_delay_ms = 150,
        .producer_randomness_ms = 50,
        .consumer_randomness_ms = 75
    };

    int index = 1;
    while (index < argc) 
    {
        if (strcmp(argv[index], "--help") == 0 || strcmp(argv[index], "-h") == 0)
        {
            printf("Usage: %s [OPTIONS]\n", argv[0]);
            printf("Options:\n");
            printf("  --help, -h                 Show this help message and exit\n");
            printf("  --ql <length>              Set queue length (default: 10)\n");
            printf("  --pd <ms>                  Set producer delay in milliseconds (default: 100)\n");
            printf("  --cd <ms>                  Set consumer delay in milliseconds (default: 150)\n");
            printf("  --pr <ms>                  Set producer randomness in milliseconds (default: 50)\n");
            printf("  --cr <ms>                  Set consumer randomness in milliseconds (default: 75)\n");
            exit(EXIT_SUCCESS);
        }
        else if (strcmp(argv[index], "--ql") == 0 && index + 1 < argc) 
        {
            args.queue_length = atoi(argv[index + 1]);
            index += 2;
        } 
        else if (strcmp(argv[index], "--pd") == 0 && index + 1 < argc) 
        {
            args.producer_delay_ms = atoi(argv[index + 1]);
            index += 2;
        } 
        else if (strcmp(argv[index], "--cd") == 0 && index + 1 < argc) 
        {
            args.consumer_delay_ms = atoi(argv[index + 1]);
            index += 2;
        } 
        else if (strcmp(argv[index], "--pr") == 0 && index + 1 < argc) 
        {
            args.producer_randomness_ms = atoi(argv[index + 1]);
            index += 2;
        } 
        else if (strcmp(argv[index], "--cr") == 0 && index + 1 < argc) 
        {
            args.consumer_randomness_ms = atoi(argv[index + 1]);
            index += 2;
        } 
        else 
        {
            fprintf(stderr, "Unknown argument: %s\n", argv[index]);
            exit(EXIT_FAILURE);
            index++;
        }
    }

    return args;
}
