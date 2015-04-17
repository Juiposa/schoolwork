CC = gcc
JC = javac
JFLAGS = -g -d bin/
CFLAGS = -Wall -ansi -g -std=c99 -Iinclude
JAVA_HOME = /usr/lib/jvm/java-1.7.0-openjdk-amd64
JNI_HEADER = -I$(JAVA_HOME)/include  -I$(JAVA_HOME)/include/linux
LD_PATH = export LD_LIBRARY_PATH={LD_LIBRARY_PATH}:bin/
LIB = -Llibpm -Iinclude

all: gui compiler

compiler: bin/compiler.o
	$(CC) -shared -Wl,-soname,libcompiler.so $(JNI_HEADER) -o bin/libcompiler.so bin/compiler.o

bin/compiler.o: src/compiler/* libpm
	$(CC) -c $(CFLAGS) $(JNI_HEADER) src/compiler/* -o bin/jni.o -fPIC
	ld -r bin/libpm.o bin/jni.o -o bin/compiler.o

gui: src/gui/*
	$(JC) src/gui/* $(JFLAGS)

##LIBPM TARGETS
# library building
libpm: creationDestruction interface functions
	ld -r PM_cd.o PM_interface.o PM_functions.o -o bin/libpm.o 

interface: src/libpm/PM_interface.c
	$(CC) -c $(CFLAGS) src/libpm/PM_interface.c -o PM_interface.o -fPIC

#creationdestruction functions
creationDestruction: src/libpm/PM_createDestroy.c 
	$(CC) -c $(CFLAGS) src/libpm/PM_createDestroy.c -o PM_cd.o -fPIC

#functions
functions: src/libpm/PM_functions.c
	$(CC) -c $(CFLAGS) src/libpm/PM_functions.c -o PM_functions.o -fPIC

#testing file
testFile: $(TESTFILE)
	$(CC) -c $(CFLAGS) $(TESTFILE) -o main.o

clean:
	rm *.o
	rm bin/*.o
