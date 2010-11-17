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

/*	======================= searchMgr ===================================
	This is a driver function to search the Hash Table.
		Pre: listHeader - header structure with the pointer to the Hash Table
		Post printed package to screen if found
			 print error message if not found
*/
void searchMgr ( HEADER *listHeader )
{
	PACKAGE* found;
	char searchName[100];

	userPackage(searchName);
	// found = Hash_Search(listHeader, searchName);
	if(!found)
		printf("Sorry the package %s was not found in the Table!\n", searchName);
	else
		printPackage(found);

	return;
} // searchMgr

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