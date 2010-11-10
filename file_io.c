/* File IO Libary Functions */

// #includes
#include "main.h"



#define FILENAME "input.txt"

/*  ===================== loadData ======================
	This function reads the file and gathers the data into nodes
	to be placed into the BST and Hash Table.
		Pre: listHeader - empty header with pointers to a BST and Hash Table
		Post: listHeader - header with pointers to full BST and full Hash Table
*/
void loadData ( HEADER* listHeader )
{
		PACKAGE* tempPackage;
		FILE* fpIn;
		char packageNameTemp[99];
		char versionTemp[99];
		char descriptionTemp[99];
		int levelTemp;

		fpIn = fopen(FILENAME, "r");
		if(!fpIn)
			MEM_ERR;

		while() // loop that will read file line-by-line saving data into the above temp variables
		{
			tempPackage = (PACKAGE*) malloc (sizeof(PACKAGE));
			if(!tempPackage)
				MEM_ERR;

			tempPackage->description = (char*) malloc (sizeof (strlen (descriptionTemp) + 1 ));
			if(!tempPackage->description)
				MEM_ERR;

			tempPackage->packageName = (char*) malloc (sizeof (strlen (packageNameTemp) + 1 ));
			if(!tempPackage->packageName)
				MEM_ERR;

			tempPackage->version = (char*) malloc (sizeof (strlen (versionTemp) + 1 ));
			if(!tempPackage->version)
				MEM_ERR;

			strcpy(tempPackage->description, descriptionTemp);
			strcpy(tempPackage->packageName, packageNameTemp);
			strcpy(tempPackage->version, versionTemp);
			tempPackage->level = levelTemp;

			listHeader->count++;

			insertTree(tempPackage);
			insertHash(tempPackage);

		}

		return;
} // end loadData