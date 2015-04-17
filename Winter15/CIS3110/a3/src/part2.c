#include "part2.h"

int main(int argc, char * argv[]) {
	//so many variables :S
	process * waitQueue = NULL; //process waiting to be loaded
	process * memQueue = NULL; //list of processes in memory
	process * endQueue = NULL; //processes that have been laoded three times; if any
	process * workingProc = NULL; //process currently being operated on
	process * tempProc = NULL; //temp variable for swapping
	int i,k; //iterators
	int numLoads = 0; //number of loads completed
	int processes = 0; //number of process currently loaded
	int totalProcesses = 0; //cumulative process loaded across all operations
	int insertIndex = -1; //the index where the process will be put into memory
	int holes = 0; //current number of holes
	int currentHole = 0; //currently selected hole
	int mostSuitedHole = -1; //hole most suited for a process, used only by best/worst fit
	int totalHoles = 0; //total number of holes across all operations
	int memory[128]; //array representing memory
	int memUsage = 0; //amount of memory being used
	int totalMemUsage = 0; //cumulative usage across all operations
	FILE * fp; //file pointer is a file pointer

	for( k = 0; k < 4; k++ ) { //loop once for each memory management method
		//k = 0: first fit; 1: best fit; 2: next fit; 3: worst fit

		for( i = 0; i < 128; i++ ) { //memory initialisation
			memory[i] = 0;
		}
		fp = fopen( argv[1], "r" );
		if( fp == NULL ) { //teriminate if no file was entered on the command line
			printf("No file entered\n");
			return 0;
		}
		waitQueue = readFile(fp);

		if( k == 0 ) { //DEBUG
			print(waitQueue);
			printf("\n");
		} //END DEBUG

		while( waitQueue != NULL && k != 2 ) { //loop until all processes are in memory or have been completed
			workingProc = popFromQueue( &waitQueue ); //pop the next process from the ready queue
			while( insertIndex == -1 ) { //loop until a suitable hole has been found
				if( k == 0 && workingProc->size <= holeSize(memory, currentHole) ) { //first fit, simply if hole fits the process
					insertIndex = currentHole;
				} else if ( k == 1 && workingProc->size <= holeSize(memory, currentHole) ) { //best fit, will rotate throguh all of memory first
					if( mostSuitedHole == -1 ) { //first hole that meets criteria
						mostSuitedHole = currentHole;
					} else if (holeSize(memory, currentHole) < holeSize(memory, mostSuitedHole)) { //curhole is a better fit
						mostSuitedHole = currentHole;
					}
					if( currentHole == nextHole(memory, currentHole)) {
						insertIndex = mostSuitedHole;
					}
				} else if ( k == 3 && workingProc->size <= holeSize(memory, currentHole) ) { //best fit, will rotate throguh all of memory first
					if( mostSuitedHole == -1 ) { //first hole that meets criteria
						mostSuitedHole = currentHole;
					} else if (holeSize(memory, currentHole) > holeSize(memory, mostSuitedHole)) { //curhole is a better fit
						mostSuitedHole = currentHole;
					}
					if( currentHole == nextHole(memory, currentHole)) {
						insertIndex = mostSuitedHole;
					}
				}

				if( k != 2 && currentHole == nextHole(memory, currentHole) && insertIndex == -1 ) { //if no valid hole is found above
					//swap oldest process out
					tempProc = popFromQueue(&memQueue);
					if( tempProc->loaded != 3 ) { //not the third time its been swapped
						waitQueue = addToQueue(waitQueue, tempProc); //send it to the wait list
					} else {
						endQueue = addToQueue(endQueue, tempProc);
					}
					CLEARMEMORY(tempProc->start, tempProc->end); //unset its memory
					processes--;
					memUsage -= tempProc->size;
				}
				if( currentHole == nextHole(memory, currentHole) ) {
					currentHole = 0;
				} else {
					currentHole = nextHole(memory, currentHole);
				}				
			}
			if( k != 2 ) //only if not working under next fit, we reset the chosen hole everytime
				currentHole = 0;
			//a spot has been found
			
			//data tracking
			numLoads++;
			processes++;
			holes = countHoles(memory);
			totalProcesses += processes;
			totalHoles += holes;
			memUsage += workingProc->size;
			totalMemUsage += memUsage;

			//annoucement
			printf("%s loaded, #processes = %d, #holes = %d, %%memusage = %.0f, cumulative %%memusage = %.0f\n", workingProc->name, processes, holes, (float)memUsage / 128.0 * 100, \
				 ((float) totalMemUsage / (float)numLoads) / 128.0 * 100 );


			//inserting process
			workingProc->start = insertIndex;
			workingProc->end = workingProc->start + workingProc->size;
			workingProc->loaded++;
			SETMEMORY(workingProc->start, workingProc->end);
			memQueue = addToQueue( memQueue, workingProc );
			mostSuitedHole = -1;
			insertIndex = -1;
		}

		switch(k) {
			case 0: printf("\nFirst Fit \n"); break;
			case 1: printf("\nBest Fit\n"); break;
			case 2: printf("\nNext Fit - not implemented\n"); break;
			case 3: printf("\nWorst Fit\n"); break;
		}

		printf("Total loads = %d, average #processes = %.1f, average #holes = %.1f, cumulative %%memory = %.0f\n\n", numLoads, (float)totalProcesses / (float)numLoads, \
			(float)totalHoles / (float)numLoads, ((float) totalMemUsage / (float)numLoads / 128.0 * 100) );

		fclose(fp);
		destroyQueue(waitQueue);
		destroyQueue(memQueue);
		destroyQueue(endQueue);

		waitQueue = NULL;
		memQueue = NULL;
		endQueue = NULL;

		numLoads = 0;
		processes = 0;
		totalProcesses = 0; 
		insertIndex = -1; 
		holes = 0;
		currentHole = 0;
		mostSuitedHole = -1; 
		totalHoles = 0;
		memUsage = 0; 
		totalMemUsage = 0;
	}
 
	return 0;
}

int countHoles( int memory[128] ) {
	int state = 1; //1; occupied memory, 0; reading a hole
	int i = 0;
	int numHoles = 0;
	for( i = 0; i < 128; i++ ) {
		if( memory[i] == 1 && state == 0) { //occupied memory cell and was previously reading a hole
			numHoles++; //end of hole, plus one to tally
			state = 1; //we're now reading occupied memory
		} else if ( memory[i] == 0 && state == 1 ) { //hole and was previously reading occupied memory
			state = 0; //indicate we are now reading a hole 
		} else if ( state == 0 && i == 127 ) { //still reading a hole when we reach the end of memory
			numHoles++; //counts as a hole
		}
	}
	return numHoles;
}

int holeSize( int memory[128], int index ) {
	int i = 0;
	if ( memory[index] != 0 ) //must be given the starting index of a hole
		return 0;
	for( i = index; i < 128; i++ ) { //find the end of the hole
		if( memory[i] == 1 )
			break;
	}
	return i - index; //return the difference of the starting cell and the first occupied cell after the hole
}

int nextHole( int memory[128], int index ) {
	int state;
	int i = 0;
	if( memory[index] == 0 ) { //if reading a hole, we need to ignore it and find the next one
		state = 0;
	} else if ( memory[index] == 1 ) { //otherwise just find the next hole
		state = 1;
	}

	for( i = index; i < 128; i++ ) {
		if( state == 0 && memory[i] == 1 ) { //transitioning from starting hole to occupied area
			state++;
		} else if ( state == 1 && memory[i] == 0 ) { //going from occupied area to the next hole
			break;
		} else if ( i == 127 ) { //reach end of memory before finding another hole
			i = index;
			break;
		}
	}
	return i;
}

process * newProcess( char * name, int size ) {
	process * newPr = (process*)malloc(sizeof(process));
	newPr->next = NULL;
	newPr->name = malloc(sizeof(char)*10);
	strcpy( newPr->name, name);
	newPr->loaded = 0;
	newPr->size = size;
	newPr->start = 0;
	newPr->end = 0;
	return newPr;
}

process  * readFile( FILE * fp ) {
	char * inStr = malloc(sizeof(char)*100);
	char * tempName;
	int tempSize;
	process * newPr = NULL;
	process * newList = NULL;

	while( !feof(fp) ) {
		fgets(inStr, 100, fp );
		tempName = strtok( inStr, " " );
		tempSize = atoi(strtok( NULL, " "));
		newPr = newProcess( tempName, tempSize );
		newList  = addToQueue( newList, newPr );
	}
	return newList;
}

process * addToQueue( process * list, process * toAdd ) {
	if( list == NULL ) //if a null list, new item become head
		return toAdd;
	process * curItem = list;
	while( curItem->next != NULL ) {
		curItem = curItem->next;
	}
	curItem->next = toAdd;

	return list;
}

process * popFromQueue( process ** list ) {
	if(*list == NULL)
		return NULL;
	process * temp = *list;
	*list = temp->next;
	temp->next = NULL;
	return temp; 
}

void destroyQueue( process * list ) {
	if( list == NULL )
		return;
	destroyQueue(list->next);
	free(list->name);
	free(list);
	return;
}

void print( process * list ) {
	process * temp;
	for( temp = list; temp != NULL; temp = temp->next ) {
		printf("Process %s: Size %dMB\n", temp->name, temp->size );
	}
}
