/*************************main.c************************************************************
Student Name: Jeffrey-David Kapp             Student Number: 0832671        
Date: 1 April, 2014                         Course Name: CIS*2500           
I have exclusive control over this submission via my password.
By including this statement in this header comment, I certify that:
     1) I have read and understood the University policy on academic integrity;
     2) I have completed the Computing with Integrity Tutorial on Moodle; and
     3) I have achieved at least 80% in the Computing with Integrity Self Test.
I assert that this work is my own. I have appropriately acknowledged any and all material
(data, images, ideas or words) that I have used, whether directly quoted or paraphrased.
Furthermore, I certify that this assignment was prepared by me specifically for this course.
********************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	
	int x = 0, y = 0;
	
	FILE * readFile;
	
	char ** verses;
	char iteration[15];
	
	readFile = fopen("lyricfile.txt", "r");
	
	verses = malloc(sizeof(char)*1024);
	for( x = 0; x < 1024; x++ ) {
		verses[x] = malloc(sizeof(char)*1024);
	}
	
	for ( x = 0; x < 12; x++ ) {
		fgets(verses[x], 1024, readFile );
	}
	
	for ( x = 0; x < 12; x++ ) {
		switch ( x ) {
			case 0: strcpy( iteration, "First"); break;
			case 1: strcpy( iteration, "Second"); break;
			case 2: strcpy( iteration, "Third"); break;
			case 3: strcpy( iteration, "Fourth"); break;
			case 4: strcpy( iteration, "Fifth"); break;
			case 5: strcpy( iteration, "Sixth"); break;
			case 6: strcpy( iteration, "Seventh"); break;
			case 7: strcpy( iteration, "Eigth"); break;
			case 8: strcpy( iteration, "Ninth"); break;
			case 9: strcpy( iteration, "Tenth"); break;
			case 10: strcpy( iteration, "Eleventh"); break;
			case 11: strcpy( iteration, "Twelfth"); break;
		}
		for ( y = x; y >= 0; y-- ) {
			if ( y == x ) { 
				printf("On the %s of Christmas my true love gave to me\n", iteration); 
			} else if ( y == 0 ) {
				printf("and %s", verses[0]);
			} else {
				printf("%s", verses[y]);
			}
		}
																																																																																																																																																																																																																		
	}
	
	for( x = 0; x < 1024; x++ ) {
		free(verses[x]);
	}
	fclose(readFile);
	
	return 0;
	
	
}
