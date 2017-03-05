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

//returns the next token in source file
int getToken();

//kick off point for parser
void parse();

//prints token
void printToken( int tokenType, string tokenStr );


#endif
