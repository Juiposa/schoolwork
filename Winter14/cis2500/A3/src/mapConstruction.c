/*************************napConstruction.c***************************************************
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

MapQual * mapConstruction( MapQual * map, FILE * readFile )
{

	RoomQual * roomToBeAdded; /*room returned from function to be added to the map*/

	int x = 0, y = 0, z = 0; /*counting variables*/
	int roomspanx = 3, roomspany = 3; /*the distance the rooms are currently spanning*/

	getmaxyx( stdscr, map->maxy, map->maxx ); /*getting screen size*/

	/*memory allocation of the map floor*/
	map->MapFloor = malloc(sizeof(int *)*(map->maxy));
	for ( y = 0; y <= map->maxy; y++ ) {
		map->MapFloor[y] = malloc(sizeof(int)*(map->maxx));
	}

	for ( y = 0; y <= map->maxy; y++ ) {
		for ( z = 0; z <= map->maxx; z++ ) {
			map->MapFloor[y][z] = -1;
		}
	}

	for ( x = 0; x < 6; x++ ) { /*construction loop, will terminate once six rooms have been added*/

		roomToBeAdded = roomGen( readFile ); /*callinf the room generation fucntion*/

		if (roomToBeAdded->playerTF == 1) { /*if there is a player in the room*/
			map->playerY = roomToBeAdded->playerY+roomspany; /*tranfer the coor to the map struct*/
			map->playerX = roomToBeAdded->playerX+roomspanx;	
		}

		for ( y = 0; y < roomToBeAdded->maxy; y++ ) { /*copying room to the map*/
			for ( z = 0; z < roomToBeAdded->maxx; z++ ) {

				map->MapFloor[roomspany+y][roomspanx+z] = roomToBeAdded->roomFloor[y][z];	
			}
		}
		/*adjusting the room spans*/
		roomspanx += (roomToBeAdded->maxx + 3);

		if ( x == 2 ) { /*third iteration, new line*/
			roomspany = 28;
			roomspanx = 3;
		}

		free(roomToBeAdded);
	}

	return map; 
}