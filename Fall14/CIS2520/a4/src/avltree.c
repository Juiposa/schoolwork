/*****************
Jeffrey-David Kapp
23 November 2014
0832671
Assignment 4
CIS 2520
*****************/

#include "avl.h"

int main() {

	AVL_node * avl_tree = NULL;
	AVL_node * searchNode = NULL;
	char inputVar[100];
	char * secInput = malloc(sizeof(char)*100); //secondary input
	int i = 0; //counter

	do {
		printOptions();
		printf("avl/> ");
		fgets( inputVar, 100, stdin );

		switch( inputVar[0] ) {
			case '1': //initialisation
				printf("filename: ");
				fgets( secInput, 100, stdin );
				secInput[strlen(secInput) - 1] = '\0'; //change new line character to null terminator
				avl_tree = initialisation( secInput );
				for ( i = 0; i <= 5; i++ ) {
					avl_tree = restructure( avl_tree ); //run it through a few times
				}
				break;
			case '2': //find
				printf("find key: ");
				fgets( secInput, 100, stdin );
				secInput[strlen(secInput) - 1] = '\0'; //change new line character to null terminator
				searchNode = find( avl_tree, secInput );
				if ( searchNode	== NULL ) {
					printf("no_such_key\n");
				} else {
					printf("key: %s, frequency: %d\n", searchNode->key, searchNode->count );
				}
				break;
			case '3': //insert
				printf("insert key: ");
				fgets( secInput, 100, stdin );
				secInput[strlen(secInput) - 1] = '\0'; //change new line character to null terminator
				avl_tree = insert( avl_tree, newNode( secInput ));
				avl_tree = restructure( avl_tree );
				searchNode = find( avl_tree, secInput );
				printf("key: %s, frequency: %d\n", searchNode->key, searchNode->count );
				break;
			case '4': //remove
				printf("remove key: ");
				fgets( secInput, 100, stdin );
				secInput[strlen(secInput) - 1] = '\0'; //change new line character to null terminator
				searchNode = find( avl_tree, secInput );
				if ( searchNode	== NULL ) {
					printf("no_such_key\n");
				} else {
					printf("key: %s, frequency: %d\n", searchNode->key, searchNode->count );
					if ( searchNode == avl_tree ) { //we only catch the return if the node we're deleting is the root
						avl_tree = removeNode( searchNode );
					} else {
						removeNode( searchNode );			
					}
					avl_tree = restructure( avl_tree );
				}
				break;
			case '5': //height and size
				printf("height: %d, size: %d\n", height(avl_tree, 1), size(avl_tree) );
				break;
			case '6': //find all
				printf("frequency: ");
				fgets( secInput, 100, stdin );
				findAll( avl_tree, atoi( secInput ) );
				break;
			case '7': // exit
				if ( avl_tree != NULL ) {
					destroyTree( avl_tree );
					avl_tree = NULL;					
				}
				break;
			case '8': //DEBUG balance
				printf("find key: ");
				fgets( secInput, 100, stdin );
				secInput[strlen(secInput) - 1] = '\0'; //change new line character to null terminator
				searchNode = find( avl_tree, secInput );
				if ( searchNode	== NULL ) {
					printf("no_such_key\n");
				} else {
					printf("key: %s, frequency: %d, balanceFactor: %d\n", searchNode->key, searchNode->count, searchNode->bf );
				}
				break;
			case '9': //debug balance
				if ( avl_tree != NULL ) {
					avl_tree = restructure( avl_tree );					
				}
				break;
			case 'a': //get root
				printf("root: %s\n", avl_tree->key );
				break;
			default: printf("Invalid input.\n"); break;
		}
	} while ( inputVar[0] != '7' );

	free(secInput);
	secInput = NULL;
	return 0;
}

AVL_node * initialisation( char * filename ) {
	FILE * fp;
	AVL_node * avl_tree = NULL; //avl tree pointer
	AVL_node * newNd; //operating node, added to avl_tree
	char * activeStr; //takes strings from strtok, works as source for keys
	char inputStr[1024]; //string for reading from file

	fp = fopen(filename, "r");
	if ( fp == NULL ) {
		printf("***ERROR: Could not open file:: %s\n", filename );
		return NULL;
	}

	printf("WORKING...\n");

	while ( 1 + 1 == 2 ) { //loop break below
		fgets( inputStr, 1024, fp );
		activeStr = strtok( inputStr, " " ); //first strtok for a line
		while ( activeStr != NULL ) { //while there are still tokens
			if ( strlen(activeStr) > 3 ) {		
				if ( activeStr[strlen(activeStr) - 1] == '\n' ) { //if there is a trailing new line at the end of a string
					activeStr[strlen(activeStr) - 1] = '\0'; //change it to a null terminator
				}
				newNd = newNode( activeStr ); //make a new node
				avl_tree = insert( avl_tree, newNd ); //add it to the tree	
			}
			activeStr = strtok( NULL, " " ); //get next token
		}
		if ( feof(fp) ) { break; } //if at the end of the file, break loop
	}
	updateBalanceFactor( avl_tree );

	printf("DONE.\n");

	return avl_tree;

}

AVL_node * insert( AVL_node * avl_tree, AVL_node * node ) {
	if ( avl_tree == NULL ) { //empty tree
		return node; //we return node as the root
	} else if ( strcmp( avl_tree->key, node->key ) > 0 ) { //if the node is greater than the avl_tree node
		if ( avl_tree->left == NULL ) { //if avl_tree has no left child
			node->parent = avl_tree; //node becomes the left child
			avl_tree->left = node;
		} else { //else it does have a child
			insert( avl_tree->left, node ); //recursive call to right child
		}		
	} else if ( strcmp( avl_tree->key, node->key ) < 0 ) {
		if ( avl_tree->right == NULL ) { //same as above, but for left child
			node->parent = avl_tree;
			avl_tree->right = node;
		} else {
			insert( avl_tree->right, node ); 
		}
	} else if ( strcmp( avl_tree->key, node->key ) == 0 ) { //if equal
		avl_tree->count++; //up that nodes frequency count
		destroyNode( node ); //destroy the node we've been using to search
	} 

	return avl_tree;
}

AVL_node * removeNode( AVL_node * node ) {
	AVL_node * activeNode = NULL;

	if ( node->left == NULL && node->right == NULL ) { //if node is a leaf
		if ( node->parent->left == node ) { // and the node is the left child
			node->parent->left = NULL; //remove that address
 		} else { //otherwise, right child
 			node->parent->right = NULL;
 		}
 		destroyNode( node );
 		return NULL;
	} else if ( node->left == NULL || node->right == NULL ) { //if either children are null
		if ( node->left == NULL ) { //left is null
			activeNode = node->right; //working node is the right child
		} else if (  node->right == NULL ) { //right is null
			activeNode = node->left; //working node is left child
		}
		if ( node->parent->left == node ) { //the node is the left child
			node->parent->left = activeNode; //set active node to be the child
 		} else { //otherwise, right child
 			node->parent->right = activeNode;
 		}
 		activeNode->parent = node->parent;
 		destroyNode(node);
 		return activeNode;
	} else { //node we're removing is internal
		activeNode = node->right; //we get the next inorder node
		while ( activeNode->left != NULL ) {
			activeNode = activeNode->left;
		}

		if ( activeNode->right != NULL ) { //if active node has a right child
			activeNode->parent->left = activeNode->right; //active node's right subtree becomes parent's new left subtree
			activeNode->right->parent = activeNode->parent; //and active nodes's parent becomes subtree's parent
		} else {
			activeNode->parent->left = NULL; //otherwise we simply set it to null
		}

		activeNode->parent = node->parent;
		if ( node->parent != NULL && node->parent->left == node ) { // and the node is the left child
			node->parent->left = activeNode; //set active node to be the child
 		} else if ( node->parent != NULL && node->parent->right == node  ){ //otherwise, right child
 			node->parent->right = activeNode;
 		}
 		activeNode->left = node->left;
 		activeNode->right = node->right;

 		destroyNode( node );

 		return activeNode;
	}

}

AVL_node * find( AVL_node * avl_tree, char * key ) {
	AVL_node * found;
	if ( avl_tree == NULL ) {
		return NULL;
	} else {
		if ( strcmp( avl_tree->key, key ) == 0 ) {
			return avl_tree;
		} else if ( strcmp( avl_tree->key, key ) > 0 ) {
			found = find( avl_tree->left, key );
		} else if ( strcmp( avl_tree->key, key ) < 0 ) {
			found = find( avl_tree->right, key );
		}
	}
	return found;
}

void findAll( AVL_node * avl_tree, int count ) {
	if( avl_tree == NULL ) {
		return;
	} else if ( avl_tree->count > count ) {
		 printf("key: %s, frequency: %d\n", avl_tree->key, avl_tree->count );
	}

	if ( avl_tree->left != NULL ) {
		findAll( avl_tree->left, count );
	}

	if ( avl_tree->right != NULL ) {
		findAll( avl_tree->right, count );
	}

}

void updateBalanceFactor( AVL_node * avl_tree ) {
	if ( avl_tree == NULL ) {
		return;
	} else {
		avl_tree->bf = height( avl_tree->left, 1 ) - height( avl_tree->right, 1 );

		updateBalanceFactor( avl_tree->left );
		updateBalanceFactor( avl_tree->right );
	}
} 

int height( AVL_node * avl_tree, int count ) {
	int leftHeight = 0, rightHeight = 0;

	if ( avl_tree == NULL ) { //if our node is  null
		return 0; //its height is 0
	} else if ( avl_tree->left == NULL && avl_tree->right == NULL ) { //we are at a leaf
		return count; //return current height count
	} else {
		leftHeight = height( avl_tree->left, count++ ); //recursive call downwards to left
		rightHeight = height( avl_tree->right, count++ ); //ditto to right

		if ( leftHeight >= rightHeight ) { //which ever height is larger is the height of the tree as a whole
			return leftHeight;
		} else if ( rightHeight > leftHeight ) {
			return rightHeight;
		}
	}

	return -1;

}

int size( AVL_node * avl_tree ) {
	int leftCount = 0, rightCount = 0;

	if ( avl_tree == NULL ) { //if null, sub tree size is 0
		return 0;
	} else {
		leftCount = size(avl_tree->left); //recursive call down the sides of a tree
		rightCount = size(avl_tree->right);
	}

	return leftCount + rightCount + 1; //left subtree size plus right subtree plus the active node itself
}

AVL_node * restructure( AVL_node * avl_tree ) {
	AVL_node * array[8];
	if ( height(avl_tree, 1) > 2 && avl_tree->bf >= -1 && avl_tree->bf <= 1  ) { //tree is balanced, take no action
		//printf("Balanced.\n");
		updateBalanceFactor( avl_tree );
		if ( avl_tree->left != NULL ) {
			avl_tree->left = restructure( avl_tree->left ); //check each subtree, make sure they're balanced as well
		}
		if ( avl_tree->right != NULL ) {
			avl_tree->right = restructure( avl_tree->right );
		}
	} else if ( height(avl_tree, 1) > 2 ) { //all other cases, the tree is unbalanced
		if ( avl_tree->bf >= 2 ) { //left side of the tree is unbalanced
			array[6] = avl_tree;
			array[4] = avl_tree->left;
			array[2] = avl_tree->left->left;
			if ( array[2] == NULL || array[4] == NULL ) {
				return avl_tree;
			}
			array[3] = array[2]->right;				
			array[5] = array[4]->right;				

		} else  if ( avl_tree->bf <= -2 ) { //right side is unbalanced
			array[2] = avl_tree;
			array[4] = avl_tree->right;
			array[6] = avl_tree->right->right;
			if ( array[6] == NULL || array[4] == NULL ) {

				return avl_tree;
			}
			array[3] = array[4]->left;				
			array[5] = array[6]->left;				
		}
		

		array[4]->parent = avl_tree->parent;
		if ( avl_tree->parent != NULL && avl_tree->parent->left == avl_tree ) { // avl_tree is the left child
			avl_tree->parent->left = array[4]; //set y to be the left child
 		} else if ( avl_tree->parent != NULL && avl_tree->parent->right == avl_tree )  { //otherwise, right child
 			avl_tree->parent->right = array[4]; //ditto, but right
 		}

		array[4]->left = array[2];
		array[4]->right = array[6];
		if ( array[2] != NULL ) {
			array[2]->parent = array[4];				
			array[2]->right = array[3];			
		}
		if ( array[6] != NULL ) {
			array[6]->parent = array[4];				
			array[6]->left = array[5];			
		}
		if ( array[5] != NULL ) {
			array[5]->parent = array[6];			
		}
		if ( array[3] != NULL ) {
			array[3]->parent = array[2];			
		}

		avl_tree = array[4];
		updateBalanceFactor( avl_tree );
		if ( avl_tree->left != NULL ) {
			avl_tree->left = restructure( avl_tree->left ); //check each subtree, make sure they're balanced as well
		}
		if ( avl_tree->right != NULL ) {
			avl_tree->right = restructure( avl_tree->right );
		}
	} 
	return avl_tree;
} 

AVL_node * newNode( char * key ) {
	AVL_node * newNd = (AVL_node*)malloc(sizeof(AVL_node));
	newNd->parent = NULL;
	newNd->left = NULL;
	newNd->right = NULL;
	newNd->bf = 0;
	newNd->count = 1;
	newNd->key = malloc(sizeof(char)*15);
	strcpy( newNd->key, key );

	return newNd;
}

void destroyNode( AVL_node * node ) {
	free( node->key );
	free( node );
}

void destroyTree( AVL_node * avl_tree ) {
	if ( avl_tree->left != NULL ) {
		destroyTree( avl_tree->left );
	}
	if ( avl_tree->right != NULL ) {
		destroyTree( avl_tree->right );
	}
	destroyNode( avl_tree );
}

void printOptions() {
	printf("1. Initialization\n");
	printf("2. Find\n");
	printf("3. Insert\n");
	printf("4. Remove\n");
	printf("5. Check Height and Size\n");
	printf("6. Find All (above a given frequency)\n");
	printf("7. Exit\n");
}