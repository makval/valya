# makefile for libdl 

all: hello

hello: main.o libHello.so
	gcc main.o -ldl -o hello

main.o: main.c
	gcc -fPIC -c  main.c

libHello.so: hello.c
	gcc -fPIC -shared -o libHello.so hello.c

clean:
	rm -rf *.o
	rm libHello.so
	rm hello
