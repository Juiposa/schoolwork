/********************
Jeffrey-David Kapp
0832671
CIS2520 Assignment 2
14 Oct 2014
********************/

#include "carRental.h"

void printToFile( rentalCar * listHead, char * filename ) {
	FILE * writeFile;
	rentalCar * curNode;
	
	writeFile = fopen( filename, "w" );
	curNode = listHead;

	do {	
		if ( curNode != NULL ) {		
			fprintf( writeFile, "STARTCAR\n%s\n%i\n", curNode->plateNumber, *curNode->odometer );
			fprintf( writeFile, "%d\n", *curNode->returnDate );
		}
		curNode = curNode->next;
	} while ( curNode != NULL ); 
}

rentalCar * readFromFile( rentalCar * listHead, char * filename ) {
	FILE * readFile;
	rentalCar * newNode;
	int * odometer;
	int * returnDate;
	char * plateNumber;
	int i = 0;
	char * inputString;

	inputString = (char *)malloc(100*sizeof(char));

	readFile = fopen( filename, "r" );

	do {
		for ( i = 0; i < 4; i++ ) {
			fgets( inputString, 100, readFile );
			inputString[strlen(inputString)-1] = '\0';
			if ( i == 1 ) {
				plateNumber = (char *)malloc(100*sizeof(char));
				strcpy( plateNumber, inputString );
			} else if ( i == 2 ) {
				odometer = malloc(sizeof(int));
				*odometer = atoi(inputString); 
			} else if ( i == 3 ) {
				returnDate = malloc(sizeof(int));
				*returnDate = atoi(inputString);
			}
		}
		newNode = newCarConstruct( plateNumber, odometer, returnDate );
		listHead = addToList( listHead, newNode );

	} while ( !feof( readFile ));

	return listHead;
}