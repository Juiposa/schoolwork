/*****************
Jeffrey-David Kapp
25 October 2014
0832671
Assignment 3
CIS 2520
*****************/

#include "question1.h"

tree_node * newNode( char * string, tree_node * parent ) {
	tree_node * newNd;
	newNd = (tree_node*)malloc(sizeof(tree_node));
	newNd->parent = parent;
	newNd->left_child = NULL;
	newNd->right_child = NULL;
	newNd->numericVal =  malloc(sizeof(float));
	newNd->string_val = malloc(sizeof(char)*100);
	strcpy( newNd->string_val, string );
	newNd->value = malloc(sizeof(char)*5);

	return newNd;
}

void destroyTree( tree_node * node ) {
	if ( node->left_child == NULL && node->right_child == NULL ) {
		free(node->numericVal);
		free(node->string_val);
		free(node->value);
		free(node);
	} else {
		destroyTree( node->left_child );
		destroyTree( node->right_child );

		free(node->numericVal);
		free(node->string_val);
		free(node->value);
		free(node);
	}
}