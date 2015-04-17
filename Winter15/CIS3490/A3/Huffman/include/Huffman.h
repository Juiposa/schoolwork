/************************************
Jeffrey-David Kapp
CIS3490 Assignment 3 Huffman Encoding
26 February 2015
************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct huff_node {
	int freq; 
	char chr_val;
	char * code;
	struct huff_node * left;
	struct huff_node * right;
} huff_node;

/* readFile
 * reads a file on character at a time and counting sorts into an array of tree nodes
 * Parameters: 	fp - file to be read
 * Returns: array of nodes containing a charcter's freq
*/
huff_node ** readFile(FILE * fp);

/* newNode
 * initiaises new node with provided character
 * Parameters:	inChar - character to build new node for
 * Returns: initialised node
*/
huff_node * newNode( char inChar, huff_node * left, huff_node * right ); 

/* encode
 * assigns codes to characters in a tree; called recursively
 * Parameters:	tree - tree to encode
 *				code - code supplied by parent
 * Returns: nothing
*/
void encode( huff_node * tree, char * code );

/* getCompRatio
 * Determines the compression ratio of a huffman tree
 * Parameters: 	tree - tree to examine
 * Returns: compression ratio as a floating point number
*/
float getCompRatio( huff_node * tree );

/* countFreq
 * count total bit length for each character, that is freq * code length; and totals them; works recursively
 * Parameters: 	tree - tree to total
 * Returns:	how large the compressed file would be in bits
*/
float countBitLength( huff_node * tree );

/* printNode
 * prints a nodes info to a given stream
 * Parameters: 	fp - stream to print to
 *				node - node to print
 * Returns: nothing
*/
void printNode( FILE * fp, huff_node * node );

/* buildHuffTree
 * build a huffman tree from a given array
 * Parameters: array - array to build from 
 * Returns: root node of a completed huffman tree
*/
huff_node * buildHuffTree( huff_node ** array );
/* nodeCount
 * counts the number of node remaining in an array
 * Parameters: array - array to count from
 * Returns: number of none null value in the array
*/
int nodeCount( huff_node ** array );

/* printTree
 * prints a tree in order
 * Parameters:	fp - stream to print to
 *				tree - tree to print
 * Returns: nada
*/
void printTree( FILE * fp, huff_node * tree );

/* destroyTree
 * frees all memory allocation for a tree
 * Parameters:	tree - tree we want to destroy
 * Returns: zilch
*/
void destroyTree( huff_node * tree );