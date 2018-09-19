CFLAGS = -c
CC = gcc
LIBS =  -lm 

all: main

main: main.o lib.o
	${CC} main.o lib.o -o main

main.o: main.c
	${CC} ${CFLAGS} main.c

lib.o: lib.c
	${CC} ${CFLAGS} lib.c

clean:
	rm -f *.o *~