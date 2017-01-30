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

int main ()
{
	char * input;
	char * newString;
	char ** words; 
	int wordcount = 0;
	int x = 0, y = 0;
	int spaces = 0;
	int length = 0;
	
	input = malloc(sizeof(char)*1024);
	newString =  malloc(sizeof(char)*1024);
	words = malloc(sizeof(char)*1024);
	for( x = 0; x < 1024; x++ ) {
		words[x] = malloc(sizeof(char)*1024);
	}
	
	printf("Enter a string.\n");
	fgets(input, 1024, stdin);
	
	words[0] = strtok( input, " "); 
	x = 1;
	wordcount = 1;
	
	do {
		words[x] = strtok( NULL, " ");
		x++;
		wordcount++;
	} while (words[x] !=  NULL );
	
	printf("How many spaces would you like?\n");
	fgets( input, 1024, stdin );
	length = atoi(input);
	
	spaces = length / wordcount;
	
	for ( x = 0; x <= wordcount; x++ ) {
		printf("%d\n", x);
		strcat( newString, words[x]);
		for( y = 0; y < spaces; y++ ) {
			strcat(newString, " ");
		}
	}
	
	printf("%s\n", newString);
	
	free(input);
	for(x = 0; x < 1024; x++ ) {
		free(words[x]);
	}
	free(words);
	
	return 0;
	
}

