/*******************
CIS3110 Assignment 2
Jeffrey-David Kapp
27 Feb 2014
0832671
*******************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { NEW, READY, RUNNING, BLOCKED, TERMINATED } state;

typedef struct cpu_burst {
	int number;
	int cpu_time;
	int io_time;
	struct cpu_burst * next;
} cpu_burst;

typedef struct thread {
	//working data
	int number;
	state status;
	int arrival_time;
	int number_of_CPU;
	int exec; //if a thread has been executed already; for stats
	cpu_burst * activeBurst;
	//statistical data
	int service_time;
	int io_time;
	int turnaround_time;
	int finish_time;
	//lists
	struct process * parentProcess;
	cpu_burst * bursts;
	struct thread * next;
} thread;

typedef struct process {
	//working data
	int number;
	int number_of_threads;
	//lists
	thread * threads;
	struct process * next;
} process;

typedef struct simulation {
	int number_of_processes;
	int thread_switch;
	int process_switch;
	process * processes;
} simulation;

/* getTurnaroundAvg
 * calcs turnaround average across all threads
 * Parameters: 	queue - list of threads to tally
 *				numThreads - total number of threads
 * Returns: average turnaround time
*/
float getTurnaroundAvg( thread * queue, int numThreads );

/* enqueue
 * merges thread lists into single ready queue
 * Parameters: 	processes - list of processes
 * Returns: newQueue
*/
thread * enqueue( process * processes );

/* getReady
 * gets threads that arrive at a given time, removes from new list
 * Parameters: 	time - time specified
 *				queue -  queue to search
 * Return: pointer to removed thread
*/
thread * getReady( int time, thread ** queue );

/* parse
 * Will parse a file and build a simulation from it
 * Parameters:	fp - file to parse from
 * Returns: completed process structure - null on error
*/
simulation * parse( FILE * fp );

/* add*
 * Will add a repective item to a list
 * Parameters:	list - list to add to
 * 				item - item to add
 * Returns: pointer to new list head
*/
process * addProcess( process * list, process * item );
thread * addThread( thread * list, thread * item );
cpu_burst * addBurst( cpu_burst * list, cpu_burst * item );


/* countThreads
 * will count the number of threads in a given queue/list
 * Parameters:	list - list/queue to count
 * Returns: number of items
*/
int countThreads( thread * list );

/* printThreadStats
 * prints stats gathered by threads
 * Parameters: 	queue - list of threads to print
 * Returns: nothing
*/
void printThreadStats( thread * queue );


/* printSimulation
 * debug printing
*/
void printSimulation( simulation * sim );
void printQueue(thread * queue);
