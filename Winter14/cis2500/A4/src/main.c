/*************************main.c************************************************************
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

#include "main.h"

int main( int agrc, char * argv[] )
{
	MusicRec * theList; /*music playlist*/
	FILE * readFile; /*file to be read from for input*/

	if ( argv[1] != NULL && !(agrc < 2) ) {
		readFile = fopen( argv[1], "r" ); /*opening read file*/
	} else {
		printf("INVALID TERMINAL INPUT\n");
		return 0;
	}

	theList = fileIO( readFile ); /*building the list*/

	printAverages( theList ); /*will print averages*/ 

	printList( theList ); /*printing the list*/

	destroyList( theList ); /*destroying the list*/

	return 0;
}

void printAverages( MusicRec * theList ) 
{
	int totalElements = 0; /*total elements in the list*/
	int totalTime = 0; /*total time in seconds*/
	double totalSize = 0; /*total size in KB*/
	double averageSize = 0; /*average size of the list in KB*/

	int hour = 0, minute = 0, second = 0; /*time of playlist split into basic time keeping units*/

	do {

		totalTime += theList->lengthInSeconds;
		totalSize += theList->sizeInKB;

		totalElements++;
		theList = theList->next;

	} while ( theList != NULL );

	averageSize = totalSize / ( totalElements - 1 );

	minute = totalTime / 60;
	second = totalTime - ( minute * 60 );
	hour = minute / 60;
	minute =  minute - ( hour * 60 );

	printf("%d:%d:%d\n", hour, minute, second);
	printf("%.2f\n", averageSize); 
} 