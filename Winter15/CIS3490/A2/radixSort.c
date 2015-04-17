#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//doesn't exactly run O(N), but runs O(kN), does that count as linear?
//wikipedia article on radix sort used to learn how to implement
void radixSort( int * array, int size ) {
	int i; //counting vairable
	int max = 100; //largest value in list
	int exponent = 1; //effectively the digit we are next sorting, 1, 10, 100, 1000 etc
	const int base = 10; //this is for generalisation, incase I want to use this in the future with a different base
	int *b = (int*)calloc(size, sizeof(int)); //shadow array we are sorting into
	int *bucket = (int*)calloc(base, sizeof(int)); //buckets for each number in a given base

	//normally we get the max value by running through the entire list once, but we know the max value is 100
	//it is here commented out in case I use this code in the future
	/*for(i = 1; i < size; i++ ) {
		if( array[i] > max )
			max = array[i];
	}*/

	while ( max >= exponent ) { //looping while the exponent is smaller than the largest value
		memset(bucket, 0, base * sizeof(int)); //clearing the buckets

		//number of keys that will goes in each bucket
		//(array[i] / exponent) % base will result in the value of a number's digit
		for ( i = 0; i < size; i++ ) {
			bucket[(array[i] / exponent) % base]++;
		}

		//added the counts of previous buckets to get the correct postition in the array
		for ( i = 1; i < base; i++ ) {	
			bucket[i] += bucket[i - 1];
		}

		//starting from the end, get a number's index in the bucket 
		//decrement it; and use that value to place it into the shadow array
		for ( i = size - 1; i >= 0; i-- ) {
			b[--bucket[(array[i] / exponent) % base]] = array[i];
		}

		//copying the shadow array back in the main array
		for ( i = 0; i < size; i++ ) {
			array[i] = b[i];
		}

		//next digit
		exponent *= base;
	}
	free(b);
	free(bucket);
}

int sum( int * array, int left, int right ) {
	int sum = 0;
	int i;
	for ( i = left; i < right; i++ ) {
		sum += array[i];
	}
	return sum;
}

int main() {
	int * array;
	int i, smallSum, largeSum;
	FILE * fp;
	char * inputVar = malloc(sizeof(char)*10);
	int fifteen = 0, twentyseven = 0, fiftyfour = 0, eightynine = 0;
	int size = 0;
	clock_t start, finish;
	double elapsed;

	fp = fopen("test.txt", "r");
	start = clock();
	fgets( inputVar, 10, fp );
	size = atoi(inputVar);
	printf("SIZE: %d\n", size );
	array = (int*)calloc(size, sizeof(int));

	for ( i = 0; i < size; i++ ) {
		fgets( inputVar, 10, fp );
		array[i] = atoi(inputVar);
		switch( array[i] ) {
			case 15: fifteen++; break;
			case 27: twentyseven++; break;
			case 54: fiftyfour++; break;
			case 89: eightynine++; break;
		}
	} 

	radixSort( array, size );

	smallSum = sum( array, 0, size/2-1 );
	largeSum = sum( array, size/2, size );

	finish = clock();
	elapsed = (double)(finish - start) / CLOCKS_PER_SEC;

	printf("Time taken: %8.5f seconds\n", elapsed );
	printf("Sum of halves: %d, %d\n", largeSum, smallSum );
	printf("Max difference: %d\n", largeSum-smallSum );

	printf("Frequency of: \n");
	printf("15: %d\n", fifteen );
	printf("27: %d\n", twentyseven );
	printf("54: %d\n", fiftyfour );
	printf("89: %d\n", eightynine );

	fclose(fp);
	free(inputVar);
	free(array);
	return 0;
}