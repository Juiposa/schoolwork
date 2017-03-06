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
    astTreeNode * outTree;

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

    outTree = parse();
    fprintf(outputFile, "\n\nAbstract Syntax Tree:\n" );
    printTree(outTree);

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

        case ID: fprintf(outputFile, "Identifier %s \n", tokenStr.c_str() ); break;
        case NUM: fprintf(outputFile, "Number %s \n", tokenString.c_str() ); break;

        case PLUS: fprintf(outputFile, "+\n"); break;
        case MINUS: fprintf(outputFile, "-\n"); break;
        case MULTI: fprintf(outputFile, "*\n"); break;
        case DIVIDE: fprintf(outputFile, "/\n"); break;
        case LT: fprintf(outputFile, "<\n"); break;
        case GT: fprintf(outputFile, ">\n"); break;
        case LE: fprintf(outputFile, "<=\n"); break;
        case GE: fprintf(outputFile, ">=\n"); break;
        case EQ: fprintf(outputFile, "==\n"); break;
        case NE: fprintf(outputFile, "!=\n"); break;
        case ASSIGN: fprintf(outputFile, "=\n"); break;
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
        case ERROR:
            fprintf(outputFile, "Error %s \n", tokenString.c_str() );
            break;
        default:
            fprintf(outputFile, "Unrecognised token\n" );
            break;

    }
}

astTreeNode * newStmt(StmtKind stmt) {
    astTreeNode * newNode = (astTreeNode*)malloc(sizeof(astTreeNode));
    if ( newNode == NULL ) {
        fprintf(outputFile, "Allocation error at line %d\n", lineno );
        return NULL;
    }
    for( int i = 0; i<MAXCHILDREN; i++ )
        newNode->child[i] = NULL;
    newNode->sibling = NULL;
    newNode->node_kind = STMT_K;
    newNode->kind.statement = stmt;
    newNode->pos = lineno;
    newNode->attr.val = (char*)malloc(sizeof(char)*40);

    return newNode;
}

astTreeNode * newExp(ExpKind expr) {
    astTreeNode * newNode = (astTreeNode*)malloc(sizeof(astTreeNode));
    if ( newNode == NULL ) {
        fprintf(outputFile, "Allocation error at line %d\n", lineno );
        return NULL;
    }
    for( int i = 0; i<MAXCHILDREN; i++ )
        newNode->child[i] = NULL;
    newNode->sibling = NULL;
    newNode->node_kind = EXP_K;
    newNode->kind.expression = expr;
    newNode->pos = lineno;
    newNode->attr.val = (char*)malloc(sizeof(char)*40);

    return newNode;
}

astTreeNode * newDec(DecKind dec) {
    astTreeNode * newNode = (astTreeNode*)malloc(sizeof(astTreeNode));
    if ( newNode == NULL ) {
        fprintf(outputFile, "Allocation error at line %d\n", lineno );
        return NULL;
    }
    for( int i = 0; i<MAXCHILDREN; i++ )
        newNode->child[i] = NULL;
    newNode->sibling = NULL;
    newNode->node_kind = DEC_K;
    newNode->kind.declaration = dec;
    newNode->pos = lineno;
    newNode->attr.val = (char*)malloc(sizeof(char)*40);

    return newNode;
}

//copied directly from the tiny parser and modified to work here
/* used by printTree to store current number of spaces to indent
 */
static int indentno = 0;

/* macros to increase/decrease indentation */
#define INDENT indentno+=4
#define UNINDENT indentno-=4

/* printSpaces indents by printing spaces */
static void printSpaces(void)
{
    int i;
    for (i=0;i<indentno;i++)
        fprintf(outputFile," ");
}

void printTree( astTreeNode * tree ) {
    INDENT;
    for ( ; tree != NULL; tree = tree->sibling ) {
        printSpaces();
        if( tree->node_kind == STMT_K ) {
            switch( tree->kind.statement ) {
                case IF_K:
                    fprintf(outputFile, "If\n" );
                    break;
                case RETURN_K:
                    fprintf(outputFile, "Return\n" );
                    break;
                case WHILE_K:
                    fprintf(outputFile, "While\n" );
                    break;
                case CMPD_K:
                    fprintf(outputFile, "Compount Statement\n" );
            }
        } else if ( tree->node_kind == EXP_K ) {
            switch ( tree->kind.expression ) {
                case OP_K:
                    fprintf(outputFile, "Operation: " );
                    printToken(tree->attr.op, "\0"); //idea lifted from tiny parser
                    break;
                case CONST_K:
                    fprintf(outputFile, "Const: %s\n", tree->attr.val );
                    break;
                case ID_K:
                    fprintf(outputFile, "Id: %s\n", tree->attr.val );
                    break;
                case CALL_K:
                    fprintf(outputFile, "Function call: %s\n", tree->attr.val );
                    break;
                case ARGS_K:
                    fprintf(outputFile, "Function argument: %s\n", tree->attr.val );
                    break;
            }
        } else if ( tree->node_kind == DEC_K ) {
            switch ( tree->kind.declaration ) {
                case VAR_K:
                    fprintf(outputFile, "Var dec: %s\n", tree->attr.val );
                    break;
                case FUN_K:
                    fprintf(outputFile, "Function declaration: %s\n", tree->attr.val );
                    break;
                case PARAM_K:
                    fprintf(outputFile, "Param dec: %s\n", tree->attr.val );
                    break;

            }
        }
        for ( int i = 0; i < MAXCHILDREN; i++ ) {
            printTree(tree->child[i]);
        }
    }
    UNINDENT;
}
