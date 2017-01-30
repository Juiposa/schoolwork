/*************************roomGen.c**********************************************************
Student Name: Jeffrey-David Kapp             Student Number: 0832671       
Date: 14 March, 2014                         Course Name: CIS*2500           
I have exclusive control over this submission via my password.
By including this statement in this header comment, I certify that:
     1) I have read and understood the University policy on academic integrity;
     2) I have completed the Computing with Integrity Tutorial on Moodle; and
     3) I have achieved at least 80% in the Computing with Integrity Self Test.
I assert that this work is my own. I have appropriately acknowledged any and all material
(data, images, ideas or words) that I have used, whether directly quoted or paraphrased.
Furthermore, I certify that this assignment was prepared by me specifically for this course.
********************************************************************************************/

#include "rogue.h"

RoomQual * roomGen( FILE * readFile )
{

	int x = 0, y = 0, z = 0; /*counting variables*/

	int * nodecoor; /*room element xy*/

	char * tempStr; /*temporary operating string*/

	StringComp * parsingStr; /*structure to be used for parsing*/
	RoomQual * returnRoom; /*room structure*/

	/*memory allocation*/
	tempStr = malloc(sizeof(char)*1024);
	parsingStr = (StringComp *) malloc(sizeof(StringComp)); 
	returnRoom = (RoomQual *) malloc(sizeof(RoomQual));
	
	parsingStr->lineOfFile = malloc(sizeof(char)*1024);
	parsingStr->tokenString = malloc(sizeof(char *)*256);
	for ( x = 0; x <= 256; x++ ) { 
		parsingStr->tokenString[x] = malloc(sizeof(char)*256);
	}
	/*end memory allocation*/

	returnRoom->playerTF = 0; /*initialiation of variable*/

	parsingStr->lineOfFile = fileIO( readFile, parsingStr->lineOfFile ); /*will read in a line of the input file*/

	if (parsingStr->lineOfFile == NULL) { /*if the returned value is null*/
		return NULL; /*pass null back to the calling function*/
	}

	parsingStr->tokenString = parsing( parsingStr ); /*parsing the line of the file*/

	for( x = 0; parsingStr->tokenString[x] != NULL; x++ ) { /*master sorting loop, will loop until a null string is reached*/

		if ( x == 0 ) { /*first iteration, will be the dimensions of the room*/

			if ( !(isdigit(parsingStr->tokenString[x][0]))) { /*if the first character is not a digit*/
				return NULL; /*line of file will be skipped*/
			}

			tempStr = strtok(parsingStr->tokenString[x], "X"); /*get the first set of numbers*/
			returnRoom->maxy = atoi(tempStr)+1; /*put the dimension in the variable*/

			tempStr = strtok(NULL, "X"); /*get the second set of numbers*/
			if ( tempStr ==  NULL ) { /*if the returned number was null*/
				return NULL; /*return NULL, as the delimiter was incorrect or there were no numbers, line of file will be skipped*/
			}
			returnRoom->maxx = atoi(tempStr)+1; /*put the dimension in the variable*/

			/*memory allocation of the room map*/
			returnRoom->roomFloor = malloc(sizeof(int *)*(returnRoom->maxy)+1);
			for ( y = 0; y < returnRoom->maxy; y++ ) {
				returnRoom->roomFloor[y] = malloc(sizeof(int)*(returnRoom->maxx));
			}
			/*initialisation of the room*/
			for ( y = 0; y < returnRoom->maxy; y++ ) {
				for ( z = 0; z < returnRoom->maxx; z++ ) {

					if ( y == 0 || y == returnRoom->maxy-1 ) { /*if either at the top or bottom of the room*/
						returnRoom->roomFloor[y][z] = 1; /*top wall*/
					} else if ( z == 0 || z == returnRoom->maxx-1 ) { /*at the sides of the room*/
						returnRoom->roomFloor[y][z] = 2;
					} else { /*else just neutral floor*/
						returnRoom->roomFloor[y][z] = 0;	
					}

				}
			}
		}

		if ( x > 0 ) { /*all other tokens*/

			/*if statement will operate on the basis of the first character, which will indicate the type*/
			switch ( parsingStr->tokenString[x][0] ) {
				case DOOR:
					nodecoor = malloc(sizeof(int)*2);
					switch( parsingStr->tokenString[x][1] ) { /*check cardinal direction of door*/
						case 'n':
							nodecoor[0] = 0; /*set coordinate to a wall*/
							strtok( parsingStr->tokenString[x], "n" ); /*get the coordinate number*/
							nodecoor[1] = atoi(strtok(NULL, "n")); /*set second coor to that number*/
							break; 
						case 's':
							nodecoor[0] = returnRoom->maxy-1;	
							strtok( parsingStr->tokenString[x], "s" );
							nodecoor[1] = atoi(strtok(NULL, "s"));	
							break;
						case 'e':
							nodecoor[1] = returnRoom->maxx-1;				
							strtok( parsingStr->tokenString[x], "e" );
							nodecoor[0] = atoi(strtok(NULL, "e"));
							break;
						case 'w':
							nodecoor[1] = 0;
							strtok( parsingStr->tokenString[x], "w" );
							nodecoor[0] = atoi(strtok(NULL, "w"));
							break;
					}

					returnRoom->roomFloor[nodecoor[0]][nodecoor[1]] = 3;
					
					free(nodecoor);

					break;
				case STAIRS:
						nodecoor = nodeToken( parsingStr->tokenString[x] ); /*get coordinates*/
						returnRoom->roomFloor[nodecoor[0]][nodecoor[1]] = 4; /*change floor value to correct value*/
						free(nodecoor); /*free the memory*/
					break;
				case GOLD:
						nodecoor = nodeToken( parsingStr->tokenString[x] );
						returnRoom->roomFloor[nodecoor[0]][nodecoor[1]] = 5;
						free(nodecoor);
					break;
				case POTION:
						nodecoor = nodeToken( parsingStr->tokenString[x] );
						returnRoom->roomFloor[nodecoor[0]][nodecoor[1]] = 6;
						free(nodecoor);
					break;
				case HERO:
						nodecoor = nodeToken( parsingStr->tokenString[x] );
						returnRoom->roomFloor[nodecoor[0]][nodecoor[1]] = 7;
						returnRoom->playerY = nodecoor[0];
						returnRoom->playerX = nodecoor[1];
						returnRoom->playerTF = 1;
						free(nodecoor);
					break;
				case WEAPON:
						nodecoor = nodeToken( parsingStr->tokenString[x] );
						returnRoom->roomFloor[nodecoor[0]][nodecoor[1]] = 8;
						free(nodecoor);
					break;
				case MONSTER:
						nodecoor = nodeToken( parsingStr->tokenString[x] );
						returnRoom->roomFloor[nodecoor[0]][nodecoor[1]] = 9;
						free(nodecoor);
					break;
							
			}
		}
	}

	/*initscr();
	cbreak();
	noecho();

	for ( y = 0; y < returnRoom->maxy; y++ ) {
		for ( z = 0; z < returnRoom->maxx; z++ ) {
			mvprintw( y, z, "%d", returnRoom->roomFloor[y][z]);
			refresh();
		}
	}

	getch();
	refresh();
	endwin();*/

	tempStr = NULL;
	free(tempStr);
	free(parsingStr->lineOfFile);
	free(parsingStr->tokenString);
	free(parsingStr);

	return returnRoom;
	

}

char * fileIO( FILE * readFile, char * inStr )
{

	fgets( inStr, 256, readFile );

	if ( inStr == NULL ) { /*if at the end of the file return NULL*/
		return NULL;
	}

	return inStr;

}

char ** parsing( StringComp * parsingStr )
{

	int x = 0; /*counting variables*/

	parsingStr->tokenString[0] = strtok( parsingStr->lineOfFile, " " );

	do { /*loop while the returned vlue from strtok is not null*/

		x++; /*next spot in the 2D array*/
		parsingStr->tokenString[x] = strtok( NULL, " "); /*get next token*/

	} while ( !( parsingStr->tokenString[x] == NULL ) );

	return parsingStr->tokenString; /*returning the completed 2D array*/

}

int * nodeToken ( char * tokenString ) 
{
	char * tempStrng; /*tempstring; used with strtok*/
	int * xycoor; /*xy coor to be passed back*/

	int x = 0; /*couinting variables*/

	tempStrng = malloc(sizeof(char)*strlen(tokenString)+1);
	xycoor = malloc(sizeof(int)*2);

	for ( x = 1; x <= strlen(tokenString); x++ ) { /*copy the string expect for the element character to tempStr*/
		tempStrng[x-1] = tokenString[x];
	}

	xycoor[0] = atoi(strtok(tempStrng, ","));
	xycoor[1] = atoi(strtok(NULL, ","));

	free(tempStrng);

	return xycoor;
}