/********************
Jeffrey-David Kapp
0832671
CIS2520 Assignment 2
14 Oct 2014
********************/

#include "carRental.h"


int main() {

	char inputStr[100]; //string for control and input
	//float * totalProfit; //total profit made on the cars; will reset everytime program is started

	rentalCar * availableList = NULL;
	rentalCar * rentList = NULL;
	rentalCar * repairList = NULL;

	availableList = readFromFile( availableList, "doc/availableList.txt");

	do {
		printOptions();

		fgets( inputStr, 100, stdin );

		switch ( inputStr[0] ) {
			case '1':
				availableList = newCar( availableList );
				break;
			case '2': break;
			case '3': break;
			case '4': break;
			case '5': 
				break;
			case '6': 
				printLists( availableList, rentList, repairList );
				break;
			case '7': 
				printToFile( availableList, "doc/availableList.txt" );
				break;
			default:
				printf("Invalid input.\n");
				break;
		}

	} while ( inputStr[0] != '7' );

	return 1;

}

float calcCharge( int startMileage, int endMileage ) {
	int distance =  endMileage - startMileage; 
	if ( distance <= 100 ) {
		return 40.0;
	} else  {
		distance -= 100;
		return 40 + ( distance * 0.15 );
	}
}

void returnCar( rentalCar * rentList, rentalCar * availableList, float * totalProfit ) {
	rentalCar * returnedCar;
	char inputString[100];
	char * plateNumber;
	int returnMileage = 0;
	float tripCharge = 0.0;

	plateNumber = getPlateNumber();

	returnedCar = findCar( rentList, plateNumber ); //getting the car indicated by user

	if ( returnedCar != NULL ) { //if it actually exists

		printf("What is the mileage after return?\n"); //get the mileage coming in
		fgets( inputString, 100, stdin );

		returnMileage = atoi( inputString ); //convert to interger
		if ( !(returnMileage < *returnedCar->odometer) ) { //if the returned mileage is larger than it was before it was sent out
			tripCharge = calcCharge( *returnedCar->odometer, returnMileage ); //calculating trip charge
			*totalProfit += tripCharge; //adding charge to total
			printf("Total charge for trip: $%.2f", tripCharge );
			*returnedCar->odometer = returnMileage; //setting the cars mileage to return mileage
			changeListOdometer( availableList, returnedCar ); //change retured car to the avialable list
		} else {
			printf("Car cannot have less mileage coming in than it went out with.\n");
		}
	} else {
		printf("Car does not exist or plate number entered incorrectly.\n");
	}
}

void rentOutCar( rentalCar * rentList, rentalCar * availableList ) {
	rentalCar * carToBeRented; 
	char inputString[100];

	carToBeRented = popCar( availableList ); //pop first available car
	do {
		printf("When is the car expected back? (ddmmyyyy)");
		fgets( inputString, 100, stdin);		
	} while ( strlen(inputString) != 8 ); //while the user did no enter exactly 8 characters for the date
	rentList = changeListDate( rentList, carToBeRented ); //change it to the rented list
}

void sendForRepair( char * plateNumber, rentalCar * repairList, rentalCar * availableList ) {
	rentalCar * carToBeRepaired; //car that will be sent for repair

	if ( plateNumber == NULL ) { //if a platenumber was not passed
		plateNumber = getPlateNumber(); //get one from the user
	}

	carToBeRepaired = findCar( availableList, plateNumber ); //finding the car that needs to be repaired

	if ( carToBeRepaired != NULL ) { //if the car exists
		changeListOdometer( repairList, carToBeRepaired ); //change to the repair list
	} else {
		printf("Car does not exist or plate number entered incorrectly.\n");
	}
}

void returnFromRepair( char * plateNumber, rentalCar * repairList, rentalCar * availableList ) {
	rentalCar * carToBeReturned; //car to be returned from the repair list

	if ( plateNumber == NULL ) { //if a platenumber was not passed
		plateNumber = getPlateNumber(); //get one from the user
	}

	carToBeReturned = findCar( repairList, plateNumber );

	if ( carToBeReturned != NULL ) { //if the car exists
		changeListOdometer( availableList, carToBeReturned ); //change it to the available list
	} else {
		printf("Car does not exist or platenumber entered incorrectly.\n");
	}

}

rentalCar * newCar( rentalCar * availableList ) {
	char * newPlateNumber;
	int * odometer;
	int * returnDate;
	rentalCar * newCarDec;

	newPlateNumber = (char *)malloc(100*sizeof(char));
	odometer = malloc(sizeof(int));
	returnDate = malloc(sizeof(int));

	*returnDate = 0;

	char inputString[100];
	int count = 0;

	printf("Enter a plate number followed by the car's odometer.\n");
	do {
		fgets( inputString, 100, stdin );

		inputString[strlen(inputString)-1] = '\0'; //setting end character to a null terminator

		if ( strlen(inputString) != 0 && count ==  0 ) { //if the first value is to be entered
			strcpy( newPlateNumber, inputString );
			count++;
		} else if ( strlen(inputString) != 0 && count == 1 ) { //if first value has been entered
			*odometer = atoi(inputString);
			count++;
		}

	} while( count != 2  ); //do while the user enters both values, will not terminate otherwise

	newCarDec = newCarConstruct( newPlateNumber, odometer, returnDate );

	availableList = addToList( availableList, newCarDec );

	return availableList;

}

void printLists( rentalCar * availableList, rentalCar * rentList, rentalCar * repairList ) {
	rentalCar * curNode;

	curNode = availableList;
	printf("Available to rent list.\n");
	do { //available list
		printf("Car; Platenumber: %s; Odometer: %i\n", curNode->plateNumber, *curNode->odometer );
		curNode = curNode->next;		
	} while ( curNode != NULL);
	/*
	curNode = rentList;
	printf("Rented cars.\n");
	do { //rented list
		printf("Car; Platenumber: %s; Odometer: %i; Expected return date: %i\n", curNode->plateNumber, *curNode->odometer, *curNode->returnDate );
		curNode = curNode->next;
	} while ( curNode->next != NULL );
	
	curNode = repairList;
	printf("Cars being repaired.\n");
	do { //repair list
		printf("Car; Platenumber: %s; Odometer: %i\n", curNode->plateNumber, *curNode->odometer );
		curNode = curNode->next;
	} while ( curNode->next != NULL );
	*/
}

char * getPlateNumber() {
	char * plateNumber = NULL;

	printf("What is the plate number of the car?\n");
	fgets( plateNumber, 100, stdin );

	return plateNumber;
}

void printOptions() {
	printf("Choose an option:\n");
	printf("1) add a new car to the available to rent list\n");
	printf("2) add a returned car to the avialable to rent list\n");
	printf("3) add a returned car to the repair list\n");
	printf("4) transfer a car from the repair list to the available to rent list\n");
	printf("5) rent the first avialable car\n");
	printf("6) print all the lists\n");
	printf("7) quit\n");
}