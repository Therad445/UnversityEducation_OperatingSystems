CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: client.o server.o

client.o: client.c
	$(CC) -o client.o client.c $(CFLAGS)

server.o: server.c
	$(CC) -o server.o server.c $(CFLAGS)

clean:
	rm client.o server.o

dependencies:
	client.o: client.c
	server.o: server.c