LEX=lex
YACC=yacc
LDFLAGS=-ll

all: build

build: y.tab.o lex.yy.o
	gcc y.tab.o lex.yy.o -g $(LDFLAGS)

y.tab.o: y.tab.c
	gcc -c -g y.tab.c

lex.yy.o: lex.yy.c y.tab.h
	gcc -c -g lex.yy.c

y.tab.h: y.tab.c

y.tab.c: parse.y
	$(YACC) -d -y -t parse.y

lex.yy.c: scan.l
	$(LEX) scan.l

clean:
	$(RM) y.tab.? lex.yy.? a.out
