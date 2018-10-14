CFLAGS = -o
CC = gcc
LIBS =  -lm 

client server: client.c server.c
	${CC} ${CFLAGS} client client.c
	${CC} ${CFLAGS} server server.c

clean:
	rm -f *.o *~
