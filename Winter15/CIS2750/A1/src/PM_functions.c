/*****************
Jeffrey-David Kapp
CIS2750
23 January 2015
Assignment 1
*****************/

#include "ParameterManager.h"

//extra functions used by multiple interface functions or would otherwise compose single function files

//Used by PM_manage
Parameter * getBlankParameter( Parameter * param_ll ) {
	Parameter * cur_item = param_ll;
	while ( cur_item != NULL ) { //walk list
		if ( cur_item->status == 0 ) { //blank parameter
			return cur_item; //we return it
		}
		cur_item = cur_item->next;
	}
	return NULL; //if this loop terminates for any reason, there was a problem
	//either the list is full or there is another error
}

//Used by PM_parseFrom
union param_value readParameterList( char * paramList ) {
	int parseState = 1;
	char inChar;
	union param_value newValue;
	ParameterList * newListItem;
	char * readVal = malloc(sizeof(char)*100);
	readVal[0] = '\0';
	newValue.list_val = NULL;
	for ( int i = 0; i < strlen(paramList); i++ ) {
		inChar = paramList[i];
		switch( inChar ) {
			case ' ': case '\0': case '\n': //whitespace
				if( parseState == 1 ) { //in a proper parse state
					//NOOP
				} else {
					append(readVal, inChar); //add to end of cur string
				} 
				break;
			case '"': //expecting a string specifically
				if ( parseState ==  2 ) { // already reading a string
					parseState = 1; // back to normal
				} else {
					parseState = 2;
				}
				break;
			case ',': //end val
				newListItem = PL_create( readVal );
				newValue.list_val = PL_addToList(newValue.list_val, newListItem);
				parseState = 1;
				memset(readVal,0,strlen(readVal));
				break;
			default:
				append(readVal, inChar);

				break;
		}
		if ( i ==  strlen(paramList) - 1 && strlen(readVal) > 0 ) { //if anything past last comma in list, get that in list as well
			newListItem = PL_create( readVal );	
			newValue.list_val = PL_addToList(newValue.list_val, newListItem);	
		}
	}
	free(readVal);
	return newValue;
}

//Used by multiple, see header file
Parameter * getParameter( Parameter * param_ll, char * pname ) {
	Parameter * cur_item = param_ll;
	while ( cur_item->next != NULL ) {
		if ( strcmp( cur_item->name, pname ) == 0 ) {
			return cur_item;
		}
		cur_item = cur_item->next;
	}
	return NULL;
}

int checkRequired( Parameter * param_ll ) {
	Parameter * cur_item = param_ll;
	while ( cur_item->next != NULL ) {
		if ( cur_item->required == 1 && cur_item->status != 2 ) { //if the param is registered and has been written to
			return 0;
		}
		cur_item = cur_item->next;
	}
	return 1;
}

void append( char * str, char ch ) {
	int len = strlen(str);
	str[len] = ch;
	str[len+1] = '\0';
}

