%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include "ParameterManager.h"
void yyerror(const char *);
extern char * yytext;
extern FILE * yyin;

//compiler variable declaration
ParameterManager * tfb; //form title, fields, and buttons
ParameterManager * types; //data types for fields and buttons' action listeners
ParameterManager * activePM; //active PM yyparse is pluggin into
Parameter * curParam;
union param_value newList;
ParameterList * newListItem;
ParameterList * cur_item;
int fieldCount = 0;
int  buttonCount = 0;
char filePath[1024];
char workingDirectory[1024];
char projectName[1024];
char * curChar;
int i = 0; 
%}

%union {
	char *str;
}

%token EQUALS R_PAREN L_PAREN QUOTE COLON COMMENT COMMA EXCLAIM NEWLN  
%token <str> WORD
%type <str> quoted_word value
%%

start 		: config
			;

config 		: statement config 
			| statement NEWLN config 
			| statement NEWLN 
			| statement 
			| NEWLN config
			| NEWLN
			| comments config
			;

comments	: COMMENT comments NEWLN
			| COMMENT comments
			| WORD comments
			| WORD 
			| COMMENT
			| EXCLAIM COMMENT { return 0; /*terminate on filebreak*/}
			;

statement  	: WORD EQUALS value COLON { 
				curParam = getParameter(activePM->param_ll, $1 );
				if (curParam != NULL ) { //is member of the PM
					switch( curParam->ptype ) {
						case STRING_TYPE:
							curParam->value.str_val = malloc(sizeof(char)*100);
							strcpy(curParam->value.str_val, $3 );
							break;
						case LIST_TYPE:
							curParam->value = newList;
							newList.list_val = NULL;
							break;
					}
					curParam->status = 2;
				}
			}
           	;

value	 	: quoted_word { $$ = $1; }
			| WORD
			| L_PAREN list 
 		   	;

list		: WORD COMMA list { newListItem = PL_create( $1 ); newList.list_val = PL_addToList(newList.list_val, newListItem); }
			| quoted_word COMMA list { newListItem = PL_create( $1 ); newList.list_val = PL_addToList(newList.list_val, newListItem); }
			| quoted_word R_PAREN { newListItem = PL_create( $1 ); newList.list_val = PL_addToList(newList.list_val, newListItem); }
			| WORD R_PAREN { newListItem = PL_create( $1 ); newList.list_val = PL_addToList(newList.list_val, newListItem); }
			;

quoted_word : QUOTE WORD QUOTE { $$ = $2; }
			;

%%


void yyerror(const char *s) { fprintf(stdout, "%s %s\n", s, yytext); }

int main(int argc, char * argv[] ) {
	FILE * fp;

	printf("YADC compiler\n");

	//argument resolution
	if(	argc > 1 ) { //file passed
		strcpy(filePath, argv[1] );
		fp = fopen(filePath, "r");
		yyin = fp;
	} else {
		strcpy( filePath, "null.config");
	}
	if( argc > 2 ) {
		strcpy( workingDirectory, argv[2] );
	} else {
		strcpy( workingDirectory, "." );
	}
	if( argc > 3 ) {
		strcpy( projectName, argv[3] );
	} else {
		char temp[1024];
		strcpy( temp, filePath );
		strcpy( projectName, strtok( temp, "." ));
	}
	printf("%s %s %s\n", filePath, workingDirectory, projectName );
	//end; argument resolution

	tfb = PM_create(3);
	PM_manage( tfb, "title", STRING_TYPE, 1);
	PM_manage( tfb, "fields", LIST_TYPE, 1);
	PM_manage( tfb, "buttons", LIST_TYPE, 1);
	activePM = tfb;
	if( yyparse() ) { //first pass to the file break
		PM_destroy(tfb);
		PM_destroy(types);
		if(fp != NULL)
			fclose(fp);
		return 0;
	}

	Parameter * test = getParameter( tfb->param_ll, "buttons" );

	test = getParameter( tfb->param_ll, "fields" );

	//copy pasta straight from compile.c
	fieldCount = PL_reset( PM_getValue( tfb, "fields").list_val ); //PL_reset both resets the list and counts how many items there are
	buttonCount = PL_reset( PM_getValue( tfb, "buttons").list_val );

	types = PM_create(buttonCount+fieldCount); //PM large enough to accomodate what we expect

	//looping for fields, registering them
	cur_item = PM_getValue( tfb, "fields").list_val;
	for( i = 0; i < fieldCount; i++ ) {
		curChar = PL_next(cur_item);
		PM_manage( types, curChar, STRING_TYPE, 1 );
	}

	//looping for buttons, registering them
	cur_item = PM_getValue( tfb, "buttons").list_val;
	for( i = 0; i < buttonCount; i++ ) {
		curChar = PL_next(cur_item);
		PM_manage( types, curChar, STRING_TYPE, 1 );
	}
	//end pasta

	activePM = types;

	if( yyparse() ) { //second past after the file break

		PM_destroy(tfb);
		PM_destroy(types);
		if(fp != NULL)
			fclose(fp);
		return 0;
	}

	if ( !(checkRequired(types->param_ll))) {
		fputs("PARSE:PARSE ERROR**** Requried parameter(s) not found\n", stderr);
		PM_destroy(tfb);
		PM_destroy(types);
		if(fp != NULL)
			fclose(fp);
		return 0;
	}

	//moar copy pasta from compile.c
	PL_reset( PM_getValue( tfb, "buttons").list_val ); //lists are needed again
	PL_reset( PM_getValue( tfb, "fields").list_val );

	char curwd[1024]; //directory before writing
	getcwd( curwd, sizeof(curwd)); //get current directory
	chdir(workingDirectory); //change to project's working directory

	emitJava( tfb, types, fieldCount, buttonCount, (const char*)projectName ); //emit java

	chdir(curwd); //back to old directory
	//end moar pasta

	PM_destroy(tfb);
	PM_destroy(types);
	if(fp != NULL)
		fclose(fp);
	return 0;
}
