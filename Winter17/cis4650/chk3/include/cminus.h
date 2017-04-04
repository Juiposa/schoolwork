/* cminus.h                                     */
/* Master header file for the cminus compiler   */
/* Created by Jeffrey-David Kapp; 0832671       */
/* 1 March 2017 - Last modified 6/3/2017        */


#ifndef _CMINUS_H_
#define _CMINUS_H_

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <unordered_map>

using namespace std;

extern FILE * sourceFile;
extern FILE * outputFile;
extern string tokenString;
extern int lineno;

//AST for the Cminus lanaguage - from lecture notes
typedef enum { STMT_K, EXP_K, DEC_K } NodeKind;

typedef enum { IF_K, RETURN_K, WHILE_K, CMPD_K } StmtKind;

typedef enum { OP_K, CONST_K, ID_K, CALL_K, ARGS_K } ExpKind;

typedef enum { VAR_K, FUN_K, PARAM_K } DecKind;

typedef enum { INT_T, VOID_T } VarType;

#define MAXCHILDREN 3

typedef struct astTreeNode {
    astTreeNode * child[MAXCHILDREN];

    astTreeNode * sibling;

    int pos;

    NodeKind node_kind;

    union { StmtKind statement; ExpKind expression; DecKind declaration; } kind;

    int op; //operation type
    char * val; //function or variable name
    VarType type; //variable type
    int size; //array size
    char * function; //parent function

    //level and scope ID
    int level;
    int scope;

    //offset
    //vars; where in dmem the var is sitting, relative to frame pointer
    //func; where in imem the function start is sitting, absolute
    int offset;

    //declaration flags
    bool func;
    bool array;

} astTreeNode;
//END AST

//Symbol Table Tree
typedef struct symbolTableTree {
    symbolTableTree * parent;
    unordered_map<string, astTreeNode*> symbolTable;
} stt;

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

//semantic checker
bool buildSymbolTable( astTreeNode * tree, int level, bool func, bool print );
void delNodes( int level );
bool typeChecking( astTreeNode * tree );
VarType checkOperation( astTreeNode * tree );


#endif
