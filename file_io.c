/* File IO Libary Functions */

// #includes
#include "main.h"



#define FILENAME "input.txt"

/*  ===================== getData ======================
	This function reads the file and gathers the data into nodes
	to be placed into the BST and Hash Table.
		Pre: list - empty list
			 listName - empty list
		Post: list - BST of nodes about students by pin
		      listName - BST of nodes about student by name
*/
void loadData ( HEADER* listHeader )
{
		PACKAGE* tempPack;
		FILE* fpIn;
		char* packageNameTemp;
		char* versionTemp;
		char* descriptionTemp;
		int levelTemp;

		fpIn = fopen(FILENAME, "r");


		tempPack = createPackage();

		return;
} // end getData