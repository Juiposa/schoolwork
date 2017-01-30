/*************************filename here.c***************************************************
Student Name: -------                        Student Number:  -------------
Date: -------------                          Course Name: ------------------
I have exclusive control over this submission via my password.
By including this statement in this header comment, I certify that:
     1) I have read and understood the University policy on academic integrity;
     2) I have completed the Computing with Integrity Tutorial on Moodle; and
     3) I have achieved at least 80% in the Computing with Integrity Self Test.
I assert that this work is my own. I have appropriately acknowledged any and all material
(data, images, ideas or words) that I have used, whether directly quoted or paraphrased.
Furthermore, I certify that this assignment was prepared by me specifically for this course.
********************************************************************************************/
/* rouge-like map generator and basic game
 * primary function of will be too draw the map of a rouge-like game from a structure input file
 * will also provide basic play functionality
 *
 * Authored by Jeffrey-David Kapp
 * Created 26 Feb 2014
 * Last Edited 9 Mar
*/

#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ncurses.h>
#include <ctype.h>


/*structure definition*/

/*structure that will store qualities of a defined room pulls from an input file*/
#ifndef ROOM_QUAL
 #define ROOM_QUAL

 typedef struct Room_Qualities {
 	int maxy; /*size of room by y*/
 	int maxx; /*size of room by x*/
 	int ** roomFloor; /*2D interger array to map the floor of the room*/
 	int playerX; /*player's position in X*/
 	int playerY; /*player's position in Y*/
 	int playerTF; /*whether the room has a player*/
 } RoomQual;

#endif

/*structure that will store the whole map once constructed from the readfile*/

#ifndef MAP_QUAL
 #define MAP_QUAL

 typedef struct Map_Qualities {
 	int maxy; /*maxy of the map*/
 	int maxx; /*maxx of the map*/
 	int ** MapFloor;
 	int playerX; /*player's position in X*/
 	int playerY; /*player's position in Y*/
 } MapQual;

#endif

/*structure that contains variables to be used for parsing*/
#ifndef PARSING_STRUCT
 #define PARSING_STRUCT

 typedef struct String_Component {
 	char * lineOfFile; /*line of the files being read in*/
 	char ** tokenString; /*two dimensional array of tokenised strings*/
 } StringComp;

#endif

/*room element constants from read file*/

#define DOOR 'd'
#define STAIRS 's'
#define GOLD 'g'
#define POTION 'p'
#define HERO 'h'
#define WEAPON 'w'
#define MONSTER 'm'

/*characters to be displayed for ingame elements*/

#define INGAME_DOOR '+'
#define INGAME_STAIRS '%'
#define INGAME_GOLD '*'
#define INGAME_POTION '!'
#define INGAME_HERO '@'
#define INGAME_WEAPON ')'
#define INGAME_MONSTER 'O'

#define SIDE_WALL '|'
#define TOP_WALL '_'
#define FLOOR '.'
#define HALL '#'


/*function prototypes*/


/* mapConstruction
 * Purpose: Will serve as the main function in the construction of the map;
 * will serve to pass and accept values to and from subsequent functions
 * Parameters: map - structure of the map to be passed to the play function
 * Returns: A completed structure with the map finalised
 * File: mapConstruction.c 
*/
MapQual * mapConstruction ( MapQual * map, FILE * readFile );

/* roomGen
 * Purpose: generate one room of the map from a file
 * Parameters: readFile; file to be read from 
 * Returns: complete room structure
 * File: roomGen.c 
*/
RoomQual * roomGen( FILE * readFile );

/* fileIO
 * Purpose: reading from the input file
 * Parameters: readFile; file to be read from
 * Returns: string from the readFile
 * File: roomGen.c
*/
char * fileIO( FILE * readFile, char * inStr );

/* parsing
 * Purpose: will use strtok to parse the input file line
 * Parameters: parsingStr; parsing struct
 * Returns: completed 2D array of tokenised strings
 * File: roomGen.c
*/
char ** parsing( StringComp * parsingStr );

/* nodeToken
 * Purpose: tokenise and already tokenised string :D, pulling coordinates out of room element parametres
 * Parameters: the node in question
 * Returns: array of the coordinates
 * File: roomGen.c
*/
int * nodeToken ( char * tokenString );

/* play
 * Purpose: carrying out the play of the built map
 * Parameters: the completed map
 * Returns: nothing
 * File: play.c
*/

void play( MapQual * map );

 /*print
 * Purpose: printing the map with rogue characters
 * Parameters: the completed map
 * Returns: nothing
 * File: play.c
*/

void print( MapQual * map );