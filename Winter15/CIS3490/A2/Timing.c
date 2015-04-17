

#include <stdio.h>
#include <time.h>

double  elapsed;
extern int fib(int n);
extern long long int fib1(int n);
extern long long unsigned fib2(unsigned n);

int main()   {
    clock_t start, finish;
    int fibRes = 0;
    long long int fibRes1 = 0;
    long long unsigned fibRes2 = 0;

    //recursive
    /*start = clock();
    fibRes = fib(100);
    finish = clock();
    elapsed = (double)(finish - start) / CLOCKS_PER_SEC;
    printf("recursive result = %d\n", fibRes );
    printf("time = %8.5f \n\n", elapsed);*/

    //iterative
    start = clock();
    fibRes1 = fib1(100);
    finish = clock();
    elapsed = (double)(finish - start) / CLOCKS_PER_SEC;
    printf("iterativeresult = %lld\n", fibRes1 );
    printf("time = %8.5f \n\n", elapsed);

    //constant
    start = clock();
    fibRes2 = fib2(100);
    finish = clock();
    elapsed = (double)(finish - start) / CLOCKS_PER_SEC;
    printf("constant result = %d\n", fibRes );
    printf("time = %8.5f \n\n", elapsed);


}
