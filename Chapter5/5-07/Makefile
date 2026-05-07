CC = gcc

main: main.o alloc.o lines.o
	$(CC) main.o alloc.o lines.o -o main

main.o: main.c alloc.h lines.h
alloc.o: alloc.c alloc.h
lines.o: lines.c lines.h

clean:
	rm -f *.o main
