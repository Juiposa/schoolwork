/* scanner.cpp                                                  */
/* Main source file for the SGML scanner                        */
/* Created by Jeffrey-David Kapp; 0832671                       */
/* 25 January 2017 - Last modifed 1/2/2017                      */


#include "sgml.h"
#include "Tag.h"


extern string yylval;
extern FILE * yyin;
extern FILE * yyout;

int main( int argc, char* argv[] ) {
    yyin = stdin;
    yyout = stdout;
    stack<Tag*> tagStack;
    Tag * newTag;
    token_t tokenType;
    while( (tokenType = getToken()) != ENDFILE ) {
        if ( tokenType == OPEN_TAG ) { //open tags get pushed onto the stack
            newTag = new Tag(yylval);
            if ( newTag->tagType == P && tagStack.top()->tagType == IRRELEVANT ) { //paragraph tags are only relevant if they're contained within another relevant tag
                newTag->tagType = IRRELEVANT;
            }
            tagStack.push(newTag);
            //DEBUG fprintf(stdout, "OPEN TAG: %s | %s\n", yylval.c_str(), newTag->value.c_str() );
            if ( newTag->tagType != IRRELEVANT ) { //only relevant tags are printed
                printToken(OPEN_TAG, newTag->value);
            }
        } else if ( tokenType == CLOSE_TAG ) { //close tags pop top of stack off and checks if it matches an open tag
            newTag = new Tag(yylval);
            if ( newTag->value.compare(tagStack.top()->value) == 0 ) { //close tag matches an open tag
                if ( newTag->tagType != IRRELEVANT ) { //only relevant tags are printed
                    printToken( CLOSE_TAG, newTag->value );
                }
                delete newTag;
                newTag = tagStack.top();
                tagStack.pop();
                delete newTag;
            } else { //close tag doesn't match an open tag; indicating a syntax error
                fprintf( yyout, "ERROR: Invalid Syntax on close tag; Expecting %s, but got %s\n", tagStack.top()->value.c_str(), newTag->value.c_str() );
                delete newTag;
            }
        } else if ( tagStack.top()->tagType != IRRELEVANT ) { //print the token if its not wrapped in an IRRELEVANT tag
            printToken( tokenType, yylval );
        }
    }
    if(!tagStack.empty()) {
        fprintf( yyout, "ERROR: Unclosed tags remain:\n" );
        while(!tagStack.empty()) {
            fprintf( yyout, "%s ", tagStack.top()->value.c_str() );
            newTag = tagStack.top();
            tagStack.pop();
            delete newTag;
        }
        fprintf(stdout, "\n" );
    }
    return 0;
}

//prints a token
void printToken( token_t tokenType, string value ) {
    switch (tokenType) {
        case OPEN_TAG:
            fprintf(yyout, "OPEN-%s\n", value.c_str() );
            break;
        case CLOSE_TAG:
            fprintf(yyout, "CLOSE-%s\n", value.c_str() );
            break;
        case WORD:
            fprintf(yyout, "WORD(%s)\n", value.c_str() );
            break;
        case NUMBER:
            fprintf(yyout, "NUMBER(%s)\n", value.c_str() );
            break;
        case PUNCTUATION:
            fprintf(yyout, "PUNCTUATION(%s)\n", value.c_str() );
            break;
        case HYPHENATED:
            fprintf(yyout, "HYPHENATED(%s)\n", value.c_str() );
            break;
        case APOSTROPHIZED:
            fprintf(yyout, "APOSTROPHIZED(%s)\n", value.c_str() );
            break;
    }
}

//destroys whole stack
void destroyStack( stack<Tag*> stack ) {
    Tag * tag;
    while( !stack.empty() ) {
        tag = stack.top();
        stack.pop();
        delete tag;
    }
    return;
}
