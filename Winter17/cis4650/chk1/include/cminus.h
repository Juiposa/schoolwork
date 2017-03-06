/* cminus.h                                     */
/* Master header file for the cminus compiler   */
/* Created by Jeffrey-David Kapp; 0832671       */
/* 1 March 2017 - Last modified 1/3/2017        */


#ifndef _CMINUS_H_
#define _CMINUS_H_

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <iostream>
#include <string>

using namespace std;

extern FILE * sourceFile;
extern FILE * outputFile;
extern string tokenString;
extern int lineno;

//AST for the Cminus lanaguage
typedef enum { STMT_K, EXP_K, DEC_K } NodeKind;

typedef enum { IF_K, RETURN_K, WHILE_K, CMPD_K } StmtKind;

typedef enum { OP_K, CONST_K, ID_K, CALL_K, ARGS_K } ExpKind;

typedef enum { VAR_K, FUN_K, PARAM_K } DecKind;

#define MAXCHILDREN 3

typedef struct astTreeNode {
    astTreeNode * child[MAXCHILDREN];

    astTreeNode * sibling;

    int pos;

    NodeKind node_kind;

    union { StmtKind statement; ExpKind expression; DecKind declaration; } kind;

    //add and int val storage to this for future checkpoints
    union { int op; char * val; } attr;
} astTreeNode;

//END AST

//AST manipulation functions
astTreeNode * newStmt(StmtKind stmt);

astTreeNode * newExp(ExpKind expr);

astTreeNode * newDec(DecKind dec);

//Utility functions
//returns the next token in source file
int getToken();

//kick off point for parser
astTreeNode * parse();

//prints token
void printToken( int tokenType, string tokenStr );

//prints the AST
void printTree( astTreeNode * tree );


#endif
