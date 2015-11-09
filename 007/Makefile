#summator y=S(sin(dx))[dx=delta=N/n]

all: Summ

Summ: main.o
	gcc main.o -o Summ -lpthread

main.o: main.c
	gcc -fPIC -c main.c

clean:
	rm -rf *.o
	rm Summ
