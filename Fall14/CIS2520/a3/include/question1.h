/*****************
Jeffrey-David Kapp
25 October 2014
0832671
Assignment 3
CIS 2520
*****************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//binary tree struct
typedef struct tree_node {
	struct tree_node * parent;
	struct tree_node * left_child;
	struct tree_node * right_child;

	float * numericVal; //numeric value of an operator or an operation and its operators, basically the result of a sub equation
	char * value; // value of the node, whether an operand or a operator
	char * string_val; //string value, only used if operator, displaying the entire sub equation the node represents
} tree_node;

//linked list of all variables

typedef struct variable {
	struct variable * prev;
	struct variable * next;

	char * name; //variable name
	char * value; //variable value
} var;

//parsing.c function declarations
//-------------------------------

/* parsing
 * Will take an user inputed equation and build a binary tree out of it
 * Parameters: inputStr - 	user inputed equation
 * Returns: a completed binary tree; else if input is invalid, null
*///works
tree_node * parsing( char * inputStr );

/* parseTree
 * takes a node and determines its operator or numerical value
 * Paramters: node - value assigned to it as a child of its parent node
 * Returns: nothing - will build the tree from first node
*///works
void parseNode( tree_node * node );

//binarytree.c functions declarations
//-----------------------------------

/* newNode
 * fully allocated new node
 * Parameters: string - string to be set as node's value
 * Returns: new node
*///done
tree_node * newNode( char * string, tree_node * parent );

/* destroyTree
 * trace through the binary tree and destroy it
 * Parameters: tree - tree to be destroyed
 * Returns: nothing
*///todo
void destroyTree( tree_node * tree );

//calculator.c functions declarations
//-----------------------------------

/* preoder
 * display tree in preorder notation - recursive
 * Paramters: node - tree to be displayed
 * Returns: nothing
*/
void preorder( tree_node * node );

/* inorder
 * displays tree in inorder notation
 * Parameters: node - tree to be dispalyed
 * Returns: nothing
*/
void inorder( tree_node * node );

/* postorder
 * displays tree in postorder notation - recursive
 * Parameters: node - tree to be dispalyed
 * Returns: nothing
*/
void postorder( tree_node * node );

/* calculate
 * calculates the total of the relation - recursive
 * Parameters: 	node - active node
 *				variables - list of variable values       
 * Returns: nothing
*/
void calculate( tree_node * node, float * variables );

/* updateVariable
 * updates the value of a variable
 * Parameters: variables - list of variables
 * Returns:	new variable array
*/
float * updateVariable();

/* printOptions
 * prints menu options out to the user
 * Parameters: none 
 * Returns: nothing
*/
void printOptions();

