#include "Huffman.h"

int main(int argc, char * argv[]) {
	FILE * fp;
	huff_node ** huffArray; //array of indepentent huffman nodes
	huff_node * huffTree; //point to receive the completed huffman tree
	float compression = 0.0;

	if ( argc > 1 ) {
		fp = fopen(argv[1], "r");
	} else {
		fp = fopen("dat/Huffman.txt", "r");	
	}

	huffArray = readFile( fp ); //read contents of file 

	freopen("dat/output.txt", "w", fp);
	huffTree = buildHuffTree( huffArray );
	encode( huffTree, "" );
	compression = getCompRatio( huffTree );

	fprintf(fp, "Compression Ratio %.2f\n", compression );
	printTree(fp, huffTree);

	fclose(fp);
	free(huffArray);
	destroyTree(huffTree);
	return 0;
}

huff_node * buildHuffTree( huff_node ** array ) {
	huff_node * left = NULL, * right = NULL; //current working left and right children
	huff_node * newNde; //new node that children are linked to
	int i = 0, x = 0;
	
	while( nodeCount(array) != 1 ) { //while there are more than one node which hasnt been paired
		for( i = 0; i < 100; i++ ) { //scans through array and picks two values that are closest and joins them
			if( array[i] != NULL && ( left == NULL || array[i]->freq <= left->freq ) ) { //if the node isnt null, and the node has a lesser value than the current left node
				if( left == NULL ) {
					left = array[i];
				} else if ( array[i]->freq == left->freq ) { 
					if( array[i]->chr_val < left->chr_val ) { //node has a lesser character
						right = left; //bump the left to the right position
						left = array[i];
					} else if ( array[i]->chr_val > left->chr_val ) { //else it has a greater character
						if ( array[i]->chr_val < right->chr_val ) //if lesser charcter than the right node
							right = array[i]; //swap it out; else not its time to be linked
					}
				} else if ( array[i]->freq < left->freq ) {
					right = left;
					left = array[i];
				}
			} else if ( array[i] != NULL && ( right == NULL || array[i]->freq <= right->freq)) { //else it might match right in a similar way
				if( right == NULL ) {
					right = array[i];
				} else if ( array[i]->freq == right->freq && array[i]->chr_val < right->chr_val ) { //same value and a lesser character
					right = array[i];
				} else if ( array[i]->freq < right->freq ) {
					right = array[i];
				}
			}
		} //we should now have two nodes that most closely match one another
		for( i = 0; i < 100; i++ ) { //clear thier spots in the array
			if( array[i] == left || array[i] == right ) {
				array[i] = NULL;
				x++;
			}
			if( x == 2 )
				break;
		}
		x = 0;
		newNde = newNode( '\0', left, right ); //join nodes/subtrees into new subtree; subtrees are identified by the null terminator
		left = NULL;
		right = NULL;

		for( i = 0; i < 100; i++ ) { //slot new subtree into first null space
			if( array[i] == NULL ) { 
				array[i] = newNde;
				break;
			}
		}
	}

	return array[0]; //completed huffman tree should be sitting in the first spot in array 
}

huff_node ** readFile( FILE * fp ) {
	char inChar;
	huff_node ** newArray;
	int i = 0;

	newArray = malloc(sizeof(huff_node)*100); //static size of 100 different characters; good for our implementation

	for( i = 0; i < 100; i++ ) {
		newArray[i] = NULL;
	}

	while(!feof(fp)) {
		inChar = fgetc(fp);
		for( i = 0; i < 100 ; i++ ) { 
			if ( newArray[i] == NULL ) { //if at a null element
				if ( inChar != EOF ) //and the character is no EOF
					newArray[i] = newNode(inChar, NULL, NULL); //add it
				break;
			} else if ( newArray[i]->chr_val == inChar ) { //else
				newArray[i]->freq++; //simply increment
				break;
			}
		}
	}

	return newArray;
}

void encode( huff_node * tree, char * code ) {
	char * leftCpy = malloc(sizeof(char)*10);
	char * rightCpy = malloc(sizeof(char)*10);
	strcpy(tree->code, code);
	//set up copies
	strcpy( leftCpy, code);
	strcpy( rightCpy, code );
	//concatenate new digits onto end
	strcat( leftCpy, "0");
	strcat( rightCpy, "1");

	//recursive call
	if( tree->left != NULL )
		encode(tree->left, leftCpy);
	if( tree->right != NULL )
		encode(tree->right, rightCpy);

	free(leftCpy);
	free(rightCpy);
}

float getCompRatio( huff_node * tree ) {
	float total = tree->freq * 8; //total number of characters is the freq of the root node
	float compressedTotal;

	compressedTotal = countBitLength( tree );

	return compressedTotal / total;
}

float countBitLength( huff_node * tree ) {
	int leftTotal = 0;
	int rightTotal = 0;

	if( tree->left != NULL )
		leftTotal = countBitLength(tree->left);
	if( tree->right != NULL )
		rightTotal = countBitLength(tree->right);

	if( tree->left == NULL && tree->right == NULL ) { //left node; character
		return strlen(tree->code) * tree->freq;
	}
	return leftTotal + rightTotal; //else connective node, return left right totals
}
 
huff_node * newNode( char inChar, huff_node * left, huff_node * right ) {
	huff_node * new = (huff_node*)malloc(sizeof(huff_node));
	new->chr_val = inChar;
	if ( left == NULL || right == NULL ) {
		new->freq = 1;	
	} else {
		new->freq = left->freq + right->freq;
	}
	new->code = malloc(sizeof(char)*10);
	new->left = left;
	new->right = right;

	return new;
}

void printNode( FILE * fp, huff_node * node ) {
	if( node == NULL || node->chr_val == '\0') //we dont print null nodes or contective nodes 
		return;
	fprintf(fp, "\nChar: %c Freq: %d\n", node->chr_val, node->freq );

	if ( node->code != NULL ) {
		fprintf(fp, "Code: %s Code Length: %zd\n", node->code, strlen(node->code) );
	} else {
		fprintf(fp, "Code: null\n");
	}
}

int nodeCount( huff_node ** array ) {
	int count = 0;
	int i = 0;
	for( i = 0; i < 100; i++ ) {
		if(array[i] != NULL)
			count++;
	}
	return count;
} 

void destroyTree( huff_node * tree ) {
	if( tree == NULL )
		return;
	if(tree->code != NULL )
		free(tree->code);
	destroyTree(tree->left);
	destroyTree(tree->right);
	free(tree);
	return;
}

void printTree( FILE * fp, huff_node * tree ) {
	if( tree->left != NULL ) 
		printTree( fp, tree->left );
	if( tree->right != NULL )
		printTree( fp, tree->right );

	printNode( fp, tree );
	return;
}