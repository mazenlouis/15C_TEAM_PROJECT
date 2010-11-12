/* File IO Libary Functions */

// #includes
#include "main.h"

/*  ===================== loadData ======================
	This function reads the file and gathers the data into nodes
	to be placed into the BST and Hash Table.
		Pre: listHeader - empty header with pointers to a BST and Hash Table
		Post: listHeader - header with pointers to full BST and full Hash Table
*/
void loadData ( HEADER* listHeader )
{
	PACKAGE* Package;
	FILE* fpIn;
	char line[300];
	char packageNameTemp[99];
	char versionTemp[99];
	char descriptionTemp[99];
	int levelTemp = 0;

	fpIn = fopen(INPUTFILE, "r");
	if(!fpIn)
		MEM_ERR;

	while(fgets( line, sizeof(line), fpIn )) // loop that will read file line-by-line saving data into the above temp variables
	{
		if( parseLine( line, packageNameTemp, versionTemp, levelTemp, descriptionTemp ))
		{
			//Package = allocatePackage(packageNameTemp, versionTemp, levelTemp, descriptionTemp);
			printf("%s\n", line);
			//insertTree(Package);
			//insertHash(Package);
		}
			
	}
	fclose(fpIn);
	return;
} // end loadData

PACKAGE *allocatePackage( char *packageNameTemp, char *versionTemp, int levelTemp, char *descriptionTemp)
{
	// local definitions
	PACKAGE *allocatedPackage = NULL;

	// statements
	allocatedPackage = (PACKAGE*) malloc (sizeof(PACKAGE));
	if(!allocatedPackage)
		MEM_ERR;

	allocatedPackage->packageName = (char*) calloc (strlen (packageNameTemp) + 1 , sizeof (char));
	if(!allocatedPackage->packageName)
		MEM_ERR;

	allocatedPackage->version = (char*) calloc (strlen (versionTemp) + 1 , sizeof (char));
	if(!allocatedPackage->version)
		MEM_ERR;

	allocatedPackage->description = (char*) calloc (strlen (descriptionTemp) + 1 , sizeof (char));
	if(!allocatedPackage->description)
		MEM_ERR;

	strcpy(allocatedPackage->packageName, packageNameTemp);
	strcpy(allocatedPackage->version, versionTemp);
	allocatedPackage->level = levelTemp;
	strcpy(allocatedPackage->description, descriptionTemp);
	
	return allocatedPackage;
}

int parseLine (char *line, char *packageNameTemp, char *versionTemp, int levelTemp, char *descriptionTemp)
{
	int success = 1;
	char tempLevel[99];
	sscanf( line, " %s %s %s %s", packageNameTemp, versionTemp, &tempLevel, descriptionTemp);
	printf("%s s% s% s%\n", packageNameTemp, versionTemp, tempLevel, descriptionTemp);
	return success;
}