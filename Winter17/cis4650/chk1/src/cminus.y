/* cminus.y                                     */
/* Flex specification of a cminus grammar       */
/* Created by Jeffrey-David Kapp; 0832671       */
/* 1 March 2017 - Last modified 1/3/2017        */

%{
#define YYPARSER

#include "cminus.h"

%}

//terminating tokens
%token ENDFILE, ERROR

//keywords
%token ELSE, IF, INT, RETURN, VOID, WHILE

//identifiers and numbers
%token ID, NUM

//special symbols
%token PLUS, MINUS, MULTI, DIVIDE, LT, GT, LE, GE, EQ, NE, ASSIGN, SEMICLN, COMMA
%token LPAREN, RPAREN, LBRACKET, RBRACKET, LBRACE, RBRACE, OPENCOMMENT, CLOSECOMMENT

%%


program             : declaration_list
                    ;

declaration_list    : declaration_list declaration
                    | declaration
                    ;

declaration         : var_declaration
                    | func_declaration
                    ;

var_declaration     : type_specifier ID SEMICLN
                    | type_specifier ID LBRACKET NUM RBRACKET SEMICLN
                    ;

type_specifier      : INT
                    | VOID
                    ;

func_declaration    : type_specifier ID LPAREN params RPAREN compound_stmt
                    ;

params              : param_list
                    | VOID
                    ;

param_list          : param_list COMMA param
                    | param
                    ;

param               : type_specifier ID
                    | type_specifier ID LBRACKET RBRACKET
                    ;

compound_stmt       : LBRACE local_declarations statement_list RBRACE
                    ;

local_declarations  : local_declarations var_declaration
                    | empty //fix me
                    ;

statement_list      : statement_list statement
                    | empty //fix me
                    ;

statement           : expression_stmt
                    | compound_stmt
                    | selection_stmt
                    | iteration_stmt
                    | return_stmt
                    ;

expression_stmt     : expression SEMICLN
                    | SEMICLN
                    ;

selection_stmt      : IF LPAREN expression RPAREN statement
                    | IF LPAREN expression RPAREN statement ELSE statement
                    ;

iteration_stmt      : WHILE LPAREN expression RPAREN statement
                    ;

return_stmt         : RETURN SEMICLN
                    | RETURN expression SEMICLN
                    ;

expression          : var ASSIGN expression
                    | simple_expression
                    ;

var                 : ID
                    | ID LBRACKET expression RBRACKET
                    ;

simple_expression   : additive_expression relop additive_expression
                    | additive_expression
                    ;

relop               : LT
                    | GT
                    | LE
                    | GE
                    | EQ
                    | NE
                    ;

additive_expression : additive_expression addop term
                    | term
                    ;

addop               : PLUS
                    | MINUS
                    ;

term                : term mulop factor
                    | factor
                    ;

mulop               : MULTI
                    | DIVIDE
                    ;

factor              : LPAREN expression RPAREN
                    | var
                    | call
                    | NUM
                    ;

call                : ID LPAREN args RPAREN
                    ;

args                : args_list
                    | empty //fix me
                    ;

args_list           : args_list COMMA expression
                    | expression
                    ;
