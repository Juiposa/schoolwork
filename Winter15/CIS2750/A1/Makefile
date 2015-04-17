CC = gcc
CFLAGS = -Wall -ansi -g -std=c99 -Iinclude -pg
LIB = -Llibpm -Iinclude
TESTFILE = src/a1example.c

all: libpm

#testing
test: libpm testFile
	$(CC) main.o libpm.a -pg -o bin/A1 $(LIB) 

# library building
libpm: creationDestruction interface functions
	ar ruv libpm.a PM_cd.o PM_interface.o PM_functions.o

interface: src/PM_interface.c
	$(CC) -c $(CFLAGS) src/PM_interface.c -o PM_interface.o

#creationdestruction functions
creationDestruction: src/PM_createDestroy.c 
	$(CC) -c $(CFLAGS) src/PM_createDestroy.c -o PM_cd.o

#functions
functions: src/PM_functions.c
	$(CC) -c $(CFLAGS) src/PM_functions.c -o PM_functions.o

#testing file
testFile: $(TESTFILE)
	$(CC) -c $(CFLAGS) $(TESTFILE) -o main.o

clean:
	rm *.o
