#Tree
all: tree_proc

tree_proc: main.o
	gcc main.o -o tree_proc

main.o: main.c
	gcc -fPIC -c main.c

clean:
	rm -rf *.o
	rm tree_proc
