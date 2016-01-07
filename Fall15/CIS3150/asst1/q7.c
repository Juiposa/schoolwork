#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//argv[1] will be the inputted string
int main(int argc, char *argv[])
{
	int stringLen = strlen(argv[1]);
	char currChar;
	char state = 'A';
	int i = 0;

	printf("Start state: %c\n", state);

	//loop through string
	for ( i = 0; i < stringLen; i++ ) {
		currChar = argv[1][i];

		//take action based on what state the FA is in
		switch( state ) {
			case 'A':
				if ( currChar == 'a' )
					state = 'B'; //next state
				//else we stay at A
				break;
			case 'B':
				if ( currChar == 'b' )
					state = 'C'; //next state
				else
					state = 'A';
				break;
			case 'C':
				if ( currChar == 'a' )
					state = 'D'; //next state
				else
					state = 'A';
				break;
			case 'D':
				if ( currChar == 'b' )
					state = 'E'; //end state
				else
					state = 'A';
				break;
			case 'E':
				//NOOP; in end state, don't need to go anywhere
				break;
			default: printf("You broke it.\n"); exit(1); break;
		}

		printf("Current state: %c\n", state);
	}

	printf("Last state: %c\n", state );
	if( state = 'E' )
		printf("Input accepted\n");

	return 0;
}