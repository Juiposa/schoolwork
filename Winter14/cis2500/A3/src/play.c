/*************************play.c************************************************************
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

void play( MapQual * map )
{

	char inputChar; /*user's input keypress*/
	int x = 0, y = 0; /*coordinate variables*/
	int i = 0, j = 0; /*counting variable*/
	int newy = 1, newx = 1; /*provisional coordiantes to check for move validity*/

	y = map->playerY;
	x = map->playerX;

	print(map); /*will print the map*/

	do { /*movement loop*/
		
		mvaddch( y, x, INGAME_HERO );

		inputChar = getch();

		switch( inputChar ) {
			
			case 'w':
				newy -= 1;
				break;
			case 's':
				newy += 1;
				break;
			case 'a':
				newx -= 1;
				break;
			case 'd':
				newx += 1;
				break;
			case 'q':
				break;

		}

		if (!( map->MapFloor[newy][newx] == 0 || map->MapFloor[newy][newx] == 3 )) { /*if the next spot is anything other than a door or floor*/

			mvprintw( 0, 0, "You cannot move there.\n" );
			newy = y;
			newx = x;

		} else { /*regular floor*/

			mvprintw( 0, 0, " 										\n");
			mvaddch( y, x, FLOOR);

			y = newy;
			x = newx;

		}

		if ( map->MapFloor[newy][newx] == 3 ) { /*encountering a door*/

			if ( map->MapFloor[y][newx+1] == -1 ) { /*if moving left or right*/
				
				if ( newx < x ) { /*moving left*/
					for ( i = -1; map->MapFloor[y][newx+i] == -1; i-- ) {
						
						if ( map->MapFloor[y+j][newx+i] != -1 ) { /*if no longer in the void*/
							for ( j = -25; map->MapFloor[y+j][newx+i] != 3 || j != 25; j++ ) { /*search wall for a door*/
							} /*loop until j points to a door*/
							y += j;
							x = newx+i;
						}

					}
				} else if ( newx > x ){ /*moving right*/
					for ( i = 1; map->MapFloor[y][newx+i] == -1; i++ ) {
						
						if ( map->MapFloor[y][newx+i] != -1 ) { /*if no longer in the void*/
							for ( j = -25; map->MapFloor[y+j][newx] != 3 || j != 25; j++ ) { /*search wall for a door*/
							} /*loop until j points to a door*/
							y += j;
							x = newx+i;
						}
					}
				}

			} else if ( map->MapFloor[newy+1][x] == -1 ) { /*else if moving up or down*/

				if ( newy < y ) { /*moving up*/
					for ( i = -1; map->MapFloor[newy+i][x] == -1; i-- ) {
							
						if ( map->MapFloor[newy+i][x] != -1 ) { /*if no longer in the void*/
							for ( j = -25; map->MapFloor[newy+i][x+j] != 3 || j != 25; j++ ) { /*search wall for a door*/
							} /*loop until j points to a door*/
							x += j;
							y = newy+i;
						}

					}

				} else if ( newy > y ) { /*moving down*/ 
					for ( i = 1; map->MapFloor[newy+i][x] == -1; i++) {
							
						if ( map->MapFloor[newy+i][x] != -1 ) { /*if no longer in the void*/
							for ( j = -25; map->MapFloor[newy+i][x+j] != 3 || j != 25; j++ ) { /*search wall for a door*/
							} /*loop until j points to a door*/
							x += j;
							y = newy+i;
						}

					}

				}
			}

		}

	} while ( inputChar != 'q' );

	free(map);

	return;

}

void print ( MapQual * map )
{
	int x = 0, y = 0; /*counting variables*/

	for ( y = 0; y < map->maxy; y++ ) {
		for ( x = 0; x < map->maxx; x++ ) {
			switch ( map->MapFloor[y][x] ) {
				case 0:
					mvaddch( y, x, FLOOR );
					break;
				case 1:
					mvaddch( y, x, TOP_WALL); 
					break;
				case 2:
					mvaddch( y, x, SIDE_WALL);
					break;
				case 3:
					mvaddch( y, x, INGAME_DOOR);
					break;
				case 4:
					mvaddch( y, x, INGAME_STAIRS);
					break;
				case 5:
					mvaddch( y, x, INGAME_GOLD);
					break;
				case 6:
					mvaddch( y, x, INGAME_POTION);
					break;
				case 7:
					mvaddch( y, x, INGAME_HERO);
					break;
				case 8:
					mvaddch( y, x, INGAME_WEAPON);
					break;
				case 9:
					mvaddch( y, x, INGAME_MONSTER);
					break;
				case -1:
					mvaddch( y, x, ' ');
					break;
			}
		}
	}
}