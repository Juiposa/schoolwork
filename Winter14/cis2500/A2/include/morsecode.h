/*************************morsecode.h*******************************************************
Student Name: Jeffrey-David Kapp             Student Number:  0832671      
Date: 7 Feburary, 2014                       Course Name: CIS*2500            
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
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <libxml/HTMLparser.h>
#include <libxml/HTMLtree.h>
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <curl/curl.h>

#define URL "http://morse.socs.uoguelph.ca/cgi-bin/morse.pl"
#define MSG "message="
#define PLSENTR "Please enter a message: "
#define INSTRUCTIONS "Type '-help' to get detailed instructions."
#define BLANKLINE "                                                                                                                                          "

char * messageInput ( int x, int y, int maxy, int maxx );

xmlChar * parsing( );

htmlNodePtr recursion( htmlNodePtr org_node, int * count );

void help( int maxx, int maxy );

void clearScr( int start, int end );

/*cURL_util functions and structure*/

typedef struct BufferData {
	char* string;
	size_t length;
} BufferData;

char* makeCurlCall(char* url, char* parameters);

size_t processPost(void* stream, size_t size, size_t numberOfMembers, BufferData* buffer);

CURL* initializeCurlCall(char* url, char* parameters, BufferData* buffer);


