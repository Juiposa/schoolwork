
#include "morsecode.h"

int main()
{
    char * message; /*message to be sent by the user*/
    char * result; /*HTML to be received back*/
    xmlChar * output; /*parsed string to be output to the user*/

    FILE * outfile; /*file that the users inputs and the outputs will be stored in*/

    int maxx = 0, maxy = 0; /*maxsizes of the users window*/
    int y = 0, x = 0; /*coordinate values for printing*/

    char exitVar = '\0'; /*variable to handles terminating the loop*/

    message = malloc( sizeof(char) * 200 ); /*string with a max size of 200*/
    output = malloc( sizeof(char) * 1000 ); /*string with a maz size of 1000*/

    /*ncurses initalisation*/
    initscr();
    noecho();
    cbreak();

    do { /*master loop*/

        getmaxyx( stdscr, maxy, maxx ); /*getting the window dimensions*/

        clearScr( 0, maxy ); /*clearing the screen*/

        y = ( maxy - 10 ) / 2; /*middle of the screen shifted up a bit*/
        x = ( ( maxx / 2 ) - ( strlen(INSTRUCTIONS) / 2 ) ); /*middle of the screen and offset so the message will be centred*/

        /*printing instructions to the user*/
        mvprintw( y, x, INSTRUCTIONS );
        mvprintw( y + 2, x, PLSENTR );

        refresh();

        message = messageInput( x, y, maxy, maxx ); /*getting the message to be translated*/


        if ( message != NULL ) { /*will only execute if messageInput reached its natural end, i.e. not exited out of*/

            result = makeCurlCall( URL, message ); /*making the curl post*/

            outfile = fopen ( "html.txt", "w" ); /*open file to be parsed from and saving the result*/
            fprintf( outfile, "%s", result);
            fclose(outfile); 

            free(result); /*this string is no longer needed*/

            output = parsing(); /*parsing the return from the website*/

            /*output of parsed string to the user*/
            mvprintw( y + 6, x, "Translated text: ");
            mvprintw( y + 7, x, "%s", output);

            refresh();


            /*will print the users message and the output to a text file for future reference*/
            outfile = fopen( "outfile.txt", "a" );
            fprintf(outfile, "Message: %s\nResult: %s\n", message, output );
            fclose(outfile);

        }   


        mvprintw( 0, 0, "Would you like to (q)uit or (r)estart?");

        refresh();
        
        exitVar = getch();

    } while ( exitVar != 'q' );

    free( message );
    free( output );

    return 0;
}