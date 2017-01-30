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
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define MAXSIZE 100

#define UP 'i'
#define DOWN 'k'
#define LEFT 'j'
#define RIGHT 'l'

#define PLAYER 'P'
#define EXIT 'X'
#define WALL ACS_CKBOARD


int menu();

void printMaze( int mazeMap[20][60] );

void play( int mazeMap[20][60] );

int main()
{
	
	int x = 0; /*loop variables*/

	char exitVar = '\0'; /*will store the user inputted response to the question of terminating the program or restarting*/
	
	/*ncurses initialisation*/
	initscr();
	cbreak();
	noecho();


	while ( x == 0 ) { /*master loop*/

		move( 0, 0 );
		refresh();

		printw("Welcome to a CIS*2500 maze adventure!\n");

		menu();

		mvprintw( 22, 0, "Would you like to e(x)it or (r)estart?\n");

		do {
			exitVar = getch();
		} while ( exitVar != 'x' && exitVar != 'r');

		switch( exitVar ) { /*handles exit process*/

			case 'r': 
				mvprintw( 0, 0, "Restarting. Have fun agian.\n"); /*if the function terminates naturally*/
				break;
			case 'x': 
				mvprintw( 0, 0, "Exiting.\n"); 
				x = 1; /*if the user chose to exit*/
				break;
		}
	
	} 

	refresh();

	endwin();

	return 0;

} 

/*will get the user's name and trigger later functions*/
int menu()
{

	int mazeMap[21][60] = {
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,0},
		{0,1,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
		{0,1,0,1,1,1,1,1,1,1,1,1,0,1,0,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0},
		{0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0},
		{0,1,0,1,0,1,0,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1,1,1,1,0,1,0,1,1,1,1,1,0},
		{0,1,1,1,1,1,1,1,1,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,1,0,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,0,0,0,0,0,0,1,0,1,0,0,0,1,0},
		{0,1,0,1,0,1,0,0,0,0,1,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,0,1,0,1,0,0,0,0,0,1,0,1,0,0,0,1,0,1,1,1,1,1,1,0,1,0,0,0,1,0,1,0},
		{0,0,0,1,0,1,0,1,0,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,1,1,1,1,0,1,1,1,1,1,0,1,0,1,0,1,0,0,1,1,1,1,1,1,1,0},
		{0,1,1,1,0,1,0,1,1,1,1,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,1,0,1,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
		{0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,0,1,0,1,1,1,1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,0,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0},
		{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,1,1,1,1,1,1,0,1,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0},
		{0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,0},
		{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,1,0},
		{0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,1,0,1,1,1,0,1,0},
		{0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,0,1,0,0,0,1,0,1,0,1,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,0},
		{0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,1,0,0,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,1,1,1,1,1,1,2,0},
		{0,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	};

	char playerName[MAXSIZE]; /*user's name*/

	printw("Please enter your name.\n");

	getstr( playerName );

	mvprintw(22, 0, "Hello %s!\n", playerName );

	refresh();

	printMaze( mazeMap );

	play( mazeMap );

	return 0;

}
/*will print the map basedd of the mapped array*/
void printMaze( int mazeMap[21][60] )
{

	int x = 0, y = 0; /*loop variables*/

	for ( y = 0; y <=21; y++ ) {

		for ( x = 0; x <= 60; x++ ) {

			move( y, x );

			switch ( mazeMap[y][x] ) {
				case 2:
					addch(EXIT);
					break;
				case 1:
					addch(' ');
					break;
				case 0: /*if a wall*/
					addch(WALL);
					break;
			}

			refresh();
		}
	}

}

void play( int mazeMap[21][60] ) 
{

	char moveChar; /*direction that the player moves*/

	int y = 1, x = 1; /*cooridinates*/
	int newy = 1, newx = 1; /*provisional coordiantes to check for move validity*/

	do { /*movement loop*/
		
		mvaddch( y, x, PLAYER );

		moveChar = getch();

		switch( moveChar ) {
			
			case UP:
				newy -= 1;
				break;
			case DOWN:
				newy += 1;
				break;
			case LEFT:
				newx -= 1;
				break;
			case RIGHT:
				newx += 1;
				break;
			case 'q':
				break;

		}

		if ( mazeMap[newy][newx] == 0 ) {
			mvprintw( 22, 0, "You cannot move there.\n");

			newy = y;
			newx = x;

		} else if ( mazeMap[newy][newx] == 1 ) {
			mvprintw( 22, 0, "                                                                                         ");
			mvaddch( y, x, ' ');
			y = newy;
			x = newx;
		} else if ( mazeMap[newy][newx] == 2) {
			mvprintw( 22, 0, "You win!\n");
			moveChar = 'q';

		}

	} while ( moveChar != 'q' );

}


	




