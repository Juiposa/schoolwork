#include "assignment1.h"

//algorithm implemented exactly the same as outlined in assignment
int ackermann( int m, int n )
{

	int result = 0;
	
	if ( m == 0 ) {
		return n + 1;
	} else if ( m > 0 && n == 0 ) {
		result = ackermann( m - 1, 1 );
	} else if ( m > 0 && n > 0 ) {
		result = ackermann( m - 1, ackermann( m, n - 1));
	}

	printf("%d\n", result);

	return result;
}