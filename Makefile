# Создать исполняемый файл "hello1"
all: hello1

hello1: hello1.o
	gcc -fPIC hello1.o -L. -lhello_print -o hello1	

libhello_print.so: hello_print.cpp 
	gcc  -fPIC -shared hello_print.cpp -o libhello_print.so

hello1.o: hello1.cpp libhello_print.so
	gcc  -fPIC hello1.cpp -c -o hello1.o

clean:	
	rm hello1.o
	rm libhello_print.so
	rm hello1




