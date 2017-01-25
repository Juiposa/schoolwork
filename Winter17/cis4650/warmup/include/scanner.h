/* scanner.h                                                    */
/* Scanner to tokenise and output tags of a SGML document       */
/* Created by Jeffrey-David Kapp; 0832671                       */
/* 25 January 2017 - Last modifed 25/1/2017                     */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <string>

using namespace std;

typedef struct TokenStack {
    tag_t tageType;
    TokenStack * next;
} TokenStack;

typedef struct TokenVal {
    string strval;
} TokenVal;

void PrintToken( token_t tokenType, )
