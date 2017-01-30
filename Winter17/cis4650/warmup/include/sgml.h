/* scanner.h                                                    */
/* Scanner to tokenise and output tags of a SGML document       */
/* Created by Jeffrey-David Kapp; 0832671                       */
/* 25 January 2017 - Last modifed 25/1/2017                     */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <string>
#include <stack>
#include <algorithm>

using namespace std;

typedef enum {
    OPEN_TAG, CLOSE_TAG,

    WORD, NUMBER, APOSTROPHIZED, HYPHENATED, PUNCTUATION,

    EOF
} token_t;

typedef enum {
    TEXT, DATE, DOC, DOCNO, HEADLINE, LENGTH, P,

    IRRELEVANT
} tag_t;

typedef struct TokenStack {
    token_t tokenType;
    tag_t tagType;
    string value;
    TokenStack * next;
} TokenStack;

//prints a token
void PrintToken( token_t tokenType, string value );

//destroys whole stack
void destroyStack( TokenStack * stack );
