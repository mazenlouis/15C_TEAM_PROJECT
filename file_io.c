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
	PACKAGE* package;
	FILE* fpIn;
	char line[300] = { '\0' };
	char packageNameTemp[100] = { '\0' };
	char versionTemp[100] = { '\0' };
	char levelTemp[100] = { '\0' };
	char descriptionTemp[300] = { '\0' };
	int size = 0;
	int tempC;

	fpIn = fopen(INPUTFILE, "r");
	if(!fpIn)
		MEM_ERR;
	
	while((tempC = fgetc(fpIn)) != EOF)
		if(tempC == '\n')
			size++;

	rewind(fpIn);
	createHash ( listHeader, size);
	while(fgets( line, sizeof(line), fpIn )) // loop that will read file line-by-line saving data into the above temp variables
	{
		if( parseLine( line, packageNameTemp, versionTemp, levelTemp, descriptionTemp ))
		{
			package = allocatePackage(packageNameTemp, versionTemp, levelTemp, descriptionTemp);
			BST_Insert (listHeader, package); // insert to Tree function goes here
			insertHash (listHeader, package);
			(listHeader->count)++;
		}	
	}
	fclose(fpIn);
	return;
} // end loadData

/*  ===================== allocatePackage ======================
	This function allocates a package and copies static strings to dynamic strings
		Pre:	packageNameTemp	- package name char ary
				versionTemp		- version char ary
				levelTemp		- level char ary
				descriptionTemp	- desciption char ary
		Post:	allocatedPackage - dynamic package ptr
		Return: returns a ptr to dynamic package struct
*/
PACKAGE *allocatePackage( char *packageNameTemp, char *versionTemp, char* levelTemp, char *descriptionTemp)
{
	// local definitions
	PACKAGE *allocatedPackage = NULL;

	// statements
	allocatedPackage = (PACKAGE*) malloc (sizeof(PACKAGE));
	if(!allocatedPackage)
		MEM_ERR;

	allocatedPackage->name = (char*) calloc (strlen (packageNameTemp) + 1 , sizeof (char));
	if(!allocatedPackage->name)
		MEM_ERR;

	allocatedPackage->version = (char*) calloc (strlen (versionTemp) + 1 , sizeof (char));
	if(!allocatedPackage->version)
		MEM_ERR;

	allocatedPackage->level = (char*) calloc (strlen (levelTemp) + 1 , sizeof (char));
	if(!allocatedPackage->level)
		MEM_ERR;

	allocatedPackage->description = (char*) calloc (strlen (descriptionTemp) + 1 , sizeof (char));
	if(!allocatedPackage->description)
		MEM_ERR;

	strcpy(allocatedPackage->name, packageNameTemp);
	strcpy(allocatedPackage->version, versionTemp);
	strcpy(allocatedPackage->level, levelTemp);
	strcpy(allocatedPackage->description, descriptionTemp);
	
	return allocatedPackage;
} // allocatePackage

/*  ===================== parseLine ======================
	This function takes a char string line from an ubuntu package
	repository list and parses it to individual strings.
		Pre:	line	- line to be parsed - char ary
		Post:	packageNameTemp	- package name char ary
				versionTemp		- version char ary
				levelTemp		- level char ary
				descriptionTemp	- desciption char ary
		Return:	returns 1 if successful, 0 if not
*/
int parseLine (char *line, char *packageNameTemp, char *versionTemp, char *levelTemp, char *descriptionTemp)
{
	// local definitions
	int success = 1;
	char tempString[300];
	
	// statements
	packageNameTemp[0] = versionTemp[0] = levelTemp[0] = descriptionTemp[0] = '\0';
	sscanf( line, "%99s %99s %299[^\n]", packageNameTemp, versionTemp, &tempString);
	if (tempString[0] == '[')
		sscanf( tempString, "%99s %299[^\n]", levelTemp, descriptionTemp);
	else
		strcpy(descriptionTemp, tempString);
	if (strcmp(packageNameTemp, "") == 0)
		success = 0;

	return success;
} // parseLine

/*  ==================== writeFile =============================
	This function will print the Binary Tree to an output file.
		Pre:	nothing
		Post:	Printed List of Packages to Output-packages.txt
		Return:	returns 1 if successful, 0 if not
*/

void	writeFile ( PACKAGE* ptrPackage )
{
	FILE* fpOut;

	fpOut = fopen( OUTPUTFILE, "a");
	if(!fpOut)
		printf("Sorry could not open the file \"%s\"...", OUTPUTFILE);

	fprintf(fpOut, "%s %s %s %s\n", ptrPackage->name, ptrPackage->version, ptrPackage->level, ptrPackage->description);

	fclose(fpOut);

	return;
} // writeFile