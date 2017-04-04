#include "cminus.h"
#include "emitTM.h"

FILE * tmfile;
int emitLocation = 0; //iaddr of instruction
int& el = emitLocation;
extern unordered_map<string, astTreeNode*> symbolTable;

void emitTM( astTreeNode * tree, char * filename ) {
    ostringstream tm;
    tm << filename << ".tm";
    fprintf(stdout, "FILENAME::::: %s\n", tm.str().c_str() );
    tmfile = fopen(tm.str().c_str(), "w");

    fprintf(tmfile, "* START: Prelude\n");
    emitRM("LD", 6, 0, 0, "load max address"); el++;
    emitRM("LDA", 5, 0, 6, "copy to reg(5)"); el++;
    emitRM("ST", 0, 0, 0, "clear daddr(0)"); el++;
    //
    el = 4;
    fprintf(tmfile, "* START: IO routines\n");
    fprintf(tmfile, "* input\n");
    emitRM("ST", 0, -1, 5, "store return loc"); el++;
    emitRO("IN", 0, 0, 0, "in"); el++;
    emitRM("LD", 7, -1, 5, "return" ); el++;
    fprintf(tmfile, "* output\n");
    emitRM("ST", 0, -1, 5, "store return loc"); el++;
    emitRM("LD", 0, -2, 5, "load output value"); el++;
    emitRO("OUT", 0, 0, 0, "out"); el++;
    emitRM("LD", 7, -1, 5, "return" ); el = 3;
    emitRM("LDA", 7, 7, 7, "jump past i/o");
    fprintf(tmfile, "* END: IO routines\n");
    fprintf(tmfile, "* END: Prelude\n");

    el = 11;

    nodeEmit(tree, -2, 0, false); //1021 ought to be the next available daddr

    fprintf(tmfile, "* START: Finale\n");
    emitRM("ST", 5, -1, 5, "push frame pointer"); el++;
    emitRM("LDA", 5, -1, 5, "push frame"); el++;
    emitRM("LDA", 0, 1, 7, "load reg(0) with return pointer"); el++;
    emitRM("LDA", 7, -35, 7, "jump to main"); el++;
    emitRM("LD", 5, 0, 5, "pop frame"); el++;
    emitRO("HALT", 0, 0, 0, ""); el++;
    fprintf(tmfile, "* END: Finale\n");

    fclose(tmfile);
}

void nodeEmit( astTreeNode * tree, int offset, int level, bool func ) {
    for ( ; tree != NULL; tree = tree->sibling ) {
        switch(tree->node_kind) {
            case DEC_K:
                switch(tree->kind.declaration) {
                    case VAR_K:
                    case PARAM_K:
                        tree->level = level;
                        symbolTable.insert({ tree->val, tree });
                        fprintf(tmfile, "* Processing variable %s\n", tree->val );
                        if( tree->type == INT_T ) { //simple allocation for normal vars
                            tree->offset = offset;
                            offset--;
                        } else if ( tree->type == ARRAY_T ) {
                            tree->offset = offset;
                            offset-=tree->size;
                        }
                        break;
                    case FUN_K:
                        tree->level = level;
                        symbolTable.insert({ tree->val, tree });
                        int skip = el; el++; //current loc is the skip line
                        for ( int i = 0; i < MAXCHILDREN; i++ ) {
                            nodeEmit(tree->child[i], offset, level+1, true );
                        }
                        //function done
                        int tempel = el; el = skip;
                        emitRM("LDA", 7, tempel-skip, 7, "skip function"); //print skip
                        el = tempel;
                        break;
                }
                break;
            case STMT_K:
                stmtEmit( tree, offset-1, stmt );
                break;
            case EXP_K:
                expEmit( tree, offset-1 );
                break;
        }
    }
}

void stmtEmit( astTreeNode * tree, int offset, bool func ) {
    switch( tree->kind.statement ) {
        case IF_K:
            break;
        case RETURN_K:
            break;
        case WHILE_K:
            break;
        case CMPD_K:
            if( func == false ) {
                for ( int i = 0; i < MAXCHILDREN; i++ ) {
                    nodeEmit(tree->child[i], offset, level+1, false );
                }
            } if ( func == true ) {
                for ( int i = 0; i < MAXCHILDREN; i++ ) {
                    nodeEmit(tree->child[i], offset, level, false );
                }
            }
            break;
    }
}

void expEmit( astTreeNode * tree, int offset ) {
    switch( tree->kind.expression ) {
        case CONST_K:
            break;
        case ID_K:
            break;
        case OP_K:
            break;
        case CALL_K:
            break;
        case ARGS_K:
            break;
    }
}

void emitRM(  string op, int r, int d, int s, string m ) {
    fprintf(tmfile, "  %d:  %s %d, %d(%d) %s\n", emitLocation, op.c_str(), r, d, s, m.c_str());
}

void emitRO(  string op, int r, int s, int t, string m) {
    fprintf(tmfile, "  %d:  %s %d, %d, %d %s\n", emitLocation, op.c_str(), r, s, t, m.c_str() );
}
