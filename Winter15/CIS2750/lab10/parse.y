%{
#include <stdio.h>
#include <stdlib.h>
int a_count = 0;
int b_count = 0;
char out[1024];
char a_str[1024];
void yyerror(const char *);
extern char * yytext;
%}
%union {
	char * sval;
}
%token <sval> A_TOK 
%token <sval> B_TOK
%%

string : a_val b_val
       ;

a_val  : A_TOK  { a_count = strlen(yytext); strcat(a_str, yytext); }
       ;

b_val  : B_TOK  { 
			b_count = strlen(yytext);
			if ( b_count == a_count ) {
				strcat(out, a_str);
				strcat(out, yytext);
			} else if ( b_count < a_count ) {
				strncat(out, a_str, b_count );
				strcat(out, yytext);
			} else if ( b_count > a_count ) {
				strcat(out, a_str);
				strncat(out, yytext, a_count);
				b_count = a_count;
			}
 	   }
	   ;

%%

void yyerror(const char *s) { fprintf(stderr, "%s\n", s); }

int main() {
	yyparse();
	printf("%s = %d\n", out, b_count );
	return 0;
}
