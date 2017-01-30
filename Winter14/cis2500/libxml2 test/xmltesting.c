#include <stdio.h>
#include <libxml/HTMLparser.h>
#include <libxml/HTMLtree.h>
#include <libxml/tree.h>
#include <libxml/parser.h>

htmlNodePtr recursion( htmlNodePtr org_node, int * count );

int main()
{

	htmlDocPtr doc;
	htmlNodePtr org_node = NULL;
	int count = 0;

	doc = htmlReadFile( "html.txt", NULL, 0 );
	org_node = xmlDocGetRootElement( doc );

	org_node = recursion( org_node, &count );

	printf("%s\n", org_node->content );

}

htmlNodePtr recursion( htmlNodePtr org_node, int * count )
{
	
	htmlNodePtr returnNode;
	htmlNodePtr curnt_node;

	for ( curnt_node = org_node; curnt_node != NULL; curnt_node = curnt_node->next ) {

		if ( curnt_node->type == XML_TEXT_NODE ) {

			*count = *count + 1;

			if ( *count == 4 ) {
				
				printf("%d \n", curnt_node->type );

				printf("%s \n", curnt_node->name );

				printf("%s \n\n", curnt_node->content );

				returnNode = curnt_node;

				return returnNode;

			}
			

		}

		returnNode = recursion( curnt_node->children, count ); /*calls itself*/

		if ( curnt_node == NULL ) { /*if it is null, return the previous step*/
			return NULL;
		}

		if ( returnNode != NULL ) { /*if the node has content, continue returning until parsing() is reached*/
			return returnNode;
		}

	}

}