CC=gcc
CFLAGS=-I.

 mutex_on: 
	$(CC) -o mutex_on mutex_on.c -lpthread $(CFLAGS)

 mutex_off: 
	$(CC) -o mutex_off mutex_off.c $(CFLAGS)

 program2: 
	$(CC) -o program2 program2.c $(CFLAGS)

 program3: 
	$(CC) -o program3 program3.c -lpthread $(CFLAGS)

clean :
	rm mutex_on mutex_off