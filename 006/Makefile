# 006 mykill


all: mykill

mykill: main.o
	gcc main.o -o mykill

main.o: main.c
	gcc -fPIC -c main.c

clean:
	rm -rf *.o
	rm mykill

