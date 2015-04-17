/*******************
CIS3110 Assignment 2
Jeffrey-David Kapp
27 Feb 2014
0832671
*******************/

#include "simcpu.h"

int main( int argc, char * argv[] ) {
	simulation * simDat; //simulation data
	int i = 0;
	int timeUnit = 0; //time counter
	int quantum = -1;
	int details = 0; //detail toggle
	int verbose = 0; //verbose toggle
	
	//statistical variables
	int totalNumThreads = 0; //total number of threads
	int cpuTime = 0; //time cpu spends active 
	float average = 0; //average turnaround time for all threads
	float cpuUtil = 0; //cpu utilisation
	//end; stats

	//simulation variables
	thread * newQueue = NULL; //new threads, sorted by arrival time, then process number;
	thread * readyQueue = NULL; //queue of ready to executed threads
	thread * IOList = NULL; //list of threads currently goinging through IO
	thread * finishedList = NULL; //list of threads that are finished executing
	thread * temp;
	thread * currentThread = NULL; //thread currently being executed
	int switchTimer = 0; //process/thread swithc timer
	int cpuState = 0; //1 for active processer, 0 for inactive
	int quantumTimer = 0; //timer if a quantum is set
	//end; sim vars

	//argument resolution
	for( i = 0; i < argc; i++ ) {
		if( strcmp(argv[i], "-d") == 0 ) {
			details = 1; //toggle details
		} else if ( strcmp( argv[i], "-v") == 0 ) {
			verbose = 1; //toggle verboseness
		} else if ( strcmp( argv[i], "-r") == 0 ) {
			quantum = atoi(argv[i+1]); //toggle RR on
		}
	}
	simDat = parse( stdin );
	printSimulation( simDat );

	newQueue = enqueue( simDat->processes ); 

	if( verbose )
		printQueue( newQueue );

	totalNumThreads = countThreads(newQueue);

	//simulation start
	switchTimer = simDat->process_switch;
	while( countThreads(finishedList) != totalNumThreads ) { //until all threads are done
		//printf("CPUSTATE %d SWITCH %d\n", cpuState, switchTimer );
		
		while( temp = getReady( timeUnit, &newQueue )) { //getting threads that arrive at this time into ready queue
			if ( temp != NULL ) {
				readyQueue = addThread(readyQueue, temp);
				if( verbose )
					printf("At time %d: Thread %d of Process %d move from NEW to READY\n", timeUnit, temp->number, temp->parentProcess->number);	
			}
		}

		//CPU SIM
		if ( cpuState == 1 ) { //cpu is in an active state
			if ( currentThread->activeBurst->cpu_time == 0 ) { //if the current thread bring executed is 
				if( currentThread->activeBurst->io_time == 0 ) { //undefined io time, meaning last burst and thread is done.
					if( verbose )
						printf("At time %d: Thread %d of Process %d move from RUNNING to FINISHED\n", timeUnit, currentThread->number, currentThread->parentProcess->number);
					currentThread->finish_time = timeUnit;
					currentThread->turnaround_time = currentThread->finish_time - currentThread->arrival_time;
					finishedList = addThread( finishedList, currentThread );
				}  else { //not yet done; needs io
					if( verbose )
						printf("At time %d: Thread %d of Process %d move from RUNNING to BLOCKED\n", timeUnit, currentThread->number, currentThread->parentProcess->number);
					IOList = addThread( IOList, currentThread );
				}
				//all cases
				if( quantum > 0 ) { //a quantum has been set
					quantumTimer = quantum;
				}
				if ( readyQueue != NULL && readyQueue->parentProcess->number == currentThread->parentProcess->number) { //determining how much switch time is needed
					switchTimer = simDat->thread_switch;
				} else {
					switchTimer = simDat->process_switch;
				}
				currentThread = NULL;
				cpuState = 0; //cpu is now inactive
			} else { //CPU time is NOT 0
				if( quantum > 0 ) { //quantum is defined
					if( quantumTimer == 0 ) { //time slice expired
						if( verbose )
							printf("At time %d: Thread %d of Process %d move from RUNNING to READY\n", timeUnit, currentThread->number, currentThread->parentProcess->number);
						quantumTimer = quantum;
						if ( readyQueue != NULL && readyQueue->parentProcess->number == currentThread->parentProcess->number) { //determining how much switch time is needed
							switchTimer = simDat->thread_switch;
						} else {
							switchTimer = simDat->process_switch;
						}
						readyQueue = addThread( readyQueue, currentThread );
						currentThread = NULL;
						cpuState = 0;
					} else { //quantum is not yet 0
						quantumTimer--;
						currentThread->activeBurst->cpu_time--;
					}
				} else { //no quantum is set
					currentThread->activeBurst->cpu_time--;
				}
			}
			cpuTime++; //plus one to how long the processor has worked
		} else if ( cpuState == 0 ) { //CPU is NOT active
			if ( switchTimer == 0 ) {
				if ( readyQueue != NULL ) { //if the ready queue is not empty				
					currentThread = readyQueue;
					readyQueue = readyQueue->next;
					currentThread->next = NULL;
					cpuState = 1; //cpu is not active
					if ( currentThread->exec == 0 ) { //first time being executed
						currentThread->exec = 1;
						currentThread->service_time = timeUnit; //service time in now current time
					}
					if( verbose )
						printf("At time %d: Thread %d of Process %d move from READY to RUNNING\n", timeUnit, currentThread->number, currentThread->parentProcess->number);
				} 
			} else if ( switchTimer > 0 ) { //still waiting for switch time
				switchTimer--;
			}
		}
		//END; CPU SIM
		
		//IO SIM
		thread * prev = NULL;
		for( temp = IOList; temp != NULL; prev = temp, temp = temp->next ) { //check all threads in the io list
			if ( temp->activeBurst->io_time == 0 ) {
				temp->activeBurst = temp->activeBurst->next; //load up next burst
				if( prev == NULL ) { //first element
					IOList = IOList->next;
				} else {
					prev->next = temp->next;
				}
				temp->next = NULL;

				if( verbose )
					printf("At time %d: Thread %d of Process %d move from BLOCKED to READY\n", timeUnit, temp->number, temp->parentProcess->number);

				readyQueue = addThread( readyQueue, temp );
			} else {
				temp->activeBurst->io_time--;
				temp->io_time++; //time spent in io
			}
		}
		timeUnit++;	
	}
	cpuUtil = (float)cpuTime / (float)timeUnit * 100;
	average = getTurnaroundAvg( finishedList, totalNumThreads );

	if( quantum > 0 ) { //quantum set
		printf("\n\nRound Robin:\n\n");
	} else {
		printf("\n\nFirst come, first served:\n\n");
	}
	printf("Cputime: %d time units\n", cpuTime );
	printf("Total Time required is %d time units.\n", timeUnit );
	printf("Average Turnaround Time is %.1f time units.\n", average );
	printf("CPU utilisation is %.0f percent.\n", cpuUtil);

	if( details )
		printThreadStats( finishedList );

	return 0;
}

float getTurnaroundAvg( thread * queue, int numThreads ) {
	int totalTurnaround = 0;
	thread * curThread;

	for( curThread = queue; curThread != NULL; curThread = curThread->next ) {
		totalTurnaround += curThread->turnaround_time;
	}

	return totalTurnaround / numThreads;
}

thread * enqueue( process * processes ) {
	process * curProcess = processes;
	thread * list = NULL;

	for( curProcess = processes; curProcess != NULL; curProcess = curProcess->next ) { //join all threads into one big list
		list = addThread( list, curProcess->threads);
	}

	return list;
}

thread * getReady( int timeUnit, thread ** queue ) {
	if( *queue == NULL ) 
		return NULL;

	thread * cur, * prev = NULL;

	for( cur = *queue; cur != NULL; prev = cur, cur = cur->next ) {	
		if ( cur->arrival_time == timeUnit ) {
			if( prev == NULL ) { //cur is first element
				*queue = cur->next;
			} else {
				prev->next = cur->next;
			}
			cur->next = NULL;

			return cur;
		}
	}

	return NULL;
}

simulation * parse( FILE * fp ) {
	int i, j, k;
	char * inStr = malloc(sizeof(char)*100);
	process * newProcess;
	thread * newThread;
	cpu_burst * newBurst;
	//init new sim
	simulation * newSim = (simulation*)malloc(sizeof(simulation));
	newSim->processes = NULL;

	//parse start
	//simulation info
	fgets(inStr, 100, fp);
	newSim->number_of_processes = atoi(strtok(inStr, " "));
	newSim->thread_switch = atoi(strtok(NULL, " "));
	newSim->process_switch = atoi(strtok(NULL, " "));
	//end; simulation info

	for( i = 0; i < newSim->number_of_processes; i++ ) { //loop for number of processes

		//start process
		fgets( inStr, 100, fp );
		newProcess = (process*)malloc(sizeof(process));
		newProcess->number = atoi(strtok(inStr, " "));
		newProcess->number_of_threads = atoi(strtok(NULL, ""));
		newProcess->threads = NULL;

		for( j = 0; j < newProcess->number_of_threads; j++ ) { //loop for the number of threads in a process

			//start thread
			fgets( inStr, 100, fp );
			newThread = (thread*)malloc(sizeof(thread));
			newThread->number = atoi(strtok(inStr, " "));
			newThread->arrival_time = atoi(strtok(NULL, " "));
			newThread->number_of_CPU = atoi(strtok(NULL, " "));
			newThread->status = NEW;
			newThread->parentProcess = newProcess;
			newThread->bursts = NULL;

			for( k = 0; k < newThread->number_of_CPU; k++ ) { //another nested for loop? CPU bursts
				//start burst
				fgets( inStr, 100, fp);
				newBurst = (cpu_burst*)malloc(sizeof(cpu_burst));
				newBurst->number = atoi(strtok(inStr, " "));
				newBurst->cpu_time = atoi(strtok(NULL, " "));
				if( k < newThread->number_of_CPU-1 ) { //not the last cpu burst
					newBurst->io_time = atoi(strtok(NULL, " "));
				} else {
					newBurst->io_time = 0;
				}
				newThread->bursts = addBurst( newThread->bursts, newBurst );
				//end burst
			}
			newThread->activeBurst = newThread->bursts;
			newProcess->threads = addThread( newProcess->threads, newThread );
			//end; thread
		}
		newSim->processes = addProcess( newSim->processes, newProcess );
		//end; process
	} 
	//end; parse
	return newSim;
}

process * addProcess( process * list, process * item ) {
	if( list == NULL ) //if a null list, new item become head
		return item;
	process * curItem = list;
	while( curItem->next != NULL ) {
		curItem = curItem->next;
	}
	curItem->next = item;

	return list;
}

thread * addThread( thread * list, thread * item ) {
	if( list == NULL ) //if a null list, new item become head
		return item;
	thread * curItem = list;
	while( curItem->next != NULL ) {
		curItem = curItem->next;
	}
	curItem->next = item;

	return list;
}

cpu_burst * addBurst( cpu_burst * list, cpu_burst * item ) {
	if( list == NULL ) //if a null list, new item become head
		return item;
	cpu_burst * curItem = list;
	while( curItem->next != NULL ) {
		curItem = curItem->next;
	}
	curItem->next = item;

	return list;
}

int countThreads( thread * list  ) {
	if( list == NULL ) 
		return 0;
	thread * curThread;
	int count = 0;

	for( curThread = list; curThread != NULL; curThread = curThread->next )
		count++;

	return count;
}

void printThreadStats( thread * queue ) {
	thread * curThread;

	for( curThread = queue; curThread != NULL; curThread = curThread->next ) {
		printf("\nThread %d of Process %d\n\n", curThread->number, curThread->parentProcess->number );
		printf("arrival time: %d\n", curThread->arrival_time );
		printf("service time: %d\n", curThread->service_time );
		printf("IO time: %d\n", curThread->io_time);
		printf("turnaround time: %d\n", curThread->turnaround_time);
		printf("finish time: %d\n", curThread->finish_time );
	}
}

void printQueue( thread * queue ) {
	thread * curThread;
	printf("\n");
	for( curThread = queue; curThread != NULL; curThread = curThread->next ) {
		printf("At time 0: Thread # %d of Process %d move from null to NEW\n", curThread->number, curThread->parentProcess->number );
	}
}

void printSimulation( simulation * sim ) {
	process * curProcess;
	thread * curThread;
	cpu_burst * curBurst;

	printf("SIMULATION DATA: %d Processes | Process switch: %d Thread Switch: %d\n\n", sim->number_of_processes, sim->thread_switch, sim->process_switch );

	for( curProcess = sim->processes; curProcess != NULL; curProcess = curProcess->next ) {
		printf("\nProcess # %d Number of Threads: %d\n\n", curProcess->number, curProcess->number_of_threads );
		for( curThread = curProcess->threads; curThread != NULL; curThread = curThread->next ) {
			printf("Thread # %d Arrival Time: %d Number of Bursts: %d\n", curThread->number, curThread->arrival_time, curThread->number_of_CPU );
			for( curBurst = curThread->bursts; curBurst != NULL; curBurst = curBurst->next ) {
				printf("\tBurst # %d CPU Time: %d IO Time: %d\n", curBurst->number, curBurst->cpu_time, curBurst->io_time );
			}
		}
	}
}