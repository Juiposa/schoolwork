/* sgml.l                                                       */
/* Flex specification for Standard Generalized Markup Language  */
/* Created by Jeffrey-David Kapp; 0832671                       */
/* 25 January 2017 - Last modifed 25/1/2017                     */

%{
    #include "sgml.h"

    string yylval;
%}

char            [a-zA-Z0-9]
integer         [0-9]+
number          ((\+|\-)?{integer}(.{integer})?)
word            {char}+
hypenated       ({word}(\-{word})+)
apostrophized   (({hypenated}|{word})('({hypenated}|{word}))+)
punctuation     [^{word}]
tag_name        [a-zA-Z0-9=" ]+
whitespace      [ \t\n]+

%%

{whitespace}                            { /*NOOP: whitespace*/                      }
{apostrophized}                         { yylval = yytext; return APOSTROPHIZED;    }
{hypenated}                             { yylval = yytext; return HYPHENATED;       }
"<"{tag_name}">"                        { yylval = yytext; return OPEN_TAG;         }
"</"{tag_name}">"                       { yylval = yytext; return CLOSE_TAG;        }
{number}                                { yylval = yytext; return NUMBER;           }
{word}                                  { yylval = yytext; return WORD;             }
{punctuation}                           { yylval = yytext; return PUNCTUATION;      }
<<EOF>>                                 { return ENDFILE;                           }

%%

token_t getToken(void) {
    return (token_t)yylex();
}
