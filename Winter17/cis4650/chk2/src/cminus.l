/* cminus.l                                     */
/* Flex specification of a cminus scanner       */
/* Created by Jeffrey-David Kapp; 0832671       */
/* 1 March 2017 - Last modified 1/3/2017        */

%{

#include "cminus.h"
#include "y.tab.h"

string tokenString;
//true; parse normally, false; in comment, discard tokens
bool parseState = true;

%}

letter      [a-zA-z]
digit       [0-9]
identifier  {letter}+
number      {digit}+
newline     \n
whitespace  [ \t\r]+

%%

"else"          { if ( parseState ) return ELSE;          }
"if"            { if ( parseState ) return IF;            }
"int"           { if ( parseState ) return INT;           }
"return"        { if ( parseState ) return RETURN;        }
"void"          { if ( parseState ) return VOID;          }
"while"         { if ( parseState ) return WHILE;         }

"+"             { if ( parseState ) return PLUS;          }
"-"             { if ( parseState ) return MINUS;         }
"*"             { if ( parseState ) return MULTI;         }
"/"             { if ( parseState ) return DIVIDE;        }
"<"             { if ( parseState ) return LT;            }
">"             { if ( parseState ) return GT;            }
"<="            { if ( parseState ) return LE;            }
">="            { if ( parseState ) return GE;            }
"=="            { if ( parseState ) return EQ;            }
"!="            { if ( parseState ) return NE;            }
"="             { if ( parseState ) return ASSIGN;        }
";"             { if ( parseState ) return SEMICLN;       }
","             { if ( parseState ) return COMMA;         }
"("             { if ( parseState ) return LPAREN;        }
")"             { if ( parseState ) return RPAREN;        }
"["             { if ( parseState ) return LBRACKET;      }
"]"             { if ( parseState ) return RBRACKET;      }
"{"             { if ( parseState ) return LBRACE;        }
"}"             { if ( parseState ) return RBRACE;        }
"/*"            { parseState = false;   }
"*/"            { parseState = true;  }

{number}        {
                    if ( parseState ) {
                        yylval.str = strdup(yytext);
                        return NUM;
                    }
                }
{identifier}    {
                    if ( parseState ) {
                        yylval.str = strdup(yytext);
                        return ID;
                    }
                }

{newline}       { lineno++;             }
{whitespace}    {/*NOOP*/               }
.               { return ERROR;         }


%%

int getToken() {
    static bool firstTime = true;
    int curToken;
    if (firstTime) {
        firstTime = false;
        lineno++;
        yyin = sourceFile;
    }
    curToken = yylex();
    tokenString = yytext;
    /*
    fprintf(outputFile, "Line: %d ", lineno );
    printToken( curToken, tokenString );
    */
    return curToken;
}
