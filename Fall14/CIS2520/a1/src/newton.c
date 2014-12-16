#include "assignment1.h"

void newtonControl() 
{
	double a = 0.0;		//newtown variables
	double number = 0.0;
	double epsilon = 0.0;

	time_t timeBefore = 0; //testing execution time
	time_t timeAfter = 0;
	time_t timeDifference = 0;

	printf("Enter a number to be rooted then an epsilon value.\n");
	scanf("%lf", &number);
	scanf("%lf", &epsilon);
	
	a = number / 2; //inital step

	if ( fabs( a * a - number ) <= epsilon ) {
		printf("The approximate root for %.2f for epsilon %.2f is %.2f.\n", number, epsilon, a);
	} else {
		timeBefore = time(NULL);
		a = newtonRecursive( number, epsilon, a ); //call to the recursive implementation
		timeAfter = time(NULL);
		timeDifference = timeAfter - timeBefore;

		printf("Recursion.\n");
		printf("The approximate root for %.2f for epsilon %.2f is %.2f.\n", number, epsilon, a);
		printf("Execution time: %d seconds\n", (int)timeDifference );

		a = number / 2; //reseting the value of a for iteration

		timeBefore = time(NULL);
		a = newtonIterative( number, epsilon, a ); //call to the iterative implementation
		timeAfter =  time(NULL);
		timeDifference = timeAfter - timeBefore;

		printf("Iterative.\n");
		printf("The approximate root for %.2f for epsilon %.2f is %.2f.\n", number, epsilon, a);
		printf("Execution time: %d seconds\n", (int)timeDifference );
	}

	return;
}

double newtonRecursive( double number, double epsilon, double a )
{

	a = ( a + (number / a) ) / 2; //newton's approximation

	if ( epsilon >= fabs( a * a - number ) ) { //is quotient is larger that epsilon
		return a; //do it again
	} else {
		a = newtonRecursive( number, epsilon, a ); //else return that value
	}

	return a;
}

double newtonIterative( double number, double epsilon, double a )
{

	do {

		a = ( a + ( number / a) ) / 2; //newton's approximation

	} while ( epsilon <= fabs( a * a - number) ); //while quotient is larger than epsilon

	return a;

}