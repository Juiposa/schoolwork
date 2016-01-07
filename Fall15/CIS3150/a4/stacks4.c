#include <stdio.h>

// Assume that n < 8
int A[8], B[8], C[8], atop=0, btop=0, ctop=0;
int n, num[8], config[10];
int num_configs;
int configurations[181441][10];

int num_moves[16] = {0,2,2,2,4,4,4,4,4,4,6,6,6,6,6,6};
int moves[16][6] = {
    {},
    {1,2}, // stack B and C empty
    {3,4}, // stack A and C empty 
    {5,6}, // stack A and B empty 
    {3,4,5,6}, // stack A empty (b<c)
    {3,4,5,6}, // stack A empty (c<b)
    {1,2,5,6}, // stack B empty (a<c)
    {1,2,5,6}, // stack B empty (c<a)
    {1,2,3,4}, // stack C empty (a<b) 
    {1,2,3,4}, // stack C empty (b<a)
    {1,2,3,4,5,6}, // a < b < c
    {1,2,3,4,5,6}, // a < c < b
    {1,2,3,4,5,6}, // b < a < c
    {1,2,3,4,5,6}, // b < c < a 
    {1,2,3,4,5,6}, // c < a < b 
    {1,2,3,4,5,6},// c < b < a
};

int algo[16];
//1528823808
int total_algos = 0;
int success = 0;
int successAlgo = 0;

//===================================================
// Returns True=1 if and only if the stack contains
// elements 1,2,...,n  where 1 is the top of the stack
//===================================================
int TestStack(int x[], int top, int n) {
    int i;
    
    if (top != n) return 0;
    for (i=1; i<=n; i++)  if (x[i] != n-i+1) return 0;
    return 1;
}
//===================================================
// Output the elements from the stack, top to bottom
//===================================================
void PrintStack(int x[], int top) {
    int i;
    
    for (i=top; i>=1; i--) printf("%d ", x[i]);
    printf("\n");
}
//===================================================
// Pop and return the top element of the stack
// or 0 if stack empty
//===================================================
int Pop(int x[], int *top) {

	if (*top == 0) return 0;
	*top = *top - 1;
	return x[*top+1];
}
//===================================================
// Push v onto the stack
//===================================================
void Push(int x[], int *top, int v) {

	*top = *top +1;
	x[*top] = v;
}
//===================================================
// Moves an element from the top of one stack to another.
// If moving from an empty stack report an error and return 0,
// otherwise return the value of the element moved.
//===================================================
int Move(int m) {
int v;
    
    if (m == 1 || m == 2) v = Pop(A,&atop);
    if (m == 3 || m == 4) v = Pop(B,&btop);
    if (m == 5 || m == 6) v = Pop(C,&ctop);
    
    if (v == 0) { printf("Error: move from empty stack\n"); return 0; }
    
    if (m == 3 || m == 5) Push(A,&atop,v);
    if (m == 1 || m == 6) Push(B,&btop,v);
    if (m == 2 || m == 4) Push(C,&ctop,v);
    return 1;
}
//============================================================
// Run the algorithm represented by the string algo[1..15],
// testing for an infinite loop.  Return 1 if algorithm works,
// otherwise return 0.
//============================================================
int RunAlgorithm() {
    int a,b,c,count = 0;
    
    while (count++ < num_configs) {
        
        // TEST IF BELL SHOULD RING!
        if (TestStack(A,atop,n)) return 1;
        
        a = A[atop];   b = B[btop];    c = C[ctop];
        //=================
        // TWO STACKS EMPTY
        //=================
        if      (b==0 && c==0) Move( algo[1] );   // B and C empty
        else if (a==0 && c==0) Move( algo[2] );   // A and C empty
        else if (a==0 && b==0) Move( algo[3] );   // A and B empty
        
        //=================
        // ONE STACK EMPTY
        //=================
        else if (a==0 && (b < c) )  Move( algo[4] );  // A empty
        else if (a==0 && (c < b) )  Move( algo[5] );
        
        else if (b==0 && (a < c) )  Move( algo[6] );  // B empty
        else if (b==0 && (c < a) )  Move( algo[7] );
        
        else if (c==0 && (a < b) )  Move( algo[8] );  // C empty
        else if (c==0 && (b < a) )  Move( algo[9] );
        
        //===================
        // ZERO  STACKS EMPTY
        //===================
        else if (a < b && b < c)  Move( algo[10] );
        else if (a < c && c < b)  Move( algo[11] );
        else if (b < a && a < c)  Move( algo[12] );
        else if (b < c && c < a)  Move( algo[13] );
        else if (c < a && a < b)  Move( algo[14] );
        else if (c < b && b < a)  Move( algo[15] );
    }
    return 0;
}
//=========================================================
// Initialize the stacks based on configurations[t][1..n+2]
//=========================================================
void InitializeStacks(int t) {
    int i;
    
    atop = btop = ctop = 0;
    
    i = 1;
    while (configurations[t][i] != 0) Push(A, &atop, configurations[t][i++]);
    i++;
    while (configurations[t][i] != 0) Push(B, &btop, configurations[t][i++]);
    i++;
    while (i <= n+2) Push(C, &ctop, configurations[t][i++]);
}
//========================================================================
// Iterate through all possible starting confgurations testing algo[1..15]
//========================================================================
int TestAlgorithm() {
    int i;
    
    for (i=1; i<=num_configs; i++) {
        InitializeStacks(i);
        if (RunAlgorithm() != 1) return 0; 
    }
    return 1;
}
//===================================================================
// Generate all starting configurations as strings containing
// the elements 00123..n.  The 0s represent partitions of the stacks.
//===================================================================
void GenConfigurations(int t) {
    int i;
    
    if (t > n+2) {
        num_configs++;
        for (i=1; i<=n+2; i++) configurations[num_configs][i] = config[i];
    }
    else {
        // Loop through all possible values and add if available
        for (i=0; i<=n; i++) {
            if (num[i] > 0) {
                num[i]--;
                config[t] = i;
                GenConfigurations(t+1);
                num[i]++;
            }
        }
    }
}

void GenAlgos( int t ) {
    int i;
    if( t == 16 ) {
        total_algos++;
        if( total_algos%1000000 == 0)
            printf("%.1f%%\n", (float)total_algos/1528823808.0*100.0 );
        if ( 1 == TestAlgorithm() ) {
            successAlgo++;
        }
        success = 0;
    } else {
        for ( i = 0; i < num_moves[t]; i++ ) {
            algo[t] = moves[t][i];
            GenAlgos(t+1);
        }
    }
}
//====================================
int main() {
int i;
    
    printf("Enter n: "); scanf("%d", &n);
    
    // Generate and store all stack configurations
    num_configs = 0;
    num[0] = 2;
    for (i=1; i<=n; i++) num[i] = 1;
    GenConfigurations(1);

    GenAlgos(1);
    printf("Total starting stacks = %d\n", num_configs);
    printf("Total algorithms = %d\n", total_algos );

    printf("Total number of algorithms that solve = %d\n", successAlgo );
    
    /*TestAlgorithm();
    printf("Total success = %d\n", success);*/
}