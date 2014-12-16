/*****************
Jeffrey-David Kapp
24 November 2014
0832671
Assignment 3
CIS 2520
*****************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct AVL_node {
	struct AVL_node * parent;
	struct AVL_node * left;
	struct AVL_node * right;

	int bf; //balance factor

	char * key; //node key
	int count; //node count
} AVL_node;

/* initialisation
 * Initialise an AVL tree with data from user provided file
 * Parameters:	filename - string containing the filename to be read from
 * Returns: a completed AVL tree
*/
AVL_node * initialisation( char * filename );

/* insert
 * Adds a node to an AVL tree
 * Parameters:	avl_tree - tree to added to
 *				newNode - node to be added to
 * Returns: expanded tree
*/
AVL_node * insert( AVL_node * avl_tree, AVL_node * node );

/* remove
 * removes a given node from a tree
 * Parameters:	node - node to remove
 * Returns: new root of the subtree old node once rooted
*/
AVL_node * removeNode( AVL_node * node );

/* find
 * finds a node and returns it
 * Parameters: 	avl_tree - tree to be searched
 *				key - key of the node to be found
 * Returns: found node, or NO_SUCH_KEY
*/
AVL_node * find( AVL_node * avl_tree, char * key );

/* findAll
 * finds and prints every node above a given frequency
 * Parameters:	avl_tree - tree to be searched
 *				count - lower bound for the search
 * Returns: nothing
*/
void findAll( AVL_node * avl_tree, int count );

/* updateBalanceFactor
 * updates the balance factor of every node of a given tree/subtree
 * Parameters: 	avl_tree - tree to be updated
 * Returns:	nothing
*/
void updateBalanceFactor( AVL_node * avl_tree );

/* height
 * will return the height of a given tree/subtree
 * Parameters: 	avl_tree - tree to be evaluated
 *  			count - current height
 * Returns: integer value of the height
*/
int height( AVL_node * avl_tree, int count );

/* size
 * get the size of a tree
 * Parameters:	avl_tree - tree to get the size of
 * Returns: integer value of the number of nodes in the tree
*/
int size( AVL_node * avl_tree );

/* restructure
 * will restructure a tree so as to be balanced
 * Parameters:	avl_tree - tree to be balanced
 * Returns: root of a balanced tree
*/
AVL_node * restructure( AVL_node * avl_tree );

/* newNode
 * will create a new node from a given key
 * Paramters:	key - character string to serve as the node's key
 * Returns: constructed node
*/
AVL_node * newNode( char * key );

/* destroyNode
 * destroys and frees a given node
 * Parameters: 	node - node to be destroyed
 * Returns: nothing
*/
void destroyNode( AVL_node * node );

/* destroyTree
 * destroys an entire tree
 * Parameters: avl_tree - tree to be destroyed
 * Returns: nothing
*/
void destroyTree( AVL_node * avl_tree );

/* printOptions
 * prints menu options
*/
void printOptions();
