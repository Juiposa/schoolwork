/*************************lab2.c*******************************************************
Student Name: Jeffrey-David Kapp             Student Number:  0832671      
Date: 11 Feburary, 2014                       Course Name: CIS*2500            
I have exclusive control over this submission via my password.
By including this statement in this header comment, I certify that:
     1) I have read and understood the University policy on academic integrity;
     2) I have completed the Computing with Integrity Tutorial on Moodle; and
     3) I have achieved at least 80% in the Computing with Integrity Self Test.
I assert that this work is my own. I have appropriately acknowledged any and all material
(data, images, ideas or words) that I have used, whether directly quoted or paraphrased.
Furthermore, I certify that this assignment was prepared by me specifically for this course.
*******************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * charFind( char * theString, int indexNum ); 

int main()
{
	char * theString;
	char * target; 
	int indexNum = 0; 

	theString = malloc(sizeof(char) * 50);

	printf("Please enter a string:\n");
	fgets( theString, 50, stdin );

	printf("Your string:\n%s\n", theString );

	printf("Please enter a number:\n");
	scanf( "%d", &indexNum );

	target = charFind( theString, indexNum - 1 );

	printf("%p\n", target );
	printf("%p\n", &target );
	printf("%c\n", *target );

	return 0;
}

char * charFind( char * theString, int indexNum )
{

	char * returnChar;

	returnChar = &theString[indexNum];

	return returnChar;

}