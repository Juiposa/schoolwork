//usage: ./a4C <filename> <pattern>
//pattern being what you what the algorithm to find in the file

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int * buildtable( char * pattern ) {
    int size = strlen(pattern);
    int * pmtable = (int*)malloc(sizeof(int)*size);

    int pos = 2; //iterator through pmtable
    int cnd = 0; //index of W

    pmtable[0] = -1; pmtable[1] = 0;

    while( pos < size ) {
        if( pattern[pos-1] == pattern[cnd] ) {
            pmtable[pos] = cnd + 1;
            cnd++;
            pos++;
        } else if ( cnd > 0 ) {
            cnd = pmtable[cnd];
        } else {
            pmtable[pos] = 0;
            pos++;
        }
    }
    return pmtable;
}

int kmpsearch( char * string, char * pattern, int sizeS, int sizeP ) {
    int m = 0; //start of current match
    int i = 0; //pos in string
    int * pmtable = buildtable(pattern); //partial match table; used to backtrack match isnt found

    while( m + i < sizeS ) {
        if( pattern[i] == string[m+i] ) {
            if( i == sizeP - 1 )
                return m;
            i++;
        } else {
            if( pmtable[i] > -1 ) {
                m = m + i - pmtable[i];
                i = pmtable[i];
            } else {
                m++;
                i = 0;
            }
        }
    }
    return -1;
}

int main ( int argc, char* argv[] ) {
    //string get
    FILE * f = fopen(argv[1], "r");
    fseek(f, 0, SEEK_END);
    long filesize = ftell(f);
    fseek(f, 0, SEEK_SET);
    char * string = (char*)malloc(sizeof(char)*filesize+1);
    fread(string, filesize, 1, f);
    string[filesize] = '\0';
    //end string get
    //pattern get
    char * pattern = (char*)malloc(sizeof(char)*strlen(argv[2]));
    strcpy(pattern, argv[2]);
    //pattern get

    clock_t start = clock();
    int found = kmpsearch(string, pattern, strlen(string), strlen(pattern) );
    clock_t diff = clock() - start;
    double timetaken = (double)diff / CLOCKS_PER_SEC;
    if( found == -1)
        fprintf(stdout, "Pattern \"%s\" not found in %f seconds\n", pattern, timetaken );
    else
        fprintf(stdout, "Pattern \"%s\" found at positon %d in %f seconds\n", pattern, found, timetaken );
    return 0;
}
