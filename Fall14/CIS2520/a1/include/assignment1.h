/* Assignment 1 CIS2520
 * Authored by Jeffrey-David Kapp 0832671
 * 29th of September 2014
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h> 

//Question 1
void carbonControl();

int carbon( char carbonStr[6], int arrayVal, char string[6] );

int carbonCompare( char curChar, char string[6] );

//Question 2
int ackermann( int m, int n );


//Question 3
void newtonControl();

//paramters: number; number user wants to root; epsilon; small number used to determine a root; a; resultant of Newton's approximation
double newtonRecursive( double number, double epsilon, double a );

double newtonIterative( double number, double epsilon, double a );

