CC = gcc
SHELL := /bin/bash

.PHONY: all clean

all: tail 

tail: tail.o alloc.o lines.o
	$(CC) tail.o alloc.o lines.o -o tail 

tail.o: tail.c alloc.h lines.h
alloc.o: alloc.c alloc.h
lines.o: lines.c lines.h
clean:
	rm -f *.o
