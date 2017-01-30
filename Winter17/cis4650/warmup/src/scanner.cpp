/* scanner.cpp                                                  */
/* Main source file for the SGML scanner                        */
/* Created by Jeffrey-David Kapp; 0832671                       */
/* 25 January 2017 - Last modifed 25/1/2017                     */


#include "sgml.h"


extern string yylval;
extern FILE * yyin;
extern FILE * yyout;

int main( int argc, void* argv[] ) {
    yyin = stdin;
    yyout = stdout;
    stack<Tag*> tagStack;
    Tag * newTag;
    token_t tokenType;
    while( (tokenType = getToken() ) != EOF ) {
        if ( tokenType == OPEN_TAG ) { //open tags get pushed onto the stack
            newTag = new Tag(yyval);
            tagStack.push(newTag);
            if ( newTag->tagType != IRRELEVANT ) { //only relevant tags are printed
                printToken(OPEN_TAG, newTag->value);
            }
        } else if ( tokenType == CLOSE_TAG ) { //close tags pop top of stack off and checks if it matches an open tag
            newTag = new Tag(yyval);
            if ( newTag->tagType == tagStack.top->tagType ) { //close tag matches an open tag
                if ( newTag->tagType != IRRELEVANT ) { //only relevant tags are printed
                    printToken( CLOSE_TAG, newTag->value );
                }
                delete newTag;
                newTag = tagStack.top();
                tagStack.pop();
                delete newTag;
            } else { //close tag doesn't match an open tag; indicating a syntax error
                fprintf( stdout, "ERROR: Invalid Syntax on close tag; Expecting %s, but got %s\n", tagStack.top()->value.c_str(), newTag->value.c_str() );
                delete newTag;
            }
        } else if ( tagStack.top()->tagType != IRRELEVANT ) { //print the token if its not wrapped in an IRRELEVANT tag
            printToken( tokenType, yyval );
        }
    }
    if(!tagStack.empty()) {
        fprintf( stdout, "ERROR: Unclosed tags remain:\n" );
        while(!tagStack.empty()) {
            fprintf( stdout, "%s ", tagStack.top()->value );
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

}

//destroys whole stack
void destroyStack( TokenStack * stack ) {
    Tag * tag;
    while( !stack.empty() ) {
        tag = stack.top();
        stack.pop();
        delete tag;
    }
    return;
}
