#killl

all: my_kill

my_kill: main.o
	gcc main.o -o my_kill

main.o: main.c
	gcc -fPIC -c main.c

clean:
	rm -rf *.o
	rm my_kill
