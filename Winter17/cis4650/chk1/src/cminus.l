/* cminus.l                                     */
/* Flex specification of a cminus scanner       */
/* Created by Jeffrey-David Kapp; 0832671       */
/* 1 March 2017 - Last modified 1/3/2017        */

%{

#include "cminus.h"
#include "y.tab.h"

string inString;
%}

letter      [a-zA-z]
digit       [0-9]
identifier  {letter}+
number      {digit}+

%%

"else"          { return ELSE;          }
"if"            { return IF;            }
"int"           { return INT;           }
"return"        { return RETURN;        }
"void"          { return VOID;          }
"while"         { return WHILE;         }

"+"             { return PLUS;          }
"-"             { return MINUS;         }
"*"             { return MULTI;         }
"/"             { return DIVIDE;        }
"<"             { return LT;            }
">"             { return GT;            }
"<="            { return LE;            }
">="            { return GE;            }
"=="            { return EQ;            }
"!="            { return NE;            }
"="             { return ASSIGN;        }
";"             { return SEMICLN;       }
","             { return COMMA;         }
"("             { return LPAREN;        }
")"             { return RPAREN;        }
"["             { return LBRACKET;      }
"]"             { return RBRACKET;      }
"{"             { return LBRACE;        }
"}"             { return RBRACE;        }
"/*"            { return OPENCOMMENT;   }
"*/"            { return CLOSECOMMENT;  }

{number}        { return NUM;           }
{identifier}    { return ID;            }

{newline}       { lineno++;             }
{whitespace}    {/*NOOP*/               }
<<EOF>>         { return ENDFILE;       }
