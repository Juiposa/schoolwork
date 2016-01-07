#include <stdio.h>
#include <stdlib.h>

int A[100];
int atop = 0;

int TestStack(int x[], int n) {
	int i;
	for( i = 1; i <= n; i++ ) {
		if ( x[i] - x[i+1] != 1 ) {
			return 0;
		}
	}
	return 1;
}

int Pop(int x[], int * top) {
	if ( *top == 0 )
		return 0;
	int i = 0;
	i = x[*top];
	x[*top] = 0;
	(*top)--;
	return i;
}

void Push(int x[], int * top, int v ) {
	(*top)++;
	x[*top] = v;
}

int main() {
	Pop(A, &atop);
	Push(A, &atop, 5);
	Push(A, &atop, 4);
	Push(A, &atop, 1);
	Pop(A, &atop);
	Push(A, &atop, 3);
	Push(A, &atop, 2);
	Push(A, &atop, 1);
	if (TestStack(A, 5)) printf("The stack is sorted!!!\n");
	return 0;
}