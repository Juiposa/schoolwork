#include "list.h"


StdntRec * createRecord( char * firstName, char * lastName, int studentNumber, float GPA )
{
	StdntRec *  newRecord;

	newRecord = ( StdntRec * ) malloc(sizeof(StdntRec));
	newRecord->firstName = malloc(sizeof(char)*strlen(firstName)+1);
	newRecord->lastName = malloc(sizeof(char)*strlen(lastName)+1);

	strcpy(newRecord->firstName, firstName);
	strcpy(newRecord->lastName, lastName);
	newRecord->studentNumber = studentNumber;
	newRecord->GPA = GPA;

	return newRecord;

}

StdntRec * addToFront( StdntRec * toBeAdded, StdntRec * listhead )
{

	toBeAdded->next = listhead;

	return toBeAdded;
}

void printList( StdntRec * listhead )
{
	StdntRec * curnt = listhead; 

	do {

		printf("Name: %s %s\n", curnt->firstName, curnt->lastName);
		printf("Student number: %d\n", curnt->studentNumber );
		printf("GPA: %.2f\n\n", curnt->GPA );

		curnt = curnt->next;

	} while ( curnt != NULL );

	return;

}

void deleteList( StdntRec * curnt )
{	

	free(curnt->firstName);
	free(curnt->lastName);

	if ( curnt->next != NULL ) {
		deleteList( curnt->next );	
	}

	free(curnt);

	return;

}