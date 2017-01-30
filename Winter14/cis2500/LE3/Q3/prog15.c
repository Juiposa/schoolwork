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

int main() 
{
	char * input;
	
	float miles;
	float kilometres;
	
	input = malloc(sizeof(char)*1024);
	
	printf("Enter a distance in miles.\n");
	
	fgets( input, 1024, stdin );
	
	miles = atof(input);
	
	kilometres = miles * 1.61;
	
	printf("%.2f miles is %.2f kilometres.\n", miles, kilometres);
	
	free(input);
	
	return 0;
}
