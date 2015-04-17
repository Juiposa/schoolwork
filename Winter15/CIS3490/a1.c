/*
Jeffrey Kapp
CIS3490
January 19
Assignment 1 q2
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int prettyMuchEqual( float n1, float numberX );

int main() {
	char input[100];
	float numberX = 0.0;
	float a = 0.0, b = 0.0, c = 0.0;
	float n1 = 0.0;
	float n2 = 0.0;

	printf("Enter a number.\n");
	fgets( input, 100, stdin );
	numberX = atof(input);
	printf("Entered Number: %f\n", numberX );
	b = numberX;

	do {
		c = (a + b) / 2;
		n1 = log2f( c ) * c;
		if ( n1 > numberX ) {
			a = c;
		} else if ( n1 < numberX ) {
			b = c;
		}
	} while ( !prettyMuchEqual( n1, numberX ) );

	printf("n1: %f\n", n1 );

	return 0;
}

int prettyMuchEqual( float n1, float numberX ) {
	if ( n1 <= numberX + 0.001 && n1 >= numberX - 0.001 ) {
		return 1;
	}
	return 0;
}