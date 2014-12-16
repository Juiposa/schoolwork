/*****************
Jeffrey-David Kapp
25 October 2014
0832671
Assignment 3
CIS 2520
*****************/

#include "question2.h"

int main() {
	int ** array;
	heap_node * heap;
	int i = 0, j = 0;
	array = fileIO();

	//DEBUG
	for( i = 0; i < 20; i++ ) {
		printf("Key: %d : ", array[i][0] + array[i][1] + array[i][2] );
		for( j = 0; j < 10; j++ ) {
			printf("%d ", array[i][j] );
		}
		printf("\n");
	}

	heap = constructHeap( array );

	displayHeap( heap );

	destroyHeap( heap );

	free(array);
	return 1;
}

int ** fileIO() {
	//boring file IO, nothing special, im sure it makes sense
	FILE * fileToRead;
 	char * inputStr;
 	int i = 0, j = 0;

 	inputStr = (char*)malloc(sizeof(char)*100);
 	int ** array = (int**)malloc(sizeof(int*)*20);
 	for( i = 0; i < 20; i++ ) {
 		array[i] = (int*)malloc(sizeof(int)*10);
 	}

 	fileToRead = fopen("f.dat", "r");

 	if ( fileToRead != NULL ) {
	 	for ( i = 0; i < 20; i++ ) {
	 		fgets( inputStr, 100, fileToRead );
	 		for ( j = 0; j < 10; j++ ) {
	 			if ( j == 0 ) {
	 				array[i][j] = atoi(strtok(inputStr, " "));
	 			} else {
	 				array[i][j] = atoi(strtok(NULL, " "));
	 			}
	 		}
	 	}
	} else {
		printf("Failure in opening file.\n");
	} 

 	free(inputStr);

 	return array;
}

heap_node * constructHeap( int ** array ) {
	heap_node * heap = NULL; //root of the list
	heap_node * newNd; //node that will we added
	int i = 0;
	for ( i = 0; i < 20; i++ ) { //twenty times for twenty nodes
		newNd = newNode( array[i] ); //get a new node
		heap = addToHeap( heap, newNd );
	}

	return heap;
}

heap_node * newNode( int * array ) {
	heap_node * newNd = (heap_node*)malloc(sizeof(heap_node));
	newNd->parent = NULL;
	newNd->left_child = NULL;
	newNd->right_child = NULL;

	newNd->key = malloc(sizeof(int));
	*newNd->key = array[0] + array[1] + array[2];
	newNd->array = array;

	return newNd;
}

heap_node * addToHeap( heap_node * heap, heap_node * node ) {
	heap_node * activeNode;
	if ( heap != NULL ) {
		printf("====INVALUES: Heap Root Key %d; Working Node Key %d\n", *heap->key, *node->key); //DEBUG		
	} else {
		printf("====INVALUES: Heap Root Key NULL; Working Node Key %d\n", *node->key); //DEBUG	
	}
	if ( heap == NULL ) { //if the tree is empty
		printf("Root is null\n"); //DEBUG
		heap = node; //node becomes the root
		return heap;
	} else if ( *heap->key > *node->key ) { //if the root is greater than the node
		printf("Root is larger than working node.\n"); //DEBUG
		activeNode = heap;
		node->left_child = activeNode->left_child; // swap the node into the old root spot
		node->right_child = activeNode->right_child;
		activeNode->left_child->parent = node;
		activeNode->right_child->parent = node;

		activeNode->parent = NULL; //you have no family >:(
		activeNode->left_child = NULL;
		activeNode->right_child = NULL;

		printf("++++++RECURSIVE CALL++++++\n");
		heap = addToHeap( node, activeNode ); //find the old root's new spot in the heap, RECURSION!
		return heap;
	} else if ( *heap->key <= *node->key ) { //else the node is larger that the root
		printf("Root is smaller that working node.\n");
		activeNode = heap;
		do {
			if ( activeNode->left_child == NULL ) { // if the left child is a leaf
				printf("Left child is null\n"); //DEBUG
				activeNode->left_child = node; //set the added node there
				node->parent = activeNode;
				return heap;
			} else if ( activeNode->right_child == NULL ) { //else if the right child is a leaf
				printf("Right child is null\n"); //DEBUG
				activeNode->right_child = node; //same stuff
				node->parent = activeNode;
				return heap;
			//only condition that is capable of executing multiple times, all others terminate the function
			//VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV
			} else  if ( *activeNode->key <= *node->key ) { //if the active node is smaller than the node
				if ( *activeNode->left_child->key - *node->key < *activeNode->right_child->key - *node->key ) { //the left node is closer in value
					printf("Switch active node to = %d\n", *activeNode->left_child->key); //DEBUG
					activeNode = activeNode->left_child; //the left child becomes the new active node
				} else { //the right child being greater or equal is the only other possibility
					printf("Switch active node to = %d\n", *activeNode->right_child->key ); //DEBUG
					activeNode = activeNode->right_child; //the right child becomes the active node
				}
			//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^	
			} else if ( *activeNode->key > *node->key ) { // if the node is smaller that the active node
				printf("Swap out nodes %d and %d\n", *activeNode->key, *node->key ); //DEBUG
				node->left_child = activeNode->left_child; // swap the node into that spot
				node->right_child = activeNode->right_child;
				activeNode->left_child->parent = node;
				activeNode->right_child->parent = node;
				node->parent = activeNode->parent;
				if ( activeNode->parent->left_child == activeNode ) { //if active node is the left child
					activeNode->parent->left_child = node; //node becomes moma's new left child
				} else {
					activeNode->parent->right_child = node; //else node is the right child
				}

				activeNode->parent = NULL; //family? what family?
				activeNode->left_child = NULL;
				activeNode->right_child = NULL;

				printf("++++++RECURSIVE CALL++++++\n");
				heap = addToHeap( heap, activeNode ); //recursive call to find the old node's new home and family

				return heap;

			}
			printf("Loop keys:::::: Active Node %d Working Node %d\n", *activeNode->key, *node->key); //DEBUG
		} while ( 1 + 1 == 2 /*forevvvveeeeerrrrrrrr*/ ); 
	}
	return heap;
}

void displayHeap( heap_node * node ) {
	int i = 0;
	if ( node->left_child != NULL || node->right_child != NULL ) { //if the children are not leaves
		printf( "Key: %d ::", *node->key );
		for( i = 0; i < 10; i++ ) {
			printf(" %d", node->array[i] );
		}
		printf("\n");
		if ( node->left_child != NULL ) {
			displayHeap( node->left_child ); //recursive call for first the left then right child
		}
		if ( node->right_child != NULL ) {
			displayHeap( node->right_child );
		}
	} else {
		printf( "Key: %d ::", *node->key );
		for( i = 0; i < 10; i++ ) {
			printf(" %d", node->array[i] );
		}
		printf("\n");
	}
}

void destroyHeap( heap_node * node ) {
	if ( node->left_child == NULL && node->right_child == NULL ) {
		free(node->array);
		free(node->key);
		free(node);
	} else {
		if ( node->left_child != NULL ) {
			destroyHeap( node->left_child );
		}
		if ( node->right_child != NULL ) {
			destroyHeap( node->right_child );
		}	
		free(node->array);
		free(node->key);
		free(node);
	}
}