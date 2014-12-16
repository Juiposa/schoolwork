/********************
Jeffrey-David Kapp
0832671
CIS2520 Assignment 2
14 Oct 2014
********************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

//rental car attribute structure
typedef struct rentalCar {

	char * plateNumber; //license plate number
	int * odometer; //current mileage
	int *  returnDate; //expected date of return
	
	//linked list pointers
	struct rentalCar * next;
	struct rentalCar * prev;

} rentalCar;

//carList.c fucntions//

/* calcCharge
 * Calculates the charge incurred when car is returned
 * Parameters: 	startMileage - mileage before the car was rented out
 *				endMileage - mileage when the car is returned
 * Returns: total charge for that car
*/
float calcCharge( int startMileage, int endMileage );

/* returnCar
 * Handles procedure to return a car
 * Parameters:	rentList - list of rented cars
 *				availableList - list of available
 *				totalProfit - total amount made from the cars so far 
 * Returns: nothing
*/
void returnCar( rentalCar * rentList, rentalCar * availableList, float * totalProfit );

/* rentOutCar
 * does exactly as the name suggests
 * Parameters:	rentList - list of rented cars
 *				availableList - list of avialable cars
 * Returns: nothing
*/
void rentOutCar( rentalCar * rentList, rentalCar * availableList );

/* sendForRepair
 * ditto
 * Parameter:	plateNumber - platenumber of the car to be sent for repairs
 *				repairList - list of cars that are being repaired
 *				availableList - list of car avialable
 * Returns: nothing
*/
void sendForRepair( char * plateNumber, rentalCar * repairList, rentalCar * availableList );

/* returnFromRepair
 * returns car from repiar list to avialable to rent list
 * Parameters: 	plateNumber - plate number of the car to be sent to available list
 *				repairList - list of cars that are being repaired
 *				availableList - list of car avialable
 * Returns: nothing
*/
void returnFromRepair( char * plateNumber, rentalCar * repairList, rentalCar * availableList );

/* newCar
 * new car creation then adding to avilable to rent list
 * Parameters: availableList - list of available cars
 * Returns: pointer to the new list
*/
rentalCar * newCar( rentalCar * availableList );

/* printLists
 * prints all three lists
 * Parameters: 	headers for each of the respective lists
 *				availableList
 *				rentList
 *				repairList
 * Returns: nothing
*/
void printLists( rentalCar * availableList, rentalCar * rentList, rentalCar * repairList );

/* getPlateNumber
 * Asks user for a platenumber and returns the string
 * Parameters: None
 * Returns: string pointer of the plate number
*/
 char * getPlateNumber();

/* printOptions
 * Prints menu options, organisational thing
 * Parameters: None
 * Returns: Nothing
*/
 void printOptions();

//fileIO.c functions//

/* printToFiled
 * Prints a list ta a specified file in a formatted way
 * Paraemeters: listHead - head of list to be stored
 * 				fileName - path of the file to be used
 * Returns:	nothing
*/
void printToFile( rentalCar * listHead, char * fileName );

/* readFromFile
 * Reads a file and parses info into a provided list
 * Parameters: 	listHead - a (should be) null pointer from which the list will be built
 *				fileName - file to read from
 * Returns: header to constructed list
*/
rentalCar * readFromFile( rentalCar * listHead, char * fileName );

//linked lists functions//

/* addToList
 * Will add a new car to the avail to rent list
 * Parameters: listHead - headers of the available to rent list
 *				car - completed structure of car to be added, if null; will return null
 * Returns: pointer to the new list
*/
rentalCar * addToList( rentalCar * listHead, rentalCar * car );

/* changeList
 * Will remove a provided car from its current list and transfer it to the specified list, sort based on the odometer
 * Parameters: listHead - head of the list the car is to be transfered to
 *			   car - car that needs to be transfered
 * Returns: pointer to the new list
*/
rentalCar * changeListOdometer( rentalCar * listHead, rentalCar * car );

/* changeList
 * Will remove a provided car from its current list and transfer it to the specified list, sorts based on the expected return date
 * Parameters: listHead - head of the list the car is to be transfered to
 *			   car - car that needs to be transfered
 * Returns: pointer to the new list
*/
rentalCar * changeListDate( rentalCar * listHead, rentalCar * car );

/* findCar
 * Finds a car in the provided list
 * Parameters: listHead -  head of the list to be searched
 * 			   plateNumber - plate of the car to be found
 * Returns: pointer to the car in question; else if car is not found or one of the parameters is null, returns null
*/
rentalCar * findCar( rentalCar * listHead, char * plateNumber );

/* popCar
 * pops the first element off the head of the list
 * Parameters: list - list to be edited
 * Returns: first element from the list
*/
rentalCar * popCar( rentalCar * listHead );

/* newCarConstuct
 * constructor for a new car
 * Parameters - plateNumber; plate number
 *				odometer; mileage at entry
 *				note that return date is set to null by default until set when car is sent out
 * Returns: new car struct
*/
rentalCar * newCarConstruct( char * plateNumber, int * odometer, int * returnDate ); 

/* destroyList
 * destroys a list and frees all the memory it used
 * Parameters: listHead - head of the list to be destroyed
 * Returns: nothing
*/
void destroyList( rentalCar * listHead );