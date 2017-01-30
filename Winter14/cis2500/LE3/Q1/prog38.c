#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main() 
{
	char * inputString;
	int stringSize = 0;
	int total = 0;
	int i = 0;
	
	inputString = malloc(sizeof(char)*1024);
	
	printf("Please enter an interger.\n");
	
	fgets(inputString, 1024, stdin);
	
	stringSize = strlen(inputString);
	
	for( i = 0; i < stringSize; i++ ) {
		total += atoi(inputString[i]);
	}
	
	if ( total == atoi(inputString) ) {
		printf("%s is an armstrong number\n", inputString);
	} else {
		printf("%s in not an armstrong number\n", inputString);
	}
	
	free(inputString);
	
	return 0;
}
