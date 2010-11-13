/* Screen Output Libary Functions */

// #includes
#include "main.h"

/*  ===================== printPackage ======================
	This function prints a package to stdout
		Pre:	package - ptr to PACKAGE struct
		Post:	package printed to stdout
		Return:	returns 1 if successful, 0 if not
*/
int printPackage ( PACKAGE *package )
{
	if(package)
	{
		printf("\nName       : %s", package->name);
		printf("\nVersion    : %s", package->version);
		printf("\nLevel      : %s", package->level);
		printf("\nDescription: %s", package->description);
		return 1;
	}
	return 0;
} // printPackage

/*	=================== printUnsorted ===================================
	This function will print the contents of the BST unsorted to the screen
		Pre:	listHeader - header structure with pointers to BST/Hash
		Post:	Printed unsorted BST to screen	
*/
void printUnsorted ( HEADER *listHeader )
{
	// inorder traversal of BST, printing contents at each Node.
	// call BST_Traversal, then at each node call printPackage

	return;
} // printUnsorted

/*	=================== printSorted ===================================
	This function will print the contents of the BST sorted by name to the screen
		Pre:	listHeader - header structure with pointers to BST/Hash
		Post:	Printed sorted BST to screen	
*/
void printSorted ( HEADER *listHeader )
{
	// Breadth-First traversal of BST, printing contents at each Node.
	// call BST_Traversal_BFT, then at each node call printPackage

	return;
} // printSorted