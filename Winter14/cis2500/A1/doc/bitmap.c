#include <stdio.h>
#include <ncurses.h>


void main()
{

	int maxx = 100; 
	int maxy = 40;

	int mazeCells[100][40];

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

						mazeCells[y][x] = 0;
					
					} else {
					
						mazeCells[y][x] = 2;
					
					}

				} else {
					
					mazeCells[y][x] = 2;
				
				}

			} else { /*if the current cell is anywhere on the border*/

				mazeCells[y][x]= 2;

			}
		}
	}

	for ( y = 0; y <=maxy; y++ ) {

		for ( x = 0; x <= maxx; x++ ) {

			move( y, x );

			switch ( mazeCells[y][x] ) {
				case 0:
					addch(' ');
					break;
				case 1: /*if a blank space*/
					addch(' ');
					break;
				case 3:
					addch(' ');
					break;
				case 2: /*if a wall*/
					addch("#");
					break;
			}

			refresh();
		}
	}

	refresh(); 
}
