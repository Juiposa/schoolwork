/* messageInput
 * Purpose: will take the users input of the message they wish to send, as well as double in echoing the input
 *          to the ncurses screen in a neat manner
 * Parameters: 
 *              x: x postion as determined in main()
 *              y: y    "      "       "         "
 *              maxy: maximum y value of the user's window at the program's start
 *              message: pointer to the message to be passed to the website 
 * Returns: will return a integer indicating the sucess of the message input and will tell main how to proceed
 */

 #include "morsecode.h"

char * messageInput ( int x, int y, int maxy, int maxx )
{
    char * tempMessage; /*temporary variable, will be copied to message once user input is finalised*/
    char * returnMessage;

    char inputChar = '\0'; /*character input*/
    
    int i = 0;

    tempMessage = malloc( sizeof(char) * 200 );
    returnMessage = malloc( sizeof(char) * 215);

    do {

        getstr( tempMessage );

        if ( strcmp(tempMessage, "-quit") == 0 ) { /*if the user chooses to quit input*/ 

            mvprintw(0, 0, "Are you sure you want leave input (q)?");
            refresh();
            inputChar = getch();

            if ( inputChar == 'q' ) { 
                return NULL; /*return accordingly*/
            }

        } else if ( strcmp(tempMessage, "-help") == 0) { /*print help function if the request it*/

            help( maxy, maxx );



        } else { /*if niether of these special inputs are present*/

            refresh();

            strcpy( returnMessage, "message=" );

            strcat( returnMessage, tempMessage ); /*concatenate the completed input string to the message var*/
            i = 1; /*terminate the loop*/

        }

    } while ( i == 0 );

    return returnMessage;
}