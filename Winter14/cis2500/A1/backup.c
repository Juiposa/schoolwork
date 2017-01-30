/*************************a1.c**************************************************************
Student Name: Jeffrey-David Kapp         Student Number:  0832671      
Date: 22 January 2014                        Course Name: CIS*2500          
I have exclusive control over this submission via my password.
By including this statement in this header comment, I certify that:
     1) I have read and understood the University policy on academic integrity;
     2) I have completed the Computing with Integrity Tutorial on Moodle; and
     3) I have achieved at least 80% in the Computing with Integrity Self Test.
I assert that this work is my own. I have appropriately acknowledged any and all material
(data, images, ideas or words) that I have used, whether directly quoted or paraphrased.
Furthermore, I certify that this assignment was prepared by me specifically for this course.
*******************************************************************************************/

#include <stdio.h>
#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define MAXSIZE 100
#define DEBUG 0

#define UP 'i'
#define DOWN 'k'
#define LEFT 'j'
#define RIGHT 'l'

#define PLAYER 'P'
#define EXIT 'X'
#define WALL ACS_CKBOARD



typedef struct mazeInformation { /*will store the maze's info, includin the player's name and the cell placement*/

	int mazeCells[MAXSIZE][MAXSIZE];
	char playerName[MAXSIZE];

} mazeInfo;

int mazeGeneration();

int recursionFunct( mazeInfo * mazeCells, int y, int x, int maxx, int maxy);

void fieldInitialisation(int maxx, int maxy, mazeInfo * mazeCells );

void play( mazeInfo * mazeCells );

int main(void)
{
	
	int x = 0, y = 0; /*loop variables*/

	int mazeGen_success = 0; /*returned value from mazeGeneration indicating the sucess of the mazeGeneration*/

	char exitVar; /*will store the user inputted response to the question of terminating the program or restarting*/

	srand( time(NULL) );
	
	/*ncurses initialisation*/
	initscr();
	cbreak();
	noecho();


	while ( x == 0 ) { /*master loop*/

		move( 0, 0 );
		refresh();

		printw("Welcome to a CIS*2500 maze adventure!\n");

		mazeGeneration();

		switch( mazeGen_success ) { /*handles if the user chose to exit during maze generation*/

			case 1: 
				printf(">>Maze successfully generated. Good luck.\n"); /*if the function terminates naturally*/
				break;
			case 2: 
				printf(">>Exiting.\n"); 
				x = 1; /*if the user chose to exit*/
				break;
		}
	
	} 

	refresh();

	endwin();

	return 0;

} 

/*will generate the maze for the user, and give an option to regenerate if the user does not like the size of the maze*/
int menu()
{

	int count = 0;

	int x = 0, y = 0, z = 1; /*loop variable*/

	int maxy = 0, maxx = 0; /*maxximum cooridinate values to be determined by the size of the user's window*/

	char inputchar = '\0'; /*character input for user comap*/

	printw("Please enter your name.\n");

	getstr( map.playerName );

	printw("Hello %s!\n", map.playerName );

	printw("Your maze will now generate.\n");
	

	printw("Please resize you window to the desired size.\n");
	printw("After doing so, please type 'y' when ready.\n");

	do { /*will loop while input is not 'y'*/
			
		inputchar = getch();
		
	} while ( inputchar != 'y' );

	

	getmaxyx( stdscr, maxy, maxx ); /*will get the window's maxximum dimensions*/

	refresh();

	do { /*will loop while window size is considered invalid*/

		/*if the window size is either too small (20) or too big (100), the program will prompt the user accordingly
		if too small, will ask user to make it bigger
		if too big, will prompt the user but then just size the maze to be smaller than the window*/

		if ( ( maxx > 100 || maxy > 100 ) || ( maxx < 20 || maxy < 20 ) ) { 

			if ( maxx > 100 ) { /*when the window is wider than 100*/

				printw("Your window is too wide, will default to 100 wide.\n");
				maxx = 100;
			}

			if ( maxy > 100 ) { /*when the window is taller than 100*/

				printw("Your window is too tall, will default to 100 tall.\n");
				maxy = 100;

			} 

			if ( maxx < 20 ) { /*when the window is narrower than 20*/

				printw("Your window is too narrow.\n");

			}

			if ( maxy < 20 ) { /*when the window is shorter*/

				printw("Your window is too short.\n");

			}

			if ( maxy < 20 || maxx < 20 ) {

				printw("Please resize the window to be at least 20x20. And then press y when ready.\n");

				do { /*will loop while input is not 'y'*/
			
					inputchar = getch();

				} while ( inputchar != 'y' );

				getmaxyx( stdscr, maxy, maxx ); /*will get the windows maxximum dimensions*/
				
			}
			
		} else { /*if the size of the window is considered acceptable*/

			z = 0; /* terminate the window sizing loop*/
		
		}

		refresh();

	} while ( z == 1 ); /*will loop while the window size is considered invalid*/

	fieldInitialisation( maxx, maxy, &map );  /*call to the map imitialisation function*/

	mvprintw( 2, 101, "Started\n");
	recursionFunct( &map, 1, 1, maxx, maxy);
	printw( 2, 101, "Finished\n");
	/*printing the maze*/

	refresh();

	for ( y = 0; y <=maxy; y++ ) {

		for ( x = 0; x <= maxx; x++ ) {

			move( y, x );

			switch ( map.mazeCells[y][x] ) {
				case 0:
					addch('0');
					break;
				case 1: /*if a blank space*/
					addch('1');
					break;
				case 3:
					addch('3');
					break;
				case 2: /*if a wall*/
					addch(WALL);
					break;
			}

			refresh();
		}
	}

	/*printing the maze*/

	

	refresh();

	play( &map );
	
	return 1;
}

/*initialise the field of play to be randomly generated into a maze
will include assign character values to cells
some cells will be walls by default to faciliate building a maze where characters will have to act as walls*/

void fieldInitialisation(int maxx, int maxy, mazeInfo * mazeCells  )
{

	int x = 0, y = 0; /*loop vars*/

	if ( !(maxx % 2) ) { /*will correct the maxx to the nearest odd number*/
  		maxx -= 1;
 	}

	if ( !(maxy % 2) ) { /*ditto, but for maxy*/
			maxy -= 1;
	}

	/*will assign initialise the maze map. 0 for void cells and 2 for walls*/
	/*both the maxx and maxy have to be odd to obtain a blank cell, all other will be set to be a wall*/
	/*note, this is simply initalisation for the maze generation, this will not be the final version of the maze*/

	for ( y = 0; y <= maxy; y++ ) { /*two dimensional loop through all elements in the maze*/
		
		for ( x = 0; x <= maxx; x++ ) {

			if ( !( y == 0 || y == maxy ) && !( x == 0 || x == maxx ) ) { /*if the current cell is not on the borders*/

				if ( y % 2 ) { /*if y is odd*/

					if ( x % 2 ) { /*if x is odd*/

						mazeCells->mazeCells[y][x] = 0;
					
					} else {
					
						mazeCells->mazeCells[y][x] = 2;
					
					}

				} else {
					
					mazeCells->mazeCells[y][x] = 2;
				
				}

			} else { /*if the current cell is anywhere on the border*/

				mazeCells->mazeCells[y][x]= 2;

			}
		}
	}

	move( 0 , 0);

	refresh(); 
}

void play( mazeInfo * mazeCells ) {

	char moveChar; /*direction that the player moves*/

	int y = 1, x = 1; /*cooridinates*/

	mvaddch( y, x, PLAYER );

	do { /*movement loop*/

		moveChar = getch();

		switch( moveChar ) {
			
			case UP:
				y -= 1;
				break;
			case DOWN:
				y += 1;
				break;
			case LEFT:
				x -= 1;
				break;
			case RIGHT:
				x += 1;
				break;
			case 'q':
				break;

		}

		if ( mazeCells->mazeCells[y][x] == 2 ) {
			move ( 0, 0 );
			printw("You cannot move there,\n");
		}

	} while ( moveChar != 'q' );


}

int recursionFunct( mazeInfo * mazeCells, int y, int x, int maxx, int maxy )
{

	int z = 0;

	int count = 0;
	int count2 = 0;

	int newy = 1, newx = 1; /*coordinates pointing to the new cell*/
	int wallx = 1, wally = 1; /*wall coordinates between cells*/ 
	int vistedDirections = 0; /*directions the maze could travel in that are not valid, as in they visited*/

	int expandedCells = 0; /*number of cells that will have to be expanded to, will control we to end the maze generation loop*/

	int direction = 0; /*randomised direction to expand the maze in*/

	do { /*master randomisation loop*/

		switch ( direction ) { /*will move focus to the cell adjacent in the direction chosen*/

			case 0: /*up*/
				newy = y - 2;
				wally = newy + 1;
				wallx = x;
				newx = x;
				break;
			case 1: /*down*/
				newy = y + 2;
				wally = newy - 1;
				wallx = x;
				newx = x;
				break;
			case 2: /*left*/
				newx = x - 2;
				wallx = newx + 1;
				wally = y;
				newy = y;
				break;
			case 3: /*right*/
				newx = x + 2;
				wallx = newx - 1;
				wally = y;
				newy = y;
				break;

		}

		printw("%d", direction);

		/*iff the adjacent cell we picked is not already in the maze*/

		refresh();

		if ( newy > 0 && newy < maxy && newx > 0 && newx < maxx ) {

			count++;
			/*mvprintw(0, 101, "Loopcheck1 %d %d\n", count, direction);*/


			if (  mazeCells->mazeCells[newy][newx] == 0  ) { 

				count2++;
				/*mvprintw( 1, 101, "Loopcheck2 %d\n", count2);*/

				mazeCells->mazeCells[newy][newx] = 1; /* we then add it to the maze*/
				mazeCells->mazeCells[wally][wallx] = 3; /*and we break the wall connecting the two cells, and add it to the maze as well*/
				vistedDirections++;
				
				z = recursionFunct( &mazeCells->mazeCells, newy, newx, maxx, maxy);

			}

			direction++;

		}/* else if ( ( mazeCells->mazeCells[newy][newx] == 1 ) ||  newy < 0 || newy > maxy || newx < 0 || newx > maxy ) {

			mvprintw(4, 101, "Nigger is false.\n");
			mvprintw(5, 101, "%d %d %d", newy, newx, direction);
			
			direction++;

		} */

		if ( direction >= 4 ) {
			z = 1;
		}

		


	} while( z == 0 );

	
	return 0;

}