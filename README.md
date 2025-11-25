# Producer-Consumer Synchronization

This project is a college assignment for the Operating Systems course. It demonstrates the implementation of the **Producer-Consumer Problem** using semaphores for synchronization.

## Purpose
The goal of this project is to implement a solution to the classic Producer-Consumer Problem, where multiple producers generate data and place it in a shared queue, and multiple consumers retrieve data from the queue. Synchronization is achieved using semaphores to ensure thread-safe access to the shared resources.

## File Structure
- **`src/main.c`**: Entry point of the program.
- **`src/producer.c`**: Contains the implementation of the producer logic.
- **`src/consumer.c`**: Contains the implementation of the consumer logic.
- **`src/queue.c`**: Implements the shared queue used by producers and consumers.
- **`src/semaphores.h`**: Header file defining semaphore-related utilities.
- **`Makefile`**: Used to compile the project.

## Usage
After building the project, run the executable to start the simulation:

```bash
make
./semaphores
```

The program will simulate producers and consumers interacting with a shared queue.

Operation can be slowed down by setting the `SLOW_OPERATION` define in 
`src/semaphores.h` to a value of 1.
