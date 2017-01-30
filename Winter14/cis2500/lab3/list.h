#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


typedef struct Student_Record {
	char * firstName;
	char * lastName;
	int studentNumber;
	float GPA;
	struct Student_Record * next;
} StdntRec;

StdntRec * createRecord( char * firstName, char * lastName, int studentNumber, float GPA );

StdntRec * addToFront( StdntRec * toBeAdded, StdntRec * listhead );

void printList( StdntRec * listhead );

void deleteList( StdntRec * curnt );

