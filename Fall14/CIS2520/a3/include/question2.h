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

typedef struct heap_node {
	struct heap_node * parent;
	struct heap_node * left_child;
	struct heap_node * right_child;

	int * key; //node's key value, the sum of the first three integers
	int * array; //object's array
} heap_node;

/* fileIO
 * Will construct a 20x10 array from a file
 * Parameters: none
 * Returns: completed 2D array
*/
int ** fileIO();

/* constructHeap
 * will build a heap using the given array
 * Parameters: array - array to be built from
 * Returns: completed heap
*/
heap_node * constructHeap( int ** array );

/* newNode
 * allocated and initialise a new node
 * Parameters: array - the array for that node
 * Returns: completed node
*/
heap_node * newNode( int * array );

/* addToHeap
 * Will add the node to the heap using downheap
 * Parameters: 	heap - the heap to be added to
 *				node - the node to be added
 * Returns: new root of the heap
*/
heap_node * addToHeap( heap_node * heap, heap_node * node );

/* displayHeap
 * displays the heap as a 20x10 array, with the 20 rows ordered in array notation for a heap.
 * Parameters: 	node - the heap to print
 *				level - level of the heap currently being operated on
 *				displayArray - 2d array used for display
 * Returns: nothing
*/
void displayHeap( heap_node	* node );

/* destroyHeap
 * heap goes boooooooooooom
 * Parameters: heap - heap to go boom
 * Returns: nothing survives
*/
void destroyHeap( heap_node * heap );