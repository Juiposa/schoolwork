/*****************
Jeffrey-David Kapp
CIS2750
23 January 2015
Assignment 1
*****************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//boolean data type
typedef enum { false, true } Boolean;

//data types for a given parameter
typedef enum { INT_TYPE, REAL_TYPE, BOOLEAN_TYPE, STRING_TYPE, LIST_TYPE } param_t;

//possible parameter values and thier types
union param_value {
	int int_val;
	float real_val;
	Boolean bool_val;
	char * str_val;
	struct ParameterList * list_val;
};

//base parameter struct, storing name, value and data type; linked list
typedef struct Parameter {
	int status; //0, blank; 1, registered but no value; 2, has value
	int required;
	char * name;
	param_t ptype;
	union param_value value;
	struct Parameter * next;
} Parameter;

//list of parameter values; linked list
typedef struct ParameterList {
	char * str_val;
	int accessed;
	struct ParameterList * next;
} ParameterList;


//master data type; used in following interface
typedef struct ParameterManager {
	Parameter * param_ll; //linked list of parameters
	int size; //strictly the number of items to be managed
} ParameterManager;

//function definition:

//Parameter manager interface;
//These functions are to be used to interface with the parameter manager; declared as outlined

/* PM_create
 * initialises an empty PM
 * Parameters: size	- number of items to be managed by the PM
 * Returns: initialised and empty PM is succeddful, null otherwise
*///DONE
ParameterManager * PM_create( int size );

/* PM_destroy
 * destroys a PM
 * Parameters: 	p - PM to be destroyed
 * Returns: 1 on success, 0 otherwise
*///DONE
int PM_destroy( ParameterManager * p );

/* PM_parseFrom
 * parses a stream for param names and values; sets up ParameterManager
 * Parameters:	p - ParameterManager to be read into
 *				fp - input stream to read from
 *				comment - character used for starting comments in fp
 * Returns: 1 on success, 0 otherwise
*/
int PM_parseFrom( ParameterManager * p, FILE * fp, char comment );

/* PM_manage
 * register parameters with manager and if they are mandatory
 * Parameters:	p - ParameterManager
 *				pname - name of parameter to be managed
 *				ptype - expected data type of param value
 *				required - 1 for mandatory, 0 for optional
 * Returns: 1 on success, 0 otherwise
*///DONE
int PM_manage( ParameterManager * p, char * pname, param_t ptype, int required );

/* PM_hasValue
 * checks if a given parameters has a value assigned to it
 * Parameters:	p - ParameterManager
 *				pname - parameter to check
 * Returns: 1 if it does, 0 if not
*/
int PM_hasValue( ParameterManager * p, char * pname );

/* PM_getValue
 * get paramter's value
 * Parameters:	p - ParameterManager
 *				pname - parameter to fetch
 * Returns: value assigned to pname, undefined if unknown or undefined
*/
union param_value PM_getValue( ParameterManager * p, char * pname );

/* PL_next
 * returns next parameter value in a paramlist
 * Parameters: 	l - list to iterate through
 * Return: string value stored
*/
char * PL_next( ParameterList * l );


//internal functions
//functions used by interface

//creation and destruction; PM_create, PM_destroy

/* param_create
 * creates and allocates memory for a single empty parameter
 * Parameters: none
 * Returns: and empty parameter
*///DONE
Parameter * param_create();

/* param_addToList
 * adds a parameter to a linked list
 * Parameters:	param_ll - linked list of parameters
 *				toAdd - parameter to be added
 * Returns: pointer to head of list
*///DONE
Parameter * param_addToList( Parameter * param_ll, Parameter * toAdd );

/* PL_destroy
 * destroy a paramter list data type
 * Parameter:	param_list - data union the list is in
 * Returns: 1 on success, 0 otherwise
*///DONE
int PL_destroy( union param_value param_list );

/* PL_addToList
 * adds a parameter list item to a given list
 * Parameters:	param_list - list to be added to
 *				toAdd - node to add
 * Returns: pointer to list header
*/
ParameterList * PL_addToList( ParameterList * param_list, ParameterList	*  toAdd ); 

/* PL_create
 * creates a PL node
 * Parameters: 	str_val - string to be stored
 * Returns: new node
*/ 
ParameterList * PL_create( char * str_val );

//pm management; PM_manage

/* getBlankParameter
 * gets the next blank parameter to register to
 * Parameters: 	param_ll - linked list to check
 * Returns: pointer to blank parameter; NULL if all parameters are occupied
*///DONE
Parameter * getBlankParameter( Parameter * param_ll );

//parsing; PM_parseFrom

/* readParameterList
 * parses a string limited by commas and build a paramList
 * Parameters:	paramValue - string to be parsed
 * Returns: a union param_value containing the constructed paramList
*/ 
union param_value readParameterList( char * paramValue );

/* append
 * adds a character to the end of a string
 * Parameters:	str - string to add to
 *				ch - char to add
 * Returns: nothing
*/
void append( char * str, char ch );

//parameter fetching; PM_parseFrom, PM_getValue, PM_hasValue

/* getParameter
 * finds a given parameter
 * Parameters:	param_ll - list to search
 *				pname - name of the parameter to look for
 * Returns: pointer to the fetched parameter, null if not found or empty list
*///DONE
Parameter * getParameter( Parameter * param_ll, char * pname );

/* checkRequired
 * checks if required parameters have been read in
 * Parameters: 	param_ll - list to check
 * Returns: true false
*/
int checkRequired( Parameter * param_ll );