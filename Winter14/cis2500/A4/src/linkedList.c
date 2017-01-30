/*************************linkedList.c************************************************************
Student Name: Jeffrey-David Kapp             Student Number: 0832671        
Date: 28 March, 2014                         Course Name: CIS*2500           
I have exclusive control over this submission via my password.
By including this statement in this header comment, I certify that:
     1) I have read and understood the University policy on academic integrity;
     2) I have completed the Computing with Integrity Tutorial on Moodle; and
     3) I have achieved at least 80% in the Computing with Integrity Self Test.
I assert that this work is my own. I have appropriately acknowledged any and all material
(data, images, ideas or words) that I have used, whether directly quoted or paraphrased.
Furthermore, I certify that this assignment was prepared by me specifically for this course.
********************************************************************************************/

#include "linkedList.h"

MusicRec * createRecord( char * title, char * artist, double fileSize, int length, char theType )
{
	MusicRec * newRecord; /*record to be added to the list*/

	/*memory allocation*/
	newRecord = ( MusicRec * ) malloc(sizeof(MusicRec));
	newRecord->title = malloc(sizeof(char)*1024);
	newRecord->artist = malloc(sizeof(char)*1024);

	/*copying passed data to the new struct*/
	strcpy(newRecord->title, title);
	strcpy(newRecord->artist, artist);

	newRecord->sizeInKB = fileSize;
	newRecord->lengthInSeconds = length;
	newRecord->type = theType;
	newRecord->next = NULL;

	return newRecord;
}

char * printRecord( MusicRec * toPrint )
{
	char * returnString;

	char intStr[100];

	returnString = malloc(sizeof(char)*1024);

	strcat( returnString, toPrint->title);
	strcat( returnString, " (");
	strcat( returnString, toPrint->artist);
	strcat( returnString, ")");
	strcat( returnString, ":");
	sprintf( intStr, "%d", toPrint->lengthInSeconds);
	strcat( returnString, intStr);
	strcat( returnString, "[");
	sprintf( intStr, "%.2f", toPrint->sizeInKB);
	strcat( returnString, intStr);
	strcat( returnString, "]");

	return returnString;
}

void destroyRecord( MusicRec * theRecord )
{
	free(theRecord->title);
	free(theRecord->artist);

	return;
}


MusicRec * addToFront( MusicRec * theList, MusicRec * toBeAdded )
{
	toBeAdded->next = theList;
	return toBeAdded;
}

MusicRec * addToBack( MusicRec * theList, MusicRec * toBeAdded )
{
	MusicRec * listHead;
	listHead = theList;

	do {

		theList = theList->next;

	} while( theList->next != NULL);

	theList->next = toBeAdded; 
	toBeAdded->next = NULL;

	return listHead;
}

MusicRec * removeFromFront( MusicRec * theList )
{
	MusicRec * returnNode;
	
	if ( isEmpty(theList) ==  true ) {
		return NULL;
	}

	returnNode = theList->next;

	free(theList->title);
	free(theList->artist);
	/*free(theList);*/

	return returnNode;
}

MusicRec * removeFromBack( MusicRec * theList )
{
	MusicRec * returnVal;

	if ( isEmpty( theList ) == true ) {
		return NULL;
	}

	if ( theList->next != NULL ) {
		returnVal = removeFromBack( theList->next );
	} else if ( theList->next == NULL ) {
		return NULL;
	}
	if ( returnVal ==  NULL ) {
		returnVal = theList->next;
		theList->next = NULL;
	}

	return returnVal;
}


MusicRec * getLastItem( MusicRec * theList )
{
	MusicRec * returnVal;

	if ( isEmpty( theList ) == true ) {
		return NULL;
	}

	if ( theList->next != NULL ) {
		returnVal = getLastItem( theList->next );
	} else if ( theList->next == NULL ) {
		return theList;
	}

	return returnVal;
}

bool isEmpty( MusicRec * theList )
{
	if ( theList == NULL ) {
		return true;
	}

	return false;
}

void printList( MusicRec * theList )
{
	MusicRec * nextNode;
	char ** printString;
	int x = 0, y = 0;

	nextNode = theList;

	printString = malloc(sizeof(char)*1024);

	x = 0;

	do {

		printString[x] = printRecord( nextNode );

		x++;
		nextNode = nextNode->next;

	} while ( nextNode != NULL );

	for ( y = 0; y <= x-1; y++ ) {
		printf("%s\n", printString[y]);
	} 

	for( y = 0; y <= x; y++ ) {
		free(printString[x]);
	}
	free(printString);

	return;
}

void destroyList( MusicRec * theList )
{
	MusicRec * temp;

	do {

		destroyRecord( theList );
		temp = theList;
		theList = theList->next;
		free(temp);

	} while( theList != NULL );

	return;
}