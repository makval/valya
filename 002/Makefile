#  makefile for my_pwd

all: my_pwd

my_pwd: main_pwd.o
	gcc -o main_pwd main_pwd.o 

main_pwd.o: main_pwd.c
	gcc -c main_pwd.c 

clean:
	rm -f *.o
	rm -f main_pwd

