/*******************
Jeffrey-David Kapp
0832671
27 March 2015
CIS3110 Assignment 3
********************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

//data to be passed to a thread
typedef struct thread_data {
	int mynumber; //the philosopher's number
	pthread_cond_t cond; //conditions for locking/unlocking a mutex var
} thread_data;

//pthread execution start
//will carry out what a "philosopher" needs to do
void * philosopher( void * param );