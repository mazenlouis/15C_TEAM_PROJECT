/* Screen Output Libary Functions */

// #includes
#include "main.h"

/*	=================== printPackage ===================================
	This function will print the contents of the package to the screen
		Pre:	root - package structure
		Post:	Printed to the screen
*/
void printPackage ( PACKAGE* ptrPackage )
{
	printf("%s %s %s %s\n", ptrPackage->name, ptrPackage->version, ptrPackage->level, ptrPackage->description);

	return;
} // printPackage


/*	======================= userPackage ===================================
	This function will prompt the user for a package to search for.
		Pre: nothing
		Post requested package to be searched for
*/
void userPackage (char* searchName )
{
	printf("What is the name of the package you would like to search for --> ");
	scanf(" %99[^\n]", searchName);
	FLUSH;
	
	return;
} // userPackage