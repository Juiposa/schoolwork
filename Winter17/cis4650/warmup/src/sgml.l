/* sgml.l                                                       */
/* Flex specification for Standard Generalized Markup Language  */
/* Created by Jeffrey-David Kapp; 0832671                       */
/* 25 January 2017 - Last modifed 25/1/2017                     */

%{
    #include "sgml.h"

    string yylval;
%}

number      [0-9]+
word        [a-zA-Z0-9]+
tag_name    [a-zA-Z0-9=" ]+
whitespace  [ \t\n]+

%%

"<"{tag_name}">"      { return OPEN_TAG; }
"</"{tag_name}">"     { return CLOSE_TAG; }
{whitespace}          { /*NOOP: whitespace*/ }

%%

token_t getToken(void) {
    return (token_t)yylex();
}
