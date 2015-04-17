/*
Jeffrey Kapp
CIS3490
January 19
Assignment 1 q2
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define PI 3.14159265
#define natLog 2.718281828

float stirlingApprox( float i );

int main() {
	char input[100];
	int numberX = 0;
	float logAnswer = 0.0;
	float n1 = 0.0;
	float n2 = 0.0;

	printf("Enter a number.\n");
	fgets( input, 100, stdin );
	numberX = atoi(input);
	printf("Entered Number: %d\n", numberX );
	

	do {
		logAnswer = n1 * log2f( n1 );
		n1++;
	} while ( numberX != ceil(logAnswer) );

	printf("n1: %.0f\n", n1 );

	do {
		if ( ceil(numberX / stirlingApprox( n1 )) > ceil(numberX / stirlingApprox( n1 + 1 )) ) {
			n1++; 
		}
	} while ( !(numberX / stirlingApprox( n1 + 1 )) < 0 );
	printf("n2: %.0f\n", n2 );

	return 0;
}

float stirlingApprox( float i ) {
	return pow((i / natLog), i) * ( sqrt( 2 * PI * i));
}
