/* cminus.cpp                                   */
/* main file for the cminus compiler            */
/* Created by Jeffrey-David Kapp; 0832671       */
/* 1 March 2017 - Last modified 1/3/2017        */

#include "cminus.h"
#include "y.tab.h"

extern string tokenString;
FILE * sourceFile;
FILE * outputFile;
int lineno = 0;

int main( int argc, char* argv[] ) {

    if ( argc < 2 ) {
        cerr << "ERROR: Filename required\n";
        cerr << "Usage: cm <filename> [-a]\n";
        exit(1);
    }

    sourceFile = fopen(argv[1], "r");

    if ( sourceFile == NULL ) {
        cerr << "ERROR: File not found: " << argv[1] << "\n";
        exit(1);
    }

    outputFile = stdout;

    parse();

    return 1;
}

void printToken( int tokenType, string tokenStr ) {
    switch( tokenType ) {
        case ELSE:
        case IF:
        case INT:
        case RETURN:
        case VOID:
        case WHILE:
            fprintf(outputFile, "Reseverd word: %s \n", tokenStr.c_str() );
            break;

        case ID: fprintf(outputFile, "Indetifier %s \n", tokenStr.c_str() ); break;
        case NUM: fprintf(outputFile, "Number %s \n", tokenString.c_str() ); break;

        case PLUS:
        case MINUS:
        case MULTI:
        case DIVIDE:
        case LT:
        case GT:
        case LE:
        case GE:
        case EQ:
        case NE:
        case ASSIGN:
        case SEMICLN:
        case COMMA:
        case LPAREN:
        case RPAREN:
        case LBRACKET:
        case RBRACKET:
        case LBRACE:
        case RBRACE:
        case OPENCOMMENT:
        case CLOSECOMMENT:
            fprintf(outputFile, "Special Symbol %s \n", tokenString.c_str() );
            break;
        case ERROR: fprintf(outputFile, "Error %s \n", tokenString.c_str() );
    }
}
