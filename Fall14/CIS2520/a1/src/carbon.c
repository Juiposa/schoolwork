#include <assignment1.h>

//see readme for description

void carbonControl()
{
	int i = 0;
	char carbonStr[6] = { 'c', 'a', 'r', 'b', 'o', 'n' };

	char string[6];

	for ( i = 0; i < 6; i++ ) {
		string[i] = ' ';
	}

	carbon( carbonStr, 0, string );

}

int carbon( char carbonStr[6], int arrayVal, char string[6] ) 
{

	printf("First print: %s\n", string );

	int i = 0;

	for ( i = arrayVal; i < 6; i++ ) {
		if ( !(carbonCompare(carbonStr[i], string)) ) {
			string[arrayVal] = carbonStr[i];
			carbon( carbonStr, arrayVal + 1, string );
		}
		
		
	}

	printf("%s\n", string);

	return 0;

}

int carbonCompare( char curChar, char string[6] ) 
{
	int i = 0;
	for ( i = 0; i < 6; i++ ) {
		if ( curChar == string[i] ) {
			return 1;
		}
	}

	return 0;

}