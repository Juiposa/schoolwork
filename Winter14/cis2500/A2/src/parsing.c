/* parsing
 * Purpose: will use xml parsing library to parse the webpage received back from the curl call.               
 * Parameters: none
 * Returns: will return the parsed string
 */

 #include "morsecode.h"

xmlChar * parsing ()
{
	htmlDocPtr doc; /*document to be parsed*/
	htmlNodePtr org_node = NULL; /*original node*/

	int count = 0;

	doc = htmlReadFile( "html.txt", NULL, 0 ); /*builds the node tree from the document*/
	org_node = xmlDocGetRootElement( doc ); /*gets the original node*/

	org_node = recursion( org_node, &count ); /*calls the recursive function*/
 

	return org_node->content;

}

/* recursion
 * Purpose: recursive function to search the created node tree for the required node
 * Parameters:
 *				org_node: the first node of the html text
 *				count: count of the number of text areas encountered
 * Returns: the node with the required string
 */

htmlNodePtr recursion( htmlNodePtr org_node, int * count )
{
	
	htmlNodePtr returnNode; /*node to be returned*/
	htmlNodePtr curnt_node; /*operating node for the loop*/

	/*will loop as long as there is a node to travel to*/
	for ( curnt_node = org_node; curnt_node != NULL; curnt_node = curnt_node->next ) {

		/*if the node is a text node*/
		if ( curnt_node->type == XML_TEXT_NODE ) {

			*count = *count + 1; /*count an encountered text box*/

			if ( *count == 4 ) { /*once we get to four, weve reached the desired text*/
				
				returnNode = curnt_node; /*return that node*/

				return returnNode;

			}
			
		}

		returnNode = recursion( curnt_node->children, count ); /*calls itself*/

		if ( curnt_node == NULL ) { /*if the current node is null, return the previous step*/
			return NULL;
		}

		if ( returnNode != NULL ) { /*if the node has content, continue returning until parsing() is reached*/
			return returnNode;
		}

	}

	return NULL;

}