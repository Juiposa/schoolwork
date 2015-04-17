/*******************
Jeffrey-David Kapp
0832671
27 March 2015
CIS3110 Assignment 3
********************/

#include "part1.h"

pthread_mutex_t m_fork;
pthread_cond_t m_cond;

int main( int argc, char * argv[] ) {
	pthread_t philosophers;

	thread_data phil_data;
	phil_data.mynumber = 0;
	pthread_cond_init(&m_cond,NULL);

	pthread_create(&philosophers, NULL, philosopher, (void*) &phil_data );
	printf("Sleep\n");
	sleep(1);
	pthread_cond_signal(&m_cond);
	sleep(1);
	printf("I can use pthreads to a basic level! Yay! \n");
	return 0;
}

void * philosopher( void * param ) {
	printf("Thread\n");
	pthread_mutex_lock(&m_fork);
	printf("Locked\n");
	pthread_cond_wait(&m_cond, &m_fork );
	printf("Continued\n");
	pthread_mutex_unlock(&m_fork);
	return (void*)0;
}