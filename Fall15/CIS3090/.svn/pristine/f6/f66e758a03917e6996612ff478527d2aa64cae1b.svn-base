/***************************
Jeffrey-David Kapp
0832671
CIS3090-A1
14 October 2015
***************************/

#include "pal.h"

//shamelessly copy pasta'd from the lab files
PI_PROCESS ** Worker;
PI_CHANNEL ** toWorker;
PI_CHANNEL ** result;
PI_BUNDLE *allResults;



int main( int argc, char * argv[] ) {

	FILE * fp;
	FILE * outfile;
	int exeType; //serial or parallel execution
	long i, j, k;
	long numStr = 0; //number of string in the given file
	long numStrPerW = 0; //number of strings each worker will get
	long extraStr = 0; //remainder of strings
	double timeTaken = 0; //time taken to execute;
	int * palinLines; //lines found by a worker
	int dump; //dummy variable to receive useless values back from workers
	int palinFound; //number of palindromes found by a worker
	int ttl = 0; //total number of palindromes found
	char ** strings; //all strings from file
	char * sstring; //single string; strings from file concatenated together into a single string

	//PILOT SETUP
	int N = PI_Configure( &argc, &argv );

	PI_StartTime();

	if( N > 1 ) {
		exeType = PARALLEL;
	} else {
		exeType = SERIAL;
	}

	//more than one process to work with
	if ( exeType == PARALLEL ) {
		Worker = malloc(sizeof(PI_PROCESS*)*N);
		toWorker = malloc(sizeof(PI_CHANNEL*)*N);
		result = malloc(sizeof(PI_CHANNEL*)*N);

		for ( i=0; i<(N-1); i++ ) {
			Worker[i] = PI_CreateProcess( workerFunc, i, NULL );
			toWorker[i] = PI_CreateChannel( PI_MAIN, Worker[i] );
			result[i] = PI_CreateChannel( Worker[i], PI_MAIN );
		}

		allResults = PI_CreateBundle( PI_SELECT, result, N-1 );
		PI_StartAll(); 
	}
	//END; PILOT SETUP

	if(argc < 2) {
		PI_Abort( 0, "ERR: Filename not given, exiting.\n", __FILE__, __LINE__ );
	} else if (!(fp=fopen(argv[1], "r"))) {
		PI_Abort( 0, "ERR: Cannot open indicated file, exiting\n", __FILE__, __LINE__ );
	}

	//STRING SET UP
	numStr = countLine(fp);
	freopen(0, "r", fp); //fp is at eof, need to be reset
	//malloc space for strings
	printf("NUMBER OF STRINGS: %ld\n", numStr );
	strings = malloc(sizeof(char*)*numStr+1);
	for( i=0; i<numStr; i++ ) {
		strings[i] = malloc(sizeof(char)*200);
	}
	//read strings in
	for( i=0; i<numStr; i++ ) {
		fgets(strings[i], 200, fp);
	}

	fclose(fp);
	if( exeType == PARALLEL ) {
		sstring = (char*)malloc(sizeof(char)*numStr*200);
		for( i=0; i<numStr; i++ ) {
			strcpy(&sstring[i*200], strings[i]);
		}

		//freeing up memory now that we have our single string
		for( i=0; i<numStr; i++ ) {
			free(strings[i]);
		}
		free(strings);
	}

	outfile = fopen("pal.out", "w");
	if( exeType == PARALLEL ) {
		//number of strings each worker gets
		numStrPerW = (N-1) == 0 ? numStr : numStr / (N - 1);
		extraStr = numStr - (numStrPerW*(N-1));

		printf("numStr per worker %ld\n", numStrPerW );
		int strIndex = 0; //starting index of the group of strings a worker is responsible for
		//giving each worker their info and strings they'll be 
		for ( i=0; i<N-1; i++ ) {
			//passing workers number of strings and their index
			//first process gets the extra strings, value set to 0 afterwards
			PI_Write(toWorker[i], "%ld %d", numStrPerW+extraStr, strIndex );
			//passing the strings themselves

			PI_Write( toWorker[i], "%^c", (numStrPerW+extraStr)*200, &sstring[strIndex*200] ); 
			strIndex = strIndex + numStrPerW + extraStr; //next index for next worker
			extraStr = 0; //no more extra strings
		}
		for ( i=0; i<N-1; i++ ) {
			j = PI_Select( allResults );
			PI_Read(result[j], "%d %^d", &palinFound, &dump, &palinLines );
			//PI_Read(result[j], "%d", &palinFound );
			for( j=0; j<palinFound; j++ ) {
				fprintf(outfile, "%010d\n", palinLines[j]+1 );
			}
			ttl += palinFound;
		}
	} else if ( exeType == SERIAL ) { //if execution is serial, this block is where all work is done
		for( i=0; i<numStr; i++ ) {
			if(isAPalin(strings[i])) {
				ttl++;
				fprintf(outfile, "%010d\n",(int)i+1 );
			}
		}
		for( i=0; i<numStr; i++ ) {
			free(strings[i]);
		}
		free(strings);
	}

	fclose(outfile);
	printf("%d PALINDROMES FOUND\n", ttl );
	if( exeType == PARALLEL ) {
		free(sstring);
	}
	timeTaken = PI_EndTime();
	printf("TIME TAKEN %.3lf sec(s)\n", timeTaken );
	free(Worker);
	free(toWorker);
	free(result);
	if( exeType == PARALLEL) 
		PI_StopMain(0);
	return 0;
}

int workerFunc( int index, void* arg2 ) {
	long myNumStr;
	int strIndex;
	int palinFound = 0;
	long len, i, j = 0;
	char * myStrings;
	PI_Read( toWorker[index], "%ld %d", &myNumStr, &strIndex );
	printf("WORKER %d: numstr %ld, start index %d\n", index, myNumStr, strIndex );
	PI_Read( toWorker[index], "%^c", &len, &myStrings );

	int palinLines[myNumStr]; //file lines which contain a palindrome 

	for(i = 0; i<myNumStr; i++ ) {
		if (isAPalin(&myStrings[i*200])) {
			palinLines[palinFound] = strIndex + i;
			palinFound++;
		}	
	}


	PI_Write(result[index], "%d %^d", palinFound, myNumStr, palinLines );
	//PI_Write(result[index], "%d", palinFound );

	printf("%dFOUND %d\n", index, palinFound );
	return 0;
}

long countLine( FILE * fp ) {
	long num = 0;
	char readStr[201];
	while(!feof(fp)) {
		fgets(readStr, 201, fp );
		num++;
	}
	return num;
}

int isAPalin( char * str ) {
	int len = strlen(str);
	int i = 0;
	//empty string is a palindrome
	if( len == 0 )  return 1;
	
	while ( str[len] == '\n' || str[len] == '\0' ) {
		str[len] = '\0'; //change all end characters to null terminators if they arent already
		len--;
	}

	for( i=0; i<=len; i++, len-- ) {
		if(str[i] != str[len] ) {
			return 0;
		}
	}

	return 1;
}
