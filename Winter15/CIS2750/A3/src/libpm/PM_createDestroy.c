/*****************
Jeffrey-David Kapp
CIS2750
23 January 2015
Assignment 1
*****************/

//creation and destruction functions; 
//used by PM_create, PM_destroy
#include "ParameterManager.h"

Parameter * param_create() {
	Parameter * newParam;
	newParam = (Parameter *)malloc(sizeof(Parameter));
	newParam->name = malloc(sizeof(char)*50);
	newParam->status = 0;
	newParam->required = 0;
	newParam->ptype = 0;
	newParam->next = NULL;
	return newParam;
}

Parameter * param_addToList( Parameter * param_ll, Parameter * toAdd ) {
	Parameter * cur_item;
	cur_item = param_ll;
	if ( cur_item == NULL ) {
		toAdd->next = NULL;
		return toAdd;
	} else {
		while( cur_item->next != NULL ) {
			cur_item = cur_item->next;
		}
		cur_item->next = toAdd;
	}
	return param_ll;
}

ParameterList * PL_create( char * str_val ) {
	ParameterList * newListItem = (ParameterList *)malloc(sizeof(ParameterList));
	newListItem->str_val = malloc(sizeof(char)*100);
	strcpy( newListItem->str_val, str_val);
	newListItem->accessed = 0;
	newListItem->next = NULL;
	return newListItem;
}

ParameterList * PL_addToList( ParameterList * param_list, ParameterList	*  toAdd ) {
	ParameterList	 * cur_item;
	cur_item = param_list;
	if ( cur_item == NULL ) {
		toAdd->next = NULL;
		return toAdd;
	} else {
		while( cur_item->next != NULL ) {
			cur_item = cur_item->next;
		}
		cur_item->next = toAdd;
	}
	return param_list;
}

int PL_destroy( union param_value param_list ) {
	ParameterList * cur_item = param_list.list_val;
	ParameterList * next_item;

	if ( cur_item == NULL ) { //UNSUCCESSFUL; passed value is null
		return 0;
	}

	while ( cur_item != NULL ) { //free list of parameter values
		free(cur_item->str_val);
		next_item = cur_item->next;
		free(cur_item);
		cur_item = next_item;
	}

	return 1; //SUCCESSFUL;
}
