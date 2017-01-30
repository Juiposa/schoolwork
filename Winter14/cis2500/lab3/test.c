#include "list.h"

int main()
{

	StdntRec * listhead = NULL;
	StdntRec * curnt = NULL; 

	char * firstName;
	char * lastName;
	char inputBuffer[100];
	char inputChar[100];
	int studentNumber = 0;
	float GPA;

	firstName = malloc(sizeof(char)*1024);
	lastName = malloc(sizeof(char)*1024);

	do {

		printf("(a) Enter new student record.\n(s) Print records.\n(q) Quit.\n\n");

		fgets(inputChar, 100, stdin);

		switch( inputChar[0] ) {

			case 'q': /*quitting*/
				printf("Quitting.\n");
				break;
			case 'a': /*input new record*/
				printf("Enter first name:\n");
				fgets( firstName, 1024, stdin );
				printf("Enter last name:\n");
				fgets( lastName, 1024, stdin );
				printf("Enter student number:\n");
				fgets( inputBuffer, 100, stdin );
				studentNumber = atoi(inputBuffer);
				printf("Enter GPA:\n");
				fgets( inputBuffer, 100, stdin );
				GPA = atof(inputBuffer);

				curnt = createRecord( firstName, lastName, studentNumber, GPA );
				listhead = addToFront( curnt, listhead );

				break;
			case 's': /*print list*/

				printList( listhead );

				break;
		}

	} while ( inputChar[0] != 'q');

	deleteList( listhead );

	free(firstName);
	free(lastName);

	return 0;

}