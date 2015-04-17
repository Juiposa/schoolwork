CC = gcc
CFLAGS = -Wall -ansi -g

all: t1 t2
	$(CC) file1.o file2.o -o program

t1:	file1.c
	$(CC) -c file1.c $(CFLAGS)

t2: file2.c
	$(CC) -c file2.c $(CFLAGS)