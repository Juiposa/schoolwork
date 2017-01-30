/* clear
 * Purpose: will clear a portion of the screen as defined by the parameters
 * Parameters: 
 *              start: starting line to be cleared
 *				end: last line to be cleared
 * Returns: nothing
 */

#include "morsecode.h"

void clearScr( int start, int end )
{
    int y = 0;

    for ( y = start; y < end ; y++ ) { 
        mvprintw( y, 0, BLANKLINE );
    }
    
}