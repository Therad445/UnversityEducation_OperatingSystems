CC = gcc
CFLAGS = -I

parallel_min_max: parallel_min_max.c find_min_max.c utils.c
	$(CC) -o parallel_min_max parallel_min_max.c find_min_max.c utils.c $(CFLAGS)

process_memory: process_memory.c
	$(CC) -o process_memory process_memory.c $(CFLAGS)

clean:
	rm -f parallel_min_max process_memory