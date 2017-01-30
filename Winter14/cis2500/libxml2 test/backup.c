#include <stdio.h>
#include <libxml/HTMLparser.h>
#include <libxml/HTMLtree.h>
#include <libxml/tree.h>
#include <libxml/parser.h>

int main()
{

	htmlDocPtr doc;
	htmlNodePtr org_node = NULL;
	htmlNodePtr curnt_node = NULL;
	htmlNodePtr curnt2_node = NULL;

	doc = htmlReadFile( "html.txt", NULL, 0 );

	for ( curnt_node = org_node; curnt_node != NULL; curnt_node = curnt_node->children ) {


		for ( curnt2_node = curnt_node; curnt2_node; curnt2_node = curnt2_node->parent ) {

			printf("%d %d\n", curnt_node->type, curnt2_node->type );

			printf("%s %s\n", curnt_node->name, curnt2_node->name );

		/*if ( curnt_node->type == XML_TEXT_NODE ) {*/
		
			printf ("%s %s\n\n", curnt_node->content, curnt2_node->content );
		
		}
		

	}

	org_node = xmlDocGetRootElement( doc );


}

int recursion( htmlNodePtr org_node )
{
	
	int returnVal = 0;
	htmlNodePtr curnt_node;

	for ( curnt_node = org_node; curnt_node != NULL; curnt_node = curnt_node->children ) {

		printf("%d %d\n", curnt_node->type );

		printf("%s %s\n", curnt_node->name );

		returnVal = recursion( curnt_node ); /*calls itself*/

		if ( curnt_node == NULL ) { /*if it is null, return the previous step*/-
			return 0;
		}

		switch ( returnVal ) {
			case 0:
				curnt_node == curnt_node->next; /*if returned, change to the next node*/
				break;
			}

	}



}