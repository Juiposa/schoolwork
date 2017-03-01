CC = g++

CFLAGS = -Iinclude -g

all: lex.yy.o Tag.o scanner.o
	$(CC) $(CFLAGS) lex.yy.o Tag.o scanner.o -o scanner -lfl

scanner.o: src/scanner.cpp include/sgml.h include/Tag.h
	$(CC) $(CFLAGS) -c src/scanner.cpp

Tag.o: src/Tag.cpp include/sgml.h include/Tag.h
	$(CC) $(CFLAGS) -c src/Tag.cpp

lex.yy.c: src/sgml.l
	flex src/sgml.l

lex.yy.o: lex.yy.c
	$(CC) $(CFLAGS) -c lex.yy.c

clean:
	rm -f *.o lex.yy.c
