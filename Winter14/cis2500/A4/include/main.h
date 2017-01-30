/*************************main.h************************************************************
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

/*function prototypes beyond the function found in the standardise header file*/

#include "linkedList.h"

/* fileIO
 * Purpose: will read in lines from the input file and call the parsing function
 * Parametres: file to be read
 * Returns: completed linked list of the playlist
*/
MusicRec * fileIO( FILE * readFile );

/* parsing
 * Purpose:  will parse by tokenisation each line of the input file
 * Parametres: line or be parsed
 * Returns: completed struct
*/
MusicRec * parsing( char * inputString );  

/* tokenString
 * Purpose: tokenise the string 
 * Parametres: string to be tokenised for first run, NULL otherwise
 * Returns: string returned from strtok
*/
char * tokenString( char * inputString );

/* printAverages
 * Purpose: will determine and print total playlist length and average filesize
 * Parametres: the list to averaged
 * Returns: nothing
*/
void printAverages( MusicRec * theList ); 