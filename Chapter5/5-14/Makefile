CC = gcc
SHELL := /bin/bash

.PHONY: all clean run

all: main input.txt

main: main.o alloc.o lines.o
	$(CC) main.o alloc.o lines.o -o main

main.o: main.c alloc.h lines.h
alloc.o: alloc.c alloc.h
lines.o: lines.c lines.h

input.txt:
	@echo "Hello there, how are you?" > input.txt
	@echo "This is a test to see how the program works." >> input.txt
	@echo "I hope you are well." >> input.txt
	@echo "All is good if you set your mind too it." >> input.txt
	@echo "Awesome work, keep it up." >> input.txt
	@echo "Becoming a good student is a noble aim." >>input.txt
	@echo "Hello world" >>input.txt
	@echo "All is fair in love and war" >>input.txt
	@echo "Brian Kernighan and Dennis Ritchie" >>input.txt
	@echo "Ken Thompson seems like he knows what he is doing" >>input.txt
	@echo "C or C++? That is an important question" >>input.txt
	@echo "All for one, and one for all!" >>input.txt
	@echo "Determinants are kinda cool in Mathematics" >>input.txt
	@echo "Malloc, alloc, calloc, ahh, its all the same, right?" >>input.txt
	@echo "Exceptional work!" >>input.txt

run:
	time ./main < input.txt
clean:
	rm -f *.o main input.txt
