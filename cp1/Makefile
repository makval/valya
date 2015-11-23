#this is cp1
CC=g++
CLEAN=rm -f
PROGRAM_NAME=cp1
OBJECT_FILES=main.o
SOURCE_FILES=main.cpp

all: $(PROGRAM_NAME)

$(PROGRAM_NAME): $(OBJECT_FILES)
	$(CC) -o $@ $^

$(OBJECT_FILES): $(SOURCE_FILES)
	$(CC) -c $^

clean:
	$(CLEAN) $(OBJECT_FILES)
	$(CLEAN) $(PROGRAM_NAME)
