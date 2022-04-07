CC=gcc
AR=ar
FLAGS= -Wall -g

all: sig

sig:  Sigaction.o
	$(CC) $(FLAGS) -o SigExample Sigaction.o

Sigaction.o: Sigaction.c
	$(CC) $(FLAGS) -c Sigaction.c

.PHONY: clean all
clean:
	rm -f *.o SigExample
