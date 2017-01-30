#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXSIZE 1024

char * stringSep( char * theString );

int main()
{
	char * theString; /*string to be entered by the user*/
	
	char * newString; /*string to be returned from the function*/
	
	theString = malloc(sizeof(char)*MAXSIZE+1); /*memory allocation*/
	
	printf("Please enter two words seperated by a space.\n");
	
	fgets(theString, MAXSIZE, stdin); /*reading in the user's input*/
	
	newString = stringSep( theString );
	
	printf("Old string: %s\nNew string: %s\n", theString, newString);
	
	free(newString); /*freeing memory*/
	free(theString);
	
	return 0;
	
	
	
}

char * stringSep( char * theString )
{
	
	char * newString; /*new string*/
	char * tokString; /*string to be tokenised*/
	char * leftString; /*left side of the tokenised string*/
	char * rightString; /*right side of the tokensied string*/
	
	int leftSize = 0; /*size of the left hand string*/
	int rightSize = 0; /*size of the right hand string*/
	int averageSize = 0; /*average size between the two sides*/
	
	int x = 0; /*counting var*/
	
	/*memory allocation*/
	tokString = malloc(sizeof(char)*strlen(theString)+1);
	newString = malloc(sizeof(char)*strlen(theString)+1);
	leftString = malloc(sizeof(char)*strlen(theString)+1);
	rightString = malloc(sizeof(char)*strlen(theString)+1);
	/*end malloc*/
	
	/*calling strtok twice to get each side of the space*/
	
	strcpy( tokString, theString ); /*copying the passed string to a temporary variable*/
	
	leftString = strtok( tokString, " "); /*left side*/
	printf("%s\n", leftString);
	rightString = strtok( NULL, " " ); /*right side*/
	printf("%s\n", rightString);
	
	leftSize = strlen( leftString ); /*getting the left size*/
	rightSize = strlen( rightString ); /*getting the right size*/
	
	averageSize = ( leftSize + rightSize ) / 2;
	
	for( x = 0; x <= averageSize; x++ ) {
		
		newString[x] = theString [x]; /*copying characters to the new string*/
	
	}
	
	newString[x+1] = '\0'; /*tacking on the null terminator*/
	
	/*freeing memory*/
	/*free(tokString);
	free(leftString);
	free(rightString);*/
	
	return( newString );
	
}
