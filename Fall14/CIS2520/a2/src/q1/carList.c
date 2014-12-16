/********************
Jeffrey-David Kapp
0832671
CIS2520 Assignment 2
14 Oct 2014
********************/

#include "carRental.h"

rentalCar * addToList( rentalCar * listHead, rentalCar * car) {
	rentalCar * curNode;

	curNode = listHead;

	do {
		if ( curNode == NULL ) { //if list head is null, therefore first in list
			listHead = car;
			listHead->prev = NULL;
			listHead->next = NULL;
			return listHead;
		} else if ( curNode->next == NULL && curNode->prev == NULL ) { //both before and after are null, therefore only one in list in the list
			if ( *car->odometer <= *curNode->odometer ) { //if mileage is smaller on the car being added
				curNode->prev = car;
				car->next = curNode;
				listHead = car;
				return listHead;
			} else {
				car->prev = curNode;
				curNode->next = car;
				listHead = curNode;
				return listHead;
			}
		} else if ( curNode->prev == NULL && curNode->next != NULL ) { //if there is nothing before but something after
			if ( *car->odometer <= *curNode->odometer ) { //if mileage is smaller on the car being added
				curNode->prev = car;
				car->next = curNode;
				listHead = car;
				return listHead;
			}
		} else if ( curNode->prev != NULL && curNode->next != NULL ) {
			if ( *car->odometer >= *curNode->odometer && *car->odometer <= *curNode->next->odometer ) { //if larger than previous and smaller than next
				car->prev = curNode; //add to list at that point
				car->next = curNode->next;
				curNode->next = car;
				curNode->next->prev = car;
				return listHead;
			} 
		} else if ( curNode->prev != NULL && curNode->next == NULL ) {
			curNode->next = car;
			car->prev = curNode;
			return listHead;
		} 

		curNode = curNode->next;

	} while ( curNode != NULL );

	return listHead;
}

rentalCar * changeListOdometer( rentalCar * listHead, rentalCar * car ) {

	return listHead;
}

rentalCar * changeListDate( rentalCar * listHead, rentalCar * car ) {

	return listHead;
}

rentalCar * findCar( rentalCar * listHead, char * plateNumber ) {
	rentalCar * curNode;

	curNode = listHead;

	do {
		if( strcmp(curNode->plateNumber, plateNumber) == 0 ) { //if car is found
			return curNode; //return it
		} else {
			curNode = curNode->next;
		}
	} while ( curNode->next != NULL );

	return NULL; // if car is not found, return NULL
}

rentalCar * popCar( rentalCar * listHead ) {
	rentalCar * poppedCar;
	poppedCar = listHead;
	listHead = listHead->next;
	return poppedCar;
}

rentalCar * newCarConstruct( char * plateNumber, int * odometer, int * returnDate ) {
	rentalCar * newCarStruct;

	newCarStruct = malloc(sizeof(rentalCar));

	newCarStruct->plateNumber = plateNumber;
	newCarStruct->returnDate = returnDate;
	newCarStruct->odometer = odometer;

	return newCarStruct;
}

void destroyList( rentalCar * listHead ) {
	rentalCar * curNode;
	rentalCar * nextNode;

	curNode = listHead;

	do {
		free(curNode->odometer);
		free(curNode->plateNumber);
		free(curNode->returnDate);
		nextNode = curNode->next;
		free(curNode);
		curNode = nextNode;
	} while( curNode->next != NULL );
}
