#include <stdio.h>
#include <time.h>

int main( int argc, char *argv[] ) {
	clock_t start;
	clock_t finish;
	double elapsed;
	int i, j, k;
	int sum = 0;
	int n = atoi(argv[1]);

	printf("N = %d\n", n );


	printf("Q1 i) Complexity: Theta(n^2)\n");
	start = clock();
	sum = 0;
	for( i = 1; i <= n; i++ )
		for( j = 1; j <= n; j++ )    
    		sum++;
    finish = clock();
    elapsed = (double)(finish - start) / CLOCKS_PER_SEC;
    printf("Sum = %d\n", sum );
    printf("time = %8.5f \n\n", elapsed);

    printf("Q1 ii) Complexity: Theta([n^2(n+1)]/2)\n");
	start = clock();
    sum = 0;
    for( i = 1; i <= n; i++ )
    	for( j = 1; j <= i; j++ )
    		sum++;
    finish = clock();
    elapsed = (double)(finish - start) / CLOCKS_PER_SEC;
    printf("Sum = %d\n", sum );
    printf("time = %8.5f \n\n", elapsed);

    /*
    printf("Q1 iii) Complexity: ???\n");
    start = clock();
    sum = 0;
    for( i = 1; i <= n; i++ )
    	for( j = 1; j <= i*i*i; j++ )
    		for( k = 1; k <= j; k++ )
    			sum++;
    finish = clock();
    elapsed = (double)(finish - start) / CLOCKS_PER_SEC;
    printf("Sum = %d\n", sum );
    printf("time = %8.5f \n\n", elapsed);
    */

    printf("Q1 iv) Complexity: ???\n");
    start = clock();
    sum = 0;
    for( i = 1; i <= n; i++ )
    	for( j = 1; j <= i*i; j++ )
    		if( j % i == 0 )
    			for( k = 1; k <= j; k++ )
    				sum++;
    finish = clock();
    elapsed = (double)(finish - start) / CLOCKS_PER_SEC;
    printf("Sum = %d\n", sum );
    printf("time = %8.5f \n\n", elapsed);

    return 0;
}