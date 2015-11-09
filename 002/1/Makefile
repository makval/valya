#Make
all: F3

F3: main.o
	gcc main.o -o F3

main.o: main.c
	gcc -fPIC -c main.c

clean:
	rm -rf *.o
	rm F3
