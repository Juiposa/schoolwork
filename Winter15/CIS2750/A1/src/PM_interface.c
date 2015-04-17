/*****************
Jeffrey-David Kapp
CIS2750
23 January 2015
Assignment 1
*****************/

//definition of all interface functions

#include "ParameterManager.h"


ParameterManager * PM_create( int size ) {
	ParameterManager * newPM;
	Parameter * newParam;

	newPM = (ParameterManager *)malloc(sizeof(ParameterManager));
	newPM->size = size;
	newPM->param_ll = NULL;

	for( int i = 0; i <= size; i++ ) {
		newParam = param_create();
		newPM->param_ll = param_addToList( newPM->param_ll, newParam );
	}

	return newPM;
}

int PM_destroy( ParameterManager * p ) {
	Parameter * cur_item;
	Parameter * next_item;

	if ( p == NULL ) {
		return 0; //UNSUCCESSFUL; passed value is null
	}

	cur_item = p->param_ll;

	while ( cur_item != NULL ) { //crawl list
		free( cur_item->name );
		if ( cur_item->ptype == STRING_TYPE ) { //if value is a string
			free(cur_item->value.str_val); //free that string
		} else if ( cur_item->ptype == LIST_TYPE ) { //if is a list type
			PL_destroy( cur_item->value ); //free list
		} 
		next_item = cur_item->next; //free list item
		free(cur_item);
		cur_item = next_item;
	} 

	//once linked list is free
	free(p); //free the PM itself

	return 1; //SUCCESSFUL;
}

int PM_parseFrom( ParameterManager * p, FILE * fp, char comment) {
	char inChar = '\0';
	char * paramName;
	char * paramValue;
	char * curStr;
	char ignore[1024];
	union param_value newValue;
	Parameter * curParam;
	int parseState = 0;
	/* parseStates
	 * 0 name read
	 * 1 normal value read; int, float, bool
	 * 2 string read;
	 * 3 list read
	*/

	paramName = malloc(sizeof(char)*100);
	paramValue = malloc(sizeof(char)*100);

	paramName[0] = '\0';
	paramValue[0] = '\0';

	curStr = paramName; //expecting a name first

	while( !feof(fp) ) {
		inChar = fgetc(fp);
		switch( inChar ) {
			case ' ': case '\0': case '\n': //whitespace
				if( parseState == 0 || parseState == 1 ) { //in a proper parse state
					//NOOP
				} else {
					append(curStr, inChar); //add to end of cur string
				} 
				break;
			case '=': //should start expecting a value
				if ( parseState == 1 ) { //we're already expecting, syntax error
					fputs("PARSE:SYNTAX ERROR**** Misplaced =\n", stderr);
					free(paramName);
					free(paramValue);
					return 0;
				} else if ( strlen(paramName) == 0 ) { //paramName hasnt been written to
					fputs("PARSE:PARSE ERROR**** Unnamed parameter\n", stderr);
					free(paramName);
					free(paramValue);
					return 0;
				}
				curStr = paramValue; //working string is now the value
				parseState = 1; //switch to value read
				break;
			case '"': //expecting a string specifically
				if ( parseState == 0 ) { //names dont have "" silly
					fputs("PARSE:SYNTAX ERROR**** Misplaced \"\n", stderr);
					free(paramName);
					free(paramValue);
					return 0;
				} else if ( parseState ==  2 ) { // already reading a string
					parseState = 1; // back to normal
				} else if ( parseState == 3 ) { //we need to ignore quotes
					//NOOP
				} else {
					parseState = 2;
				} 
				break;
			case '{': case '[': //opening a list
				if ( parseState == 0 ) {
					fputs("PARSE:SYNTAX ERROR**** Misplaced {\n", stderr);
					free(paramName);
					free(paramValue);
					return 0;
				} else {
					parseState = 3; //start expecting a list
				}
				break;
			case '}': case ']': //ending a list
				if ( parseState != 3 ) { //syntax error, random close brace :/
					fputs("PARSE:SYNTAX ERROR**** Misplaced }\n", stderr);
					free(paramName);
					free(paramValue);
					return 0;
				}
				if ( strlen(paramValue) > 0 ) { //has some sort of value
					newValue = readParameterList(paramValue); //parse the param list
					parseState = 1;
				} else {
					fputs("PARSE:PARSE ERROR**** Empty list\n", stderr);
					free(paramName);
					free(paramValue);
					return 0;
				}
				break;
			case ';': //end of line
				if ( parseState != 1 ) { //state 1 is only state where a ; is valid
					fputs("PARSE:SYNTAX ERROR****  Misplaced ;\n", stderr);
					free(paramName);
					free(paramValue);
					return 0;
				} else if ( strlen(paramName) == 0 || strlen(paramValue) == 0 ) { //null name or value
					fputs("PARSE:PARSE ERROR**** Empty name or value\n", stderr);
					free(paramName);
					free(paramValue);
					return 0;
				}
				curParam = getParameter( p->param_ll, paramName );
				if ( curParam == NULL ) { //NOT a member
					fputs("PARSE:PARSE WARNING**** Parameter not registered; ignore\n", stderr);
					parseState = 0;
					curStr = paramName;
					memset(paramName, 0, strlen(paramName));
					memset(paramValue, 0, strlen(paramValue));
				} else {
					switch( curParam->ptype ) {
						case INT_TYPE:
							curParam->value.int_val = atoi(paramValue);
							break;
						case REAL_TYPE:
							curParam->value.real_val = atof(paramValue);
							break;
						case BOOLEAN_TYPE:
							if(strcmp(paramValue, "true") == 0) {
								curParam->value.bool_val = true;
							} else { //all others false
								curParam->value.bool_val = false;
							}
							break;
						case STRING_TYPE:
							curParam->value.str_val = malloc(sizeof(char)*100);
							strcpy(curParam->value.str_val, paramValue);
							break;
						case LIST_TYPE:
							curParam->value = newValue;
							break;
						default:
							fputs("PARSE:PARAM ERROR**** Invalid ptype\n", stderr);
							free(paramName);
							free(paramValue);
							return 0;
							break;
					}
					curParam->status = 2;
					parseState = 0;
					curStr = paramName;
					memset(paramName, 0, strlen(paramName));
					memset(paramValue, 0, strlen(paramValue));
				}
				break;
			default: 
				if ( inChar != comment ) { //non control character
					append(curStr, inChar);
				} else { //comment line
					fgets( ignore, sizeof(ignore), fp);
				}
				break;
		}
	}

	if ( !(checkRequired(p->param_ll))) {
		fputs("PARSE:PARSE ERROR**** Requried parameter(s) not found\n", stderr);
		free(paramName);
		free(paramValue);
		return 0;
	}


	free(paramName);
	free(paramValue);

	fputs("PARSE:SUCCESS\n", stderr);
	return 1;
}

int PM_manage( ParameterManager * p, char * pname, param_t ptype, int required ) {
	Parameter * param_set; //parameter to be written to

	param_set = getBlankParameter( p->param_ll );

	if ( param_set == NULL ) { //there was an error in getBlankParameter
		return 0; //UNSUCCESSFUL; parameter error
	} else {
		strcpy( param_set->name, pname ); 
		param_set->ptype = ptype;
		param_set->required = required;
		param_set->status = 1; //registered but has no value
	}
	return 1; //SUCCESSFUL;
}

int PM_hasValue( ParameterManager * p, char * pname ) {
	Parameter * param;
	if ( p == NULL ) {
		return 0;
	}
	param = getParameter( p->param_ll, pname );
	if ( param != NULL && param->status == 2 ) { //if its not null and has status 2, it should have value
		return 1;
	} 
	return 0;
}

union param_value PM_getValue( ParameterManager * p, char * pname ) {
	Parameter * param = getParameter( p->param_ll, pname );
	return param->value; 
}

char * PL_next( ParameterList * l ) {
	ParameterList * cur_item = l;
	while ( cur_item != NULL ) {
		if ( cur_item->accessed == 0 ) {
			cur_item->accessed = 1; //its been accessed
			return cur_item->str_val;
		}
		cur_item = cur_item->next;
	}
	return NULL;
}