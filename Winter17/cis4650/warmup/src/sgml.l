/* sgml.l                                                       */
/* Flex specification for Standard Generalized Markup Language  */
/* Created by Jeffrey-David Kapp; 0832671                       */
/* 25 January 2017 - Last modifed 25/1/2017                     */

%{
    #include "scanner.h"
    #include "sgml.h"

    TokenVal yylval;
%}

number      [0-9]+
identifier  [a-zA-Z]+
words       [a-zA-Z0-9]+


%%

"<"{identifier}">"      { return OPEN_TAG; }
"</"{identifier}">"     { return CLOSE_TAG; }


%%

token_t getToken(void) {
    return (token_t)yylex();
}
