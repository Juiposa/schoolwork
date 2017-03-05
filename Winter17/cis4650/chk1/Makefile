CC = g++
FLEX = flex
YACC = yacc

CFLAGS = -Iinclude -g

all: parser bin/cminus.o include/y.tab.h
	$(CC) $(CFLAGS) bin/y.tab.o bin/lex.yy.o bin/cminus.o -ll -o cm

bin/cminus.o:
	$(CC) $(CFLAGS) -c src/cminus.cpp -o bin/cminus.o

parser: bin/y.tab.o bin/lex.yy.o

bin/y.tab.o: src/y.tab.c
	$(CC) $(CFLAGS) -c src/y.tab.c -o bin/y.tab.o

bin/lex.yy.o: src/lex.yy.c
	$(CC) $(CFLAGS) -c src/lex.yy.c -o bin/lex.yy.o

include/y.tab.h: src/y.tab.c
	mv src/y.tab.h include/

src/y.tab.c: src/cminus.y
	$(YACC) -v -o src/y.tab.c -d src/cminus.y

src/lex.yy.c: src/cminus.l
	$(FLEX) -o src/lex.yy.c src/cminus.l

clean:
	rm bin/*.o
	rm src/lex.yy.c src/y.tab.c
	rm include/y.tab.h
