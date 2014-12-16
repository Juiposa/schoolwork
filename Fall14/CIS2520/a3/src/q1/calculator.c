/*****************
Jeffrey-David Kapp
25 October 2014
0832671
Assignment 3
CIS 2520
*****************/

#include "question1.h"

int main( int argc, char * argv[] ) {

	tree_node * tree; //binary expression tree
	float * variables = malloc(sizeof(float)*100); //variable array
	for ( int i = 0; i < 100; i++ ) {
		variables[i] = 0.0; //setting all to 0.0
	}

	char inputVar[100]; // input variable, user's choices for menu control

	if ( argc != 2 ) { //making sure only two thing were entered at the commandline, the program name and the equation to be evaluated
		printf("Proper usage: %s equation \n", argv[0] );
	} else { //else we can function normally
		tree = parsing( argv[1] ); //parsing the string
		if ( tree == NULL ) { //function will return null if input is invalid
			printf("Input is invalid.\nEquation must be fully parenthesised and must contain at least one operation.\n");
		} else { //if input is valid
			do { //loop until the user wants otherwise
				printOptions();
				fgets( inputVar, 100, stdin );

				switch ( inputVar[0] ) {
					case '1': //display tree
						break;
					case '2': //preorder notation
						preorder( tree );
						break;
					case '3': //inorder notation
						inorder( tree );
						break;
					case '4': //postorder notation
						postorder( tree );
						break;
					case '5': //variable update
						variables = updateVariable( variables );
						break;
					case '6': //calculate
						calculate( tree, variables );
						printf("Result: %.2f\n", *tree->numericVal );
						break;
					case '7': //exit
						destroyTree( tree );
						break;
					default:
						printf("Invalid input.\n");
						break;
				}

			} while ( inputVar[0] != '7' ); 
		}
	}
	free(variables);
	return 1;
}

void preorder( tree_node * node ) {
	if ( node->left_child != NULL && node->right_child != NULL ) { //if the children have content
		printf(" %s", node->value );

		preorder( node->left_child ); //recursive call for first the left then right child
		preorder( node->right_child );
	} else {
		printf(" %s", node->value );
	}
}

void inorder( tree_node * node ) {
	printf("%s\n", node->string_val ); //not cheating, totally not
}

void postorder( tree_node * node ) {
	if ( node->left_child == NULL && node->right_child == NULL ) { //if both children are null, node is an operator
		printf(" %s", node->value );
	} else { // the children are not null
		postorder( node->left_child ); //recursive call for first the left then right child
		postorder( node->right_child );

		printf(" %s", node->value ); //print its own value after descendents are done
	}
}

void calculate( tree_node * node, float * variables ) {
	float operand1 = 0, operand2 = 0; //operands for the relation
	if ( node->left_child == NULL && node->right_child == NULL ) { //if the current node is a leaf
		return; //we go back up a level, nothing we can do here
	} else {
		calculate( node->left_child, variables ); //recursive call for each child
		calculate( node->right_child, variables );

		//after that is done, we calculate

		//setting up the operands, checking if they are variables or not and pulling their values if they are
		if ( node->left_child->value[0] == 'x' ) {
			operand1 = variables[atoi( &node->left_child->value[1])];
		} else {
			operand1 = *node->left_child->numericVal;
		}
		if ( node->right_child->value[0] == 'x' ) {
			operand2 = variables[atoi( &node->right_child->value[1])];
		} else {
			operand2 = *node->right_child->numericVal;
		}

		switch ( node->value[0] ) { //whichever operation we need to do
			case '+':
				*node->numericVal =  operand1 + operand2;
				break;
			case '-':
				*node->numericVal = operand1 - operand2;
				break;
			case '/':
				*node->numericVal = operand1 / operand2;
				break;
			case '*':
				*node->numericVal = operand1 * operand2;
				break;
		}
	}
}


float * updateVariable( float * variables ) {
	char inputStr[100];
	char * varName;
	char * newValue;
	int variableIndex = 0;

	printf("Input a variable and its new value.\n");
	printf("variable_name, new_value\n");
	fgets( inputStr, 100, stdin );

	if ( inputStr[0] != 'x' ) { //if it is not in the form xX
		printf("Variable must be in the form xX, where 'X' is any natural number.\n");
	} else {
		varName = strtok( inputStr, ", " ); //tokenising the input string to get the two values we need
		newValue = strtok( NULL, ", ");

		variableIndex = atoi( &varName[1] ); //chopping the x off to get the array index
		variables[variableIndex] = atof(newValue); //putting new value into that position 
	}
	return variables;
}

void printOptions() {
	printf("\nSelect an option\n");
	printf("1. Display\n");
	printf("2. Preorder\n");
	printf("3. Inorder\n");
	printf("4. Postorder\n");
	printf("5. Update\n");
	printf("6. Calculate\n");
	printf("7. Exit\n");
}