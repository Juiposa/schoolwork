/*************************main.c************************************************************
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

int main( int argc, char * argv[] )
{	
	/*variable declaration*/

	int x = 0;
	int y = 0; /*loop variables*/

	char exitVar; /*program exit variable*/

	MapQual * map; /*map structure*/
	FILE * readFile; /*file that will be read from for room dimensions and characteristics*/


	readFile = fopen( argv[1], "r" );


	/*ncurses initalisation*/

	initscr();
	cbreak();
	noecho();


	do {

		map = (MapQual *) malloc(sizeof(MapQual)); /*memory allocation*/

		map = mapConstruction( map, readFile ); /*constructing the map*/

		play( map );

		while ( y == 0 ) { /*exit function*/

			printf("Would you like to (r)estart or (q)uit?\n");
			exitVar = fgetc( stdin ); /*getting the exit char*/
			
			switch( exitVar ) { 
				case 'q':
					printf("Quiting.\n");
					x = 1; /*terminate master loop*/
					y = 1; /*terminate input loop*/
					break;
				case 'r': 
					printf("Restarting.\n");
					y = 1; /*terminate input loop*/
					break;
				default:
					printf("Invalid input, please only enter (r) or (q).\n");
					break;
			}

		}


	} while ( x == 0 );

	refresh();
	endwin();

	free(map);

	return 0;
	 
}