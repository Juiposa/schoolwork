#include "cminus.h"
#include "emitTM.h"
#include "y.tab.h"

FILE * tmfile;
int emitLocation = 0; //iaddr of instruction
int& el = emitLocation;
extern unordered_map<string, astTreeNode*> symbolTable;

void emitTM( astTreeNode * tree, string filename ) {
    ostringstream tm;
    tm << filename << ".tm";
    tmfile = fopen(tm.str().c_str(), "w");

    astTreeNode * outputFunc = newDec(FUN_K);
    strcpy(outputFunc->val, "output");
    outputFunc->level = 0;
    outputFunc->offset = 7;
    symbolTable.insert({"output", outputFunc});
    astTreeNode * inputFunc = newDec(FUN_K);
    strcpy(inputFunc->val, "input");
    inputFunc->level = 0;
    inputFunc->offset = 4;
    symbolTable.insert({"input", inputFunc});

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
    emitRM("LDA", 7, symbolTable.at("main")->offset-el-1, 7, "jump to main"); el++;
    emitRM("LD", 5, 0, 5, "pop frame"); el++;
    emitRO("HALT", 0, 0, 0, ""); el++;
    fprintf(tmfile, "* END: Finale\n");

    fclose(tmfile);
}

int nodeEmit( astTreeNode * tree, int offset, int level, bool func ) {
    for ( ; tree != NULL; tree = tree->sibling ) {
        switch(tree->node_kind) {
            case DEC_K:
                switch(tree->kind.declaration) {
                    case VAR_K:
                    case PARAM_K:
                        tree->level = level;
                        fprintf(tmfile, "* Processing variable %s OFFSET %d\n", tree->val, offset );
                        if( tree->type == INT_T ) { //simple allocation for normal vars
                            tree->offset = offset;
                            offset--;
                        } else if ( tree->array ) {
                            tree->offset = offset;
                            offset-=tree->size;
                        }
                        symbolTable.insert({ tree->val, tree });
                        if( tree->kind.declaration == PARAM_K ) { //params need to pull thier passed in data

                        }
                        break;
                    case FUN_K:
                        tree->level = level;
                        int skip = el; el++; //current loc is the skip line

                        tree->offset = el;
                        symbolTable.insert({ tree->val, tree });
                        fprintf(tmfile, "* FUNCTION START: %s\n", tree->val );
                        emitRM("ST", 0, -1, 5, "store return"); el++;
                        for ( int i = 0; i < MAXCHILDREN; i++ ) {
                            nodeEmit(tree->child[i], offset, level+1, true );
                        }
                        delNodes(level+1);
                        //function done
                        int tempel = el; el = skip;
                        emitRM("LDA", 7, tempel-skip-1, 7, "skip function"); //print skip
                        fprintf(tmfile, "* FUNCTION END: %s\n", tree->val );
                        el = tempel;
                        break;
                }
                break;
            case STMT_K:
                stmtEmit( tree, offset, level, func );
                break;
            case EXP_K:
                expEmit( tree, offset-1 );
                break;
        }
    }
    return offset;
}

void stmtEmit( astTreeNode * tree, int offset, int level, bool func ) {
    int tempel;
    int skip;
    int controlstart;
    int falsestart;
    switch( tree->kind.statement ) {
        case IF_K:
            fprintf(tmfile, "* if {\n" );
            emitOP(tree->child[0], offset);
            emitRM("LDC", 0, 0, 0, "false"); el++;
            emitRM("LDA", 7, 1, 7, "unconditional jump"); el++;
            emitRM("LDC", 0, 1, 0, "true"); el++;
            skip = el; el++;
            offset = nodeEmit(tree->child[1], offset, level, false ); //print whatever is contained in while
            if( tree->child[2] != NULL ) { //and else case is present
                tempel = el; el = skip;
                emitRM("JEQ", 0, tempel-skip, 7, "if: jump to else");
                el = tempel; skip = el; el++;
                offset = nodeEmit(tree->child[2], offset, level, false );
                tempel = el; el = skip;
                emitRM("LDA", 7, tempel-skip-1, 7, "if: jump past else");
                el = tempel;
            } else {
                tempel = el; el = skip;
                emitRM("JEQ", 0, tempel-skip-1, 7, "if: skip past if block");
                el = tempel;
            }
            fprintf(tmfile, "* if }\n" );
            break;
        case RETURN_K:
            if( tree->child[0] != NULL ) {
                expEmit(tree->child[0], offset);
            }
            emitRM("LD", 7, -1, 5, "return to caller"); el++;
            break;
        case WHILE_K:
            controlstart = el; //while starts here
            fprintf(tmfile, "* while {\n" );
            emitOP(tree->child[0], offset);
            emitRM("LDC", 0, 0, 0, "false"); el++;
            emitRM("LDA", 7, 1, 7, "unconditional jump"); el++;
            emitRM("LDC", 0, 1, 0, "true"); el++;
            skip = el; el++;
            offset = nodeEmit(tree->child[1], offset, level, false ); //print whatever is contained in while
            emitRM("LDA", 7, controlstart-el-1, 7, "while: loop back to top"); el++;
            tempel = el; el = skip;
            emitRM("JEQ", 0, tempel-skip-1, 7, "while: skip past while block");
            el = tempel;
            fprintf(tmfile, "* while }\n" );
            break;
        case CMPD_K:
            if( func == false ) {
                for ( int i = 0; i < MAXCHILDREN; i++ ) {
                    offset = nodeEmit(tree->child[i], offset, level+1, false );
                }
                delNodes(level+1);
            } if ( func == true ) {
                for ( int i = 0; i < MAXCHILDREN; i++ ) {
                    offset = nodeEmit(tree->child[i], offset, level, false );
                }
            }
            break;
    }
}

void expEmit( astTreeNode * tree, int offset ) {
    switch( tree->kind.expression ) {
        case ID_K:
            fprintf(tmfile, "* id {\n" );
            fprintf(tmfile, "* lookup ID %s\n", tree->val );
            emitRM("LD", 0, symbolTable.at(tree->val)->offset, 5, "load id value"); el++;
            fprintf(tmfile, "* id }\n" );
            break;
        case CONST_K:
            emitRM("LDC", 0, atoi(tree->val), 0, "load const"); el++;
            break;
        case OP_K:
            emitOP(tree, offset);
            break;
        case CALL_K:
            fprintf(tmfile, "* { call to func %s\n", tree->val );
            if(tree->child[0] != NULL ) { //arguments are present
                int tempoffset = offset;
                if(tree->child[0]->child[0] != NULL ) {
                    for(astTreeNode * tempTree = tree->child[0]->child[0]; tempTree != NULL; tempTree = tempTree->sibling ) {
                        expEmit(tempTree, tempoffset);
                        emitRM("ST", 0, tempoffset-2, 5, "store arg val"); el++;
                        tempoffset--;
                    }
                    for(astTreeNode * tempTree = tree->child[0]->child[1]; tempTree != NULL; tempTree = tempTree->sibling ) {
                        expEmit(tempTree, tempoffset);
                        emitRM("ST", 0, tempoffset-2, 5, "store arg val"); el++;
                        tempoffset--;
                    }
                } else {
                    expEmit(tree->child[0], tempoffset);
                    emitRM("ST", 0, tempoffset-2, 5, "store arg val"); el++;
                    tempoffset--;
                }
            }
            string funcString = tree->val;
            emitRM("ST", 5, offset, 5, "push frame pointer"); el++;
            emitRM("LDA", 5, offset, 5, "push frame"); el++;
            emitRM("LDA", 0, 1, 7, "load reg(0) with return pointer"); el++;
            emitRM("LDA", 7, symbolTable[funcString]->offset-el-1, 7, "jump to func"); el++;
            emitRM("LD", 5, 0, 5, "pop frame"); el++;
            fprintf(tmfile, "* } call to func %s\n", tree->val );
            break;
    }
}

void emitOP( astTreeNode * tree, int offset ) {
    fprintf(tmfile, "* op {\n" );
    switch(tree->child[0]->kind.expression) { //first child is a
        case ID_K: //var; lookup push left
            fprintf(tmfile, "* id {\n" );
            fprintf(tmfile, "* lookup ID %s\n", tree->child[0]->val );
            if( tree->op == ASSIGN ) { //if it's an assing load address
                emitRM("LDA", 0, symbolTable.at(tree->child[0]->val)->offset, 5, "load id address"); el++;
            } else {
                emitRM("LD", 0, symbolTable.at(tree->child[0]->val)->offset, 5, "load id value"); el++;
            }
            fprintf(tmfile, "* id }\n" );
            break;
        case CONST_K: //const; load left
            emitRM("LDC", 0, atoi(tree->child[0]->val), 0, "load const"); el++;
            break;
        case OP_K: //pull result from that op
            emitOP(tree->child[0], offset-1);
            break;
        case CALL_K:
            expEmit(tree->child[0], offset-1);
            break;
    }
    emitRM("ST", 0, offset, 5, "op: push left"); el++;
    switch(tree->child[1]->kind.expression) {
        case ID_K:
            fprintf(tmfile, "* id {\n" );
            fprintf(tmfile, "* lookup ID %s\n", tree->child[1]->val );
            emitRM("LD", 0, symbolTable.at(tree->child[1]->val)->offset, 5, "load id value"); el++;
            fprintf(tmfile, "* id }\n" );
            break;
        case CONST_K: //const; load left
            emitRM("LDC", 0, atoi(tree->child[1]->val), 0, "load const"); el++;
            break;
        case OP_K: //pull result from that op
            emitOP(tree->child[1], offset-1);
            break;
        case CALL_K:
            expEmit(tree->child[1], offset-1 );
            break;
    }
    emitRM("LD", 1, offset, 5, "load left" ); el++;
    switch(tree->op) {
        case ASSIGN:
            emitRM("ST", 0, 0, 1, "assign: store value"); el++;
            break;
        case PLUS:
            emitRO("ADD", 0, 1, 0, "op +" ); el++;
            break;
        case MINUS:
            emitRO("SUB", 0, 1, 0, "op -" ); el++;
            break;
        case MULTI:
            emitRO("MUL", 0, 1, 0, "op *" ); el++;
            break;
        case DIVIDE:
            emitRO("DIV", 0, 1, 0, "op /" ); el++;
            break;
        case LT:
            emitRO("SUB", 0, 1, 0, "op <" ); el++;
            emitRM("JLT", 0, 2, 7, "branch if true"); el++;
            break;
        case GT:
            emitRO("SUB", 0, 1, 0, "op >" ); el++;
            emitRM("JGT", 0, 2, 7, "branch if true"); el++;
            break;
        case LE:
            emitRO("SUB", 0, 1, 0, "op <=" ); el++;
            emitRM("JLE", 0, 2, 7, "branch if true"); el++;
            break;
        case GE:
            emitRO("SUB", 0, 1, 0, "op >=" ); el++;
            emitRM("JGE", 0, 2, 7, "branch if true"); el++;
            break;
        case EQ:
            emitRO("SUB", 0, 1, 0, "op ==" ); el++;
            emitRM("JEQ", 0, 2, 7, "branch if true"); el++;
            break;
        case NE:
            emitRO("SUB", 0, 1, 0, "op !=" ); el++;
            emitRM("JNE", 0, 2, 7, "branch if true"); el++;
            break;
    }
    fprintf(tmfile, "* op }\n" );
}

void emitRM(  string op, int r, int d, int s, string m ) {
    fprintf(tmfile, "  %d:  %s %d, %d(%d) %s\n", emitLocation, op.c_str(), r, d, s, m.c_str());
}

void emitRO(  string op, int r, int s, int t, string m) {
    fprintf(tmfile, "  %d:  %s %d, %d, %d %s\n", emitLocation, op.c_str(), r, s, t, m.c_str() );
}
