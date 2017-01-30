/* help
 * Purpose: will print help and instructions to the user
 * Parameters: 
 *              maxy: maximum y value of the window   
 *				maxx: maximum x value of the window
 * Returns: nothing
 */
 
#include "morsecode.h"

void help( maxy, maxx )
{
    mvprintw( maxy - 4, 0, "Please enter '-quit' if you wish to exit.");
    mvprintw( maxy - 3, 0, "For morsecode input, please only enter '.', '-' or ' '.");
    mvprintw( maxy - 2, 0, "Place two spaces between words written in morsecode.");
}