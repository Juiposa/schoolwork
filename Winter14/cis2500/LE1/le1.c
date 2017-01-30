#include <stdlib.h>
#include <stdio.h>

#define TRUE 1
#define FALSE 0

int calculation( int * number );

int main(void)
{
	/*delcared array*/
	int array[15] = {39, 50, 52, 35, 98, 95, 63, 47, 82, 9, 100, 39, 87, 2, 33};
	
	int i; /*loop variable*/
	
	int trueFalse; /*true false variable*/
	
	for( i = 0; i < 15; i++) { /*will loop 15 times to print the array*/
		
		printf("%d ", array[i]);
	
	}
	
	printf("\n");
	
	for ( i = 0; i < 15; i++) { /*calls calc(), which will return a value based on the passed value*/
		
		trueFalse = calculation( &array[i] ); 
		
		
		switch ( trueFalse ) { /*handles if return of the function*/
			case TRUE: 
				printf("True ");
				break;
			case FALSE:
				printf("False ");
				break;
		}	
		
	}
	
	printf("\n");
	
	for( i = 0; i < 15; i++) { /*prints the array again*/
		
		printf("%d ", array[i]);
	
	}
	
	printf("\n");
	
	
	return 0;
	
}

int calculation( int * number ) /*will calculate if the passed value is over 25*/
{
	
	if ( *number > 25 ) { /*if it is, assign a value of 100 and return true*/
	
		*number = 100;
		
		return TRUE;
	
	} else {
		
		return FALSE; /*else return false*/
		
	}
	
	return FALSE;
	
}
