CC = gcc
CFLAGS = -Wall -O2 -I./src

SRC = src/main.c src/producer.c src/consumer.c src/queue.c
OBJ = $(SRC:.c=.o)

all: semaphores

semaphores: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

clean:
	rm -f $(OBJ) semaphores
