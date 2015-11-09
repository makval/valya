#Makefile for func getenv(002)
all: F1

F1: a1.o
	gcc a1.o -o F1

a1.o: a1.c
	gcc -fPIC -c a1.c

clean:
	rm -rf *.o
	rm F1
