/*****************
Jeffrey-David Kapp
25 October 2014
0832671
Assignment 3
CIS 2520
*****************/

#include "question1.h"

tree_node * parsing( char * inputStr ) {
	tree_node * newTree;

	newTree = newNode( inputStr, NULL ); //root with the entire relation as a value

	parseNode( newTree );

	return newTree;
}

void parseNode( tree_node * node ) {
	int level = 0; //level of the relation, and/or the tree, the pointer is sitting at, denoted by open and close parenthese
	int operation = 0; //operators postion in the string
	char * tempString;
	int i = 0; //iterator
	
	for ( i = 1; i < strlen( node->string_val ); i++ ) {
		if ( node->string_val[i] == '(' ) { //if the curr char is an open paren
			level++; //we go down a level
		} else if ( node->string_val[i] == ')' ) { // if it is a close paren
			level--; //we go up a level
		} else if ( ( node->string_val[i] == '+' || node->string_val[i] == '-' || node->string_val[i] == '/' || node->string_val[i] == '*' ) && level == 0 ) { // if characters is an operator and we are on level 0
			operation = i; //the operator is at the current character
			i = strlen( node->string_val ); // we exit the loop
		} else if ( i == strlen( node->string_val ) - 1 ) { //if none of these conditons are satisfied by the end of the loop, we are necessarily at a single operator
			strcpy( node->value, node->string_val ); //we copy our single operator to the value string
			*node->numericVal = atof(node->value);
			return; //and we jump up the recursive tree
		}
	}
	tempString = malloc(sizeof(char) * 100);
	memcpy( tempString, &node->string_val[1], operation - 1 ); //get string left of operator, excluding the first paren
	node->left_child = newNode( tempString, node );
	free(tempString);
	tempString = malloc(sizeof(char) * 100);
	memcpy( tempString, &node->string_val[operation + 1], strlen(node->string_val) - operation - 2 ); //get string right of operator, excluding the last paren
	node->right_child = newNode( tempString, node );

	node->value[0] = node->string_val[operation];
	//recursive calls to parse both children
	parseNode( node->left_child );
	parseNode( node->right_child ); 

	free(tempString);
}