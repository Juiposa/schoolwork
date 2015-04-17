/*******************
Jeffrey-David Kapp
0832671
27 March 2015
CIS3110 Assignment 3
********************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define CLEARMEMORY(x,y) { for( i = x; i < y; i++ ) memory[i] = 0; } //macro for clearing memory
#define SETMEMORY(x,y) { for( i = x; i < y; i++ ) memory[i] = 1; } //macro for setting memory 

typedef struct process {
	char * name; 
	int size; //size in memory in MB
	int start, end; //memory address start and end
	int loaded; //number of time it has been loaded
	struct process * next; //next process in any given queue
} process;

/* countHoles
 * counts the holes in a set of memory
 * Parameter: 	memory - array symbolising memory
 * Returns: number of holes in memory array
*/
int countHoles( int memory[128] );

/* holeSize
 * counts the sixe of a hole at a given index
 * Parameters: 	memory - array symbolising memory
 *				index - where the begining of the hole is
 * Returns: the size of the hole, 0 if given a bad index
*/
int holeSize( int memory[128], int index );

/* nextHole
 * finds the next hole in memory
 * Parameters:	list - memory to search
 *				index - index of memory to start search from
 * Returns: index of the begining of the hole
*/
int nextHole( int memory[128], int index );

/* newProcess
 * initialises a new process
 * Parameters:	name - new processes pid
 *				size - size of the process in MB
 * Returns: new initialised process
*/
process * newProcess( char * name, int size );

/* reafFile
 * will parse file and return a new queue
 * Parameters:	fp - fiel to read from
 * Returns: a new queue
*/
process * readFile( FILE * fp );

/* addToQueue
 * adds and item to the end of queue
 * Parameters:	list - list to add to
 *				toAdd - itemt to append to end of list
 * Returns: pointer to new list header
*/
process * addToQueue( process * list, process * toAdd  );

/* popFromQueue
 * pops the item from the top of a queue
 * Parameters:	list - list to pop from
 * Returns: first item of the list
*/
process * popFromQueue( process ** list );

/* destroyQueue
 * Destroys and frees memory used by a given list
*/
void destroyQueue( process * list );

void print( process * list );

