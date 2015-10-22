# 005 shell1


all: shell1

shell1: main.o
	gcc main.o -o shell1

main.o: main.c
	gcc -fPIC -c main.c

clean:
	rm -rf *.o
	rm shell1

