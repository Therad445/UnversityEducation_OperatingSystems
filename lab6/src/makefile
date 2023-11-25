CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: server client

server: server.o utils.o
	gcc -o server server.o utils.o -Wall -Wextra -Werror -pthread

client: client.o utils.o
	gcc -o client client.o utils.o -Wall -Wextra -Werror

server.o: server.c
	gcc -c server.c

client.o: client.c
	gcc -c client.c

utils.o: utils.c
	gcc -c utils.c

clean:
	rm -f *.o server client