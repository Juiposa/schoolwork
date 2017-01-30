
# Flags that are sent to the compiler
# Do not change these
CFLAGS      =	-Wall -ansi -pedantic -g -Iinclude


music:
	gcc $(CFLAGS) src/main.c src/linkedList.c src/fileIO.c -o bin/list

test: 
	gcc $(CFLAGS) src/listTest.c src/linkedList.c -o bin/listTest

clean:
	@ rm *.o
