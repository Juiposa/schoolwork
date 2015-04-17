/* Jeffrey-David Kapp
 * 0832671
 * Assignment 1
 * CIS3110
 * 30 Jan 2015
*/

#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>


//gets the number of arguments in a character array
int argc_get( char ** args );

//majority chunk of program
//will handle decision structres for executing and piping
//returns 1 on success, 0 otherwise
int execute( char ** args );

//checks if command is one of three local commands and runs them if so
int localCmd( char ** args );

//added decimal and hexadecimal numbers
void LCadd( char ** args);

//coutning and reoutputing arguments
void LCarg( char ** args );

//our shell's own working cd command
void LCcd( char ** args );