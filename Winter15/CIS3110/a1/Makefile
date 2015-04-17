CFLAGS = -g -Wall -Iinclude

all: msh
msh: shell.o lex.yy.o
	gcc -o bin/msh shell.o lex.yy.o -lfl  
shell.o: src/shell.c
	gcc $(CFLAGS) -c src/shell.c
lex.yy.o: lex.yy.c
	gcc $(CFLAGS) -c lex.yy.c
lex.yy.c: src/lex.c
	flex src/lex.c
clean:
	rm -f *.o
	rm -f lex.yy.c
	rm -f bin/msh
	