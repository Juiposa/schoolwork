/* cminus.y                                     */
/* Flex specification of a cminus grammar       */
/* Created by Jeffrey-David Kapp; 0832671       */
/* 1 March 2017 - Last modified 6/3/2017        */

%{
#define YYPARSER

#include "cminus.h"


static astTreeNode * returnTree; //tree to be built and returned by the parser
bool parseSuccess = true; //will block the return of the ast if there were syntax errors
char * activeFunction = NULL; //reference to the function whose scope we're in
int currScope = 0; //current scope (symbol table)
extern int yychar;
extern unordered_map<string, astTreeNode*> symbolTable;
extern int yyparse(void);

static int yylex(void) {
    return getToken();
}

astTreeNode * parse() {
    yyparse();
    return returnTree;
}

void yyerror(string message) {
    parseSuccess = false;
    fprintf(outputFile, "ERROR: at line %d: %s ", lineno, message.c_str() );
    fprintf(outputFile, "on token: ");
    printToken(yychar, tokenString);
    return;
}

%}

%union {
    astTreeNode * node;
    char * str;
    int op;
    int varType;
}

//terminating tokens
%token ENDFILE ERROR

//keywords
%token ELSE IF INT RETURN VOID WHILE

//identifiers and numbers
%token ID NUM

//special symbols
%token PLUS MINUS MULTI DIVIDE LT GT LE GE EQ NE ASSIGN SEMICLN COMMA
%token LPAREN RPAREN LBRACKET RBRACKET LBRACE RBRACE OPENCOMMENT CLOSECOMMENT

%type <node> program declaration_list declaration var_declaration func_declaration
%type <node> params param_list param compound_stmt local_declarations statement_list
%type <node> statement expression_stmt expression selection_stmt iteration_stmt
%type <node> return_stmt simple_expression additive_expression term factor var
%type <node> call args args_list
%type <op> relop addop mulop
%type <op> LT GT LE GE EQ NE PLUS MINUS MULTI DIVIDE
%type <str> ID NUM
%type <varType> type_specifier

%%


program             : declaration_list
                        {
                            if (parseSuccess)
                                returnTree = $1;
                            else
                                returnTree = NULL;
                        }
                    ;

declaration_list    : declaration_list declaration
                        { //placing siblings in their linked list
                          //from tiny_c
                          //this is used several times below as well
                            astTreeNode * t = $1;
                            if ( t != NULL ) {
                                while( t->sibling != NULL ) {
                                    t = t->sibling;
                                }
                                t->sibling = $2;
                                $$ = $1;
                            } else {
                                $$ = $2;
                            }
                        }
                    | declaration { $$ = $1; }
                    ;

declaration         : var_declaration { $$ = $1; }
                    | func_declaration { $$ = $1; }
                    ;

var_declaration     : type_specifier ID SEMICLN
                        {
                            /*astTreeNode * newNode = newDec(VAR_K);
                            strcpy(newNode->val, $2);
                            newNode->array = false;
                            $$ = newNode;*/
                            $$ = newDec(VAR_K);
                            strcpy($$->val, $2);
                            $$->func = false;
                            $$->array = false;
                            switch($1) {
                                case INT:
                                    $$->type = INT_T;
                                    //symbolTable.insert({ $$->val, $$ });
                                    break;
                                case VOID:
                                    $$->type = VOID_T;
                                    //symbolTable.insert({ $$->val, $$ });
                                    break;
                                default:
                                    fprintf(outputFile, "ERROR: at line %d: Variable declaration of an invalid type\n", lineno);
                                    $$ = NULL;
                                    break;
                            }
                        }
                    | type_specifier ID LBRACKET NUM RBRACKET SEMICLN
                        {
                            $$ = newDec(VAR_K);
                            strcpy($$->val, $2);
                            $$->func = false;
                            $$->array = true;
                            $$->size = atoi($4);
                            switch($1) {
                                case INT:
                                    $$->type = INT_T;
                                    //symbolTable.insert({ $$->val, $$ });
                                    break;
                                case VOID:
                                    $$->type = VOID_T;
                                    //symbolTable.insert({ $$->val, $$ });
                                    break;
                                default:
                                    fprintf(outputFile, "ERROR: at line %d: Variable declaration of an invalid type\n", lineno);
                                    $$ = NULL;
                                    break;
                            }
                        }
                    | type_specifier error SEMICLN
                        {
                            fprintf(outputFile, "ERROR: at line %d: Unexpected tokens during variable declaration\n", lineno);
                            $$ = NULL;
                        }
                    ;

type_specifier      : INT   { $$ = INT; }
                    | VOID  { $$ = VOID; }
                    | error { $$ = 999; }
                    ;

func_declaration    : type_specifier ID LPAREN params RPAREN compound_stmt
                        {
                            $$ = newDec(FUN_K);
                            strcpy( $$->val, $2 );
                            $$->child[0] = $4;
                            $$->child[1] = $6;
                            $$->func = true;
                            switch($1) {
                                case INT:
                                    $$->type = INT_T;
                                    //symbolTable.insert({ $$->val, $$ });
                                    break;
                                case VOID:
                                    $$->type = VOID_T;
                                    //symbolTable.insert({ $$->val, $$ });
                                    break;
                                default:
                                    fprintf(outputFile, "ERROR: at line %d: Function has invalid return type\n", lineno);
                                    $$ = NULL;
                                    break;
                            }
                            if ( activeFunction != NULL ) { //if null function doesn't have a return statement
                                strcpy(activeFunction, $$->val);
                                activeFunction = NULL;
                            }

                        }
                    ;

params              : param_list { $$ = $1; }
                    | VOID { $$ = NULL; }
                    ;

param_list          : param_list COMMA param
                        {
                            astTreeNode * t = $1;
                            if ( t != NULL ) {
                                while( t->sibling != NULL ) {
                                    t = t->sibling;
                                }
                                t->sibling = $3;
                                $$ = $1;
                            } else {
                                $$ = $3;
                            }
                        }
                    | param { $$ = $1; }
                    ;

param               : type_specifier ID
                        {
                            $$ = newDec(PARAM_K);
                            strcpy($$->val, $2);
                            $$->func = false;
                            $$->array = false;
                            switch($1) {
                                case INT:
                                    $$->type = INT_T;
                                    //symbolTable.insert({ $$->val, $$ });
                                    break;
                                case VOID:
                                    $$->type = VOID_T;
                                    //symbolTable.insert({ $$->val, $$ });
                                    break;
                                default:
                                    fprintf(outputFile, "ERROR: at line %d: Variable declaration of an invalid type\n", lineno);
                                    $$ = NULL;
                                    break;
                            }
                        }
                    | type_specifier ID LBRACKET RBRACKET
                        {
                            $$ = newDec(PARAM_K);
                            strcpy($$->val, $2);
                            $$->func = false;
                            $$->array = true;
                            $$->size = 999;
                            switch($1) {
                                case INT:
                                    $$->type = INT_T;
                                    //symbolTable.insert({ $$->val, $$ });
                                    break;
                                case VOID:
                                    $$->type = VOID_T;
                                    //symbolTable.insert({ $$->val, $$ });
                                    break;
                                default:
                                    fprintf(outputFile, "ERROR: at line %d: Variable declaration of an invalid type\n", lineno);
                                    $$ = NULL;
                                    break;
                            }
                        }
                    | error { $$ = NULL; }
                    ;

compound_stmt       : LBRACE local_declarations statement_list RBRACE
                        {
                            $$ = newStmt(CMPD_K);
                            $$->child[0] = $2;
                            $$->child[1] = $3;
                        }
                    ;

local_declarations  : local_declarations var_declaration
                        {
                            astTreeNode * t = $1;
                            if ( t != NULL ) {
                                while( t->sibling != NULL ) {
                                    t = t->sibling;
                                }
                                t->sibling = $2;
                                $$ = $1;
                            } else {
                                $$ = $2;
                            }
                        }
                    | /*empty*/ { $$ = NULL; }
                    ;

statement_list      : statement_list statement
                        {
                            astTreeNode * t = $1;
                            if ( t != NULL ) {
                                while( t->sibling != NULL ) {
                                    t = t->sibling;
                                }
                                t->sibling = $2;
                                $$ = $1;
                            } else {
                                $$ = $2;
                            }
                        }
                    | /*empty*/ { $$ = NULL; }
                    ;

statement           : expression_stmt { $$ = $1; }
                    | compound_stmt { $$ = $1; }
                    | selection_stmt { $$ = $1; }
                    | iteration_stmt { $$ = $1; }
                    | return_stmt { $$ = $1; }
                    ;

expression_stmt     : expression SEMICLN { $$ = $1; }
                    | SEMICLN { $$ = NULL;}
                    ;

selection_stmt      : IF LPAREN expression RPAREN statement
                        {
                            $$ = newStmt(IF_K);
                            $$->child[0] = $3;
                            $$->child[1] = $5;
                        }
                    | IF LPAREN expression RPAREN statement ELSE statement
                        {
                            $$ = newStmt(IF_K);
                            $$->child[0] = $3;
                            $$->child[1] = $5;
                            $$->child[2] = $7;
                        }
                    | error { $$ = NULL; }
                    ;

iteration_stmt      : WHILE LPAREN expression RPAREN statement
                        {
                            $$ =  newStmt(WHILE_K);
                            $$->child[0] = $3;
                            $$->child[1] = $5;
                        }
                    ;

return_stmt         : RETURN SEMICLN
                        {
                            $$ = newStmt(RETURN_K);
                            if (activeFunction == NULL)
                                activeFunction = (char*)malloc(sizeof(char)*50);
                            $$->function = activeFunction;

                        }
                    | RETURN expression SEMICLN
                        {
                            $$ = newStmt(RETURN_K);
                            if (activeFunction == NULL)
                                activeFunction = (char*)malloc(sizeof(char)*50);
                            $$->child[0] = $2;
                            $$->function = activeFunction;
                        }
                    ;

expression          : var ASSIGN expression
                        {
                            $$ = newExp(OP_K);
                            $$->op = ASSIGN;
                            $$->child[0] = $1;
                            $$->child[1] = $3;
                        }
                    | simple_expression { $$ = $1; }
                    | error { $$ = NULL; }
                    ;

var                 : ID
                        {
                            $$ = newExp(ID_K);
                            strcpy($$->val, $1);
                        }
                    | ID LBRACKET expression RBRACKET
                        {
                            $$ = newExp(ID_K);
                            strcpy($$->val, $1);
                            $$->child[0] = $3;
                        }
                    ;

simple_expression   : additive_expression relop additive_expression
                        {
                            $$ = newExp(OP_K);
                            $$->op = $2;
                            $$->child[0] = $1;
                            $$->child[1] = $3;
                        }
                    | additive_expression { $$ = $1; }
                    ;

relop               : LT { $$ = LT; }
                    | GT { $$ = GT; }
                    | LE { $$ = LE; }
                    | GE { $$ = GE; }
                    | EQ { $$ = EQ; }
                    | NE { $$ = NE; }
                    ;

additive_expression : additive_expression addop term
                        {
                            $$ = newExp(OP_K);
                            $$->op = $2;
                            $$->child[0] = $1;
                            $$->child[1] = $3;
                        }
                    | term { $$ = $1; }
                    ;

addop               : PLUS  { $$ = PLUS; }
                    | MINUS { $$ = MINUS; }
                    ;

term                : term mulop factor
                        {
                            $$ = newExp(OP_K);
                            $$->op = $2;
                            $$->child[0] = $1;
                            $$->child[1] = $3;
                        }
                    | factor { $$ = $1; }
                    ;

mulop               : MULTI  { $$ = MULTI; }
                    | DIVIDE { $$ = DIVIDE; }
                    ;

factor              : LPAREN expression RPAREN { $$ = $2; }
                    | var { $$ = $1; }
                    | call { $$ = $1; }
                    | NUM
                        {
                            $$ = newExp(CONST_K);
                            $$->type = INT_T;
                            strcpy($$->val, $1);
                        }
                    ;

call                : ID LPAREN args RPAREN
                        {
                            $$ = newExp(CALL_K);
                            strcpy($$->val, $1);
                            $$->child[0] = $3;
                        }
                    ;

args                : args_list { $$ = $1; }
                    | /*empty*/ { $$ = NULL; }
                    ;

args_list           : args_list COMMA expression
                        {
                            $$ = newExp(ARGS_K);
                            $$->child[0] = $1;
                            $$->child[1] = $3;
                        }
                    | expression { $$ = $1; }
                    ;
