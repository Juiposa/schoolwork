CC = gcc
JC = javac
LEX=lex
YACC=yacc
JFLAGS = -g -d bin/
CFLAGS = -Wall -ansi -g -std=c99 -Iinclude
JAVA_HOME = /usr/lib/jvm/java-1.7.0-openjdk-amd64
JNI_HEADER = -I$(JAVA_HOME)/include  -I$(JAVA_HOME)/include/linux
LD_PATH = export LD_LIBRARY_PATH={LD_LIBRARY_PATH}:bin/
LIB = -Llibpm -Iinclude

all: gui compiler yadc

compiler: bin/compiler.o
	$(CC) -shared -Wl,-soname,libcompiler.so $(JNI_HEADER) -o bin/libcompiler.so bin/compiler.o

bin/compiler.o: src/compiler/compiler.c bin/emitJava.o libpm
	$(CC) -c $(CFLAGS) $(JNI_HEADER) src/compiler/compiler.c -o bin/jni.o -fPIC
	ld -r bin/libpm.o bin/jni.o bin/emitJava.o -o bin/compiler.o

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

#parser build
yadc: bin/y.tab.o bin/lex.yy.o bin/emitJava.o libpm
	gcc $(CFLAGS) bin/y.tab.o bin/lex.yy.o bin/emitJava.o bin/libpm.o -ll -o bin/yadc

bin/y.tab.o: src/yadc/y.tab.c
	gcc -g -Iinclude -c src/yadc/y.tab.c -o bin/y.tab.o 

bin/lex.yy.o: src/yadc/lex.yy.c include/y.tab.h
	gcc -g -Iinclude -c src/yadc/lex.yy.c -o bin/lex.yy.o 

bin/emitJava.o: src/compiler/emitJava.c
	gcc $(CFLAGS) -c src/compiler/emitJava.c -o bin/emitJava.o -fPIC

#moving header to where it needs to be
include/y.tab.h: src/yadc/y.tab.c
	mv src/yadc/y.tab.h include/

src/yadc/y.tab.c: src/yadc/pm_parse.y
	$(YACC) -v -o src/yadc/y.tab.c -d src/yadc/pm_parse.y 

src/yadc/lex.yy.c: src/yadc/pm_lexer.l
	$(LEX) -o src/yadc/lex.yy.c src/yadc/pm_lexer.l 

clean:
	rm *.o
	rm bin/*.o
	rm src/yadc/y.tab.? src/yadc/lex.yy.?

hardclean: clean
	rm -rf bin/*
