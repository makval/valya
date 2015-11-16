#pipe readers
CC=g++
CLEAN=rm -f
PROGRAM_NAME=PRd
OBJECT_FILES=main.o
SOURCE_FILES=main.cpp

all: $(PROGRAM_NAME)

$(PROGRAM_NAME): $(OBJECT_FILES)
	$(CC)  -o $@ $^

$(OBJECT_FILES): $(SOURCE_FILES)
	$(CC) -fPIC -c  $^

clean:
	$(CLEAN) $(OBJECT_FILES)
	$(CLEAN) $(PROGRAM_NAME)
