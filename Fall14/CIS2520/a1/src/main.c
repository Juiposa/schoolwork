#include "assignment1.h"

int main()
{

	char inputVar[100]; //for user input

	int m = 0;
	int n = 0;

	printf("==============================================\nAssignment 1, Authored by Jeffrey-David Kapp\n0832671\n29 September 2014\n==============================================\n");

	//function calls, user chooses which function they wish to run, or to quit
	do {

		printf("Enter an option.\n");
		printf("(a) Carbon function\n(b) Ackermann's function\n(c) Newton's root approximation\n(q) Quit/Exit\n");

		fgets( inputVar, 100, stdin );

		switch ( inputVar[0] ) {
			case 'a': 
				carbonControl();
				break;
			case 'b': 
				printf("Enter two intial values.\n m and then n\n");
				scanf("%d", &m);
				scanf("%d", &n);
				ackermann( m, n );
				break;
				//ackermann with asking user for inital values
			case 'c': 

				newtonControl();
				break;
				//both the recursive and iterative iplementions of newtons function
			case 'q': break;
			default: printf("Invalid input.\n"); break;
		}

	} while ( inputVar[0] != 'q' && inputVar[0] != 'Q' );

	return 0;

}