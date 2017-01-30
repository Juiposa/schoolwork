/*************************fileIO.c************************************************************
Student Name: Jeffrey-David Kapp             Student Number: 0832671        
Date: 14 March, 2014                         Course Name: CIS*2500           
I have exclusive control over this submission via my password.
By including this statement in this header comment, I certify that:
     1) I have read and understood the University policy on academic integrity;
     2) I have completed the Computing with Integrity Tutorial on Moodle; and
     3) I have achieved at least 80% in the Computing with Integrity Self Test.
I assert that this work is my own. I have appropriately acknowledged any and all material
(data, images, ideas or words) that I have used, whether directly quoted or paraphrased.
Furthermore, I certify that this assignment was prepared by me specifically for this course.
********************************************************************************************/

#include "main.h"

MusicRec * fileIO( FILE * readFile )
{
	MusicRec * theList; /*the linked list*/
	MusicRec * newRec; /*the newly parsed and constructed record*/

	char * inputString; /*string read in from file*/

	/*memory allocation*/
	inputString = malloc(sizeof(char)*1024);

	do {;

		fgets( inputString, 1024, readFile ); /*reading inthe line of the file*/

		if (inputString != NULL) {
			newRec = parsing( inputString ); /*parsing that line and getting a rec*/
		}

		if ( isEmpty( theList ) == true ) {
			theList = newRec;
			theList->next = NULL; 
		} else if ( isEmpty( theList ) == false ) {

			switch( newRec->type ) { /*handling types, if a: add to front; if b: add to back*/
				case 'a':
					theList = addToFront( theList, newRec );
					break;
				case 'b':
					theList = addToBack( theList, newRec );
					break;
			}
		}
	} while( !(feof(readFile)) );

	return theList;
}

MusicRec * parsing( char * inputString ) 
{
	MusicRec * newRec; /*new record*/
	char * artist;
	char * title;
	int length;
	double fileSize;
	char type;

	char * tokString;

	/*memory allocation*/
	artist = malloc(sizeof(char)*1024);
	title = malloc(sizeof(char)*1024);

	tokString = strtok( inputString, "," );
	strcpy( artist, tokString );

	tokString = strtok( NULL, "," );
	if ( tokString != NULL ) {
		strcpy( title, tokString );
	}

	tokString = strtok( NULL, "," );
	if ( tokString != NULL ) {
		length = atoi(tokString);
	}

	tokString = strtok( NULL, "," );
	if ( tokString != NULL ) {
		fileSize = atof(tokString);
	}

	tokString = strtok( NULL, "," );
	if ( tokString != NULL ) { 
		type = tokString[0];
	}

	newRec = createRecord( title, artist, fileSize, length, type );
	
	
	free(artist);
	free(title);

	return newRec;
}
