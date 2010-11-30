/*
15C_TEAM_PROJECT - Team 6
main.c - main source

*/

// #includes
#include "main.h"

int main( void )
{
	// Local Definitions
	HEADER* listHead = NULL;

	// Statements
	printf("\n\n\t\t\t15C TEAM PROJECT\n\n");
	
	printf("Initializing...");
	listHead = initHashBST();
	printf("Loading Data...");
	loadData(listHead);
	printf("done\n");
	
	menuManager( listHead );

	startWriteFile ( listHead );

	listHead = destory( listHead );

    printf("\n");
	printf( _CrtDumpMemoryLeaks() ? "Memory Leak\n" : "No Leak\n");

	system("PAUSE");
	return 0;
}

/*	================= printMenu ===================
	Prints main menu
	   Pre    none
	   Post   Prints menu to stdout
	   Return void
*/
void printMenu( void )
{
	// Local Definitions
	// Statements
	printf("\n\t\t*************************************");
    printf("\n\t\t*                                   *");
	printf("\n\t\t*   1. Add new package              *");
	printf("\n\t\t*   2. Delete package               *");
	printf("\n\t\t*   3. Search Package by name       *");
	printf("\n\t\t*   4. List Packages (unsorted)     *");
	printf("\n\t\t*   5. List Packages (sorted)       *");
	printf("\n\t\t*   6. Print Tree                   *");
	printf("\n\t\t*   7. Write to file                *");
	printf("\n\t\t*   8. Calculate Efficiency         *");
	printf("\n\t\t*   9. Quit                         *");
	printf("\n\t\t*                                   *");
	printf("\n\t\t*************************************");
	return;
} // printMenu


/* ============================ menuManager =======================
	Process user's option by calling appropriate functions.
	   PRE  : 
	   POST : 
*/
void menuManager( HEADER* listHeader )
{
	// Local Definitions
	char option;

	// Statements
	printMenu ();
	do
	{
		option = getChar ();
	    option = toupper (option);
		switch(option)
		{
		    case '1' : menu_AddPackage (listHeader);
				       break;
		    case '2' : menu_DeletePackage (listHeader);
				       break;
		    case '3' : menu_Search (listHeader);
				       break;
			case '4' : menu_ListUnsorted (listHeader);
				       break;
		    case '5' : menu_ListSorted (listHeader);
				       break;
			case '6' : menu_PrintTree (listHeader);
                       break;
			case '7' : menu_WriteToFile (listHeader);
				       break;
			case '8' : menu_CalcEff (listHeader);
				       break;
			case '9' : printf("Closing program\n");
				       break;
			case 'M' : printMenu();
				       break;
            default  : printf("\n*** Invalid option! ***\n");
		               printf("Enter one of the following numbers: "
			                  "1, 2, 3, 4, 5, 6, 7, 8, 9: " );
					   break;
		} 
	} while (option != '9');
	return;
}  // menuManager

/* ============================ getChar =======================
	Gets char from user and returns it
	   PRE  : 
	   POST : 
	   RETURNS : option - char from user input
*/
char getChar ( void )
{
	// Local Definitions
	char option;

	// Statements
	printf ("\n\nPlease enter an option (M - for Menu): ");
	while (scanf ("%c", &option) == 0)
	{
		FLUSH;
		printf("Invalid Input. Please try again\n");
		printf("\n\nPlease enter an option (M - for Menu): ");
	}
	FLUSH;
	return option;
}  // getChar


/* ============================ initHashBST =======================
	Allocates a header and initializes default values
	   PRE  : 
	   POST : 
	   RETURNS : ptr to allocated header struct
*/
HEADER* initHashBST ( void )
{
	// Local Definitions
	HEADER* listHeader = NULL;
	
	// Statements
	if(!(listHeader = (HEADER*) malloc( sizeof(HEADER))))
		MEM_ERR;

	listHeader->count = 0;
	listHeader->bucketSize = BUCKETSIZE;
	listHeader->hashArySize = 0;

	listHeader->hashAry = NULL;
	listHeader->treeRoot = NULL;

	return listHeader;
}  // initHashBST

/* ============================ menu_AddPackage =======================
	Calls libary functions to add a package
	   PRE  : 
	   POST : 
	   RETURNS : 
*/
void menu_AddPackage ( HEADER* listHeader )
{
	char name[100];
	char version[100];
	char level[100];
	char description[100];
	PACKAGE* package;

	printf("Add new package...\n");
	printf("Enter name        : ");
	scanf(" %99[^\n]", name);
	FLUSH;
	printf("Enter version     : ");
	scanf(" %99[^\n]", version);
	FLUSH;
	printf("Enter level       : ");
	scanf(" %99[^\n]", level);
	FLUSH;
	printf("Enter description : ");
	scanf(" %99[^\n]", description);
	FLUSH;

	if(!(hashSearch ( listHeader, name)) )
	{
		package = allocatePackage( name, version, level, description );
		BST_Insert (listHeader, package); 
		insertHash (listHeader, package);
		(listHeader->count)++;
	}
	else printf("Discarding Non-Unique Package\n");
	return;
}

/* ============================ menu_DeletePackage =======================
	Calls libary functionsto delete a package
	   PRE  : 
	   POST : 
	   RETURNS : 
*/
void menu_DeletePackage ( HEADER* listHeader )
{
	char searchName[100];

	printf("Delete package...\n");
	userPackage(searchName);
	if(BST_Delete ( listHeader, searchName))
	{
		deleteHash (listHeader, searchName);
		printf("Deleted\n");
	}
	else printf("Not found\n");// delete hash
	return;
}

/* ============================ menu_Search =======================
	Calls libary functions to search a hash table for a package
	   PRE  : 
	   POST : 
	   RETURNS : 
*/
void menu_Search ( HEADER* listHeader )
{
	PACKAGE* found;
	char searchName[100];

	printf("Search...\n");

	userPackage(searchName);
	found = hashSearch(listHeader, searchName);
	if(!found)
		printf("Sorry the package %s was not found in the Table!\n", searchName);
	else
		printPackage(found);
	return;
}

/* ============================ menu_ListUnsorted =======================
	Calls libary functions to print the hash table which is unsorted
	   PRE  : 
	   POST : 
	   RETURNS : 
*/
void menu_ListUnsorted ( HEADER* listHeader )
{
	printf("List unsorted...\n");
	listHash ( listHeader , printPackage );
	return;
}

/* ============================ menu_ListSorted =======================
	Calls libary functions to print the binary search tree which is sorted
	   PRE  : 
	   POST : 
	   RETURNS : 
*/
void menu_ListSorted ( HEADER* listHeader )
{
	printf("List sorted...\n");
	BST_Traverse (listHeader, printPackage);
	return;
}

/* ============================ menu_PrintTree =======================
	Calls libary functions to print the BST in an indented format
	   PRE  : 
	   POST : 
	   RETURNS : 
*/
void menu_PrintTree ( HEADER* listHeader )
{
	printf("Print tree...\n");
	BST_Print (listHeader);
	return;
}

/* ============================ menu_WriteToFile =======================
	Calls libary functions to write the packages to a file
	   PRE  : 
	   POST : 
	   RETURNS : 
*/
void menu_WriteToFile ( HEADER* listHeader )
{
	startWriteFile ( listHeader );
	return;
}

/* ============================ menu_CalcEff =======================
	Calls libary functions to calculate and print hash table efficiency
	   PRE  : 
	   POST : 
	   RETURNS : 
*/
void menu_CalcEff ( HEADER* listHeader )
{
	printEff ( listHeader );
	return;
}

/* ============================ destory =======================
	Calls libary functions to free BST and hash array
	   PRE  : listHeader - ptr to HEADER
	   POST : frees all dynamic memory
	   RETURNS : NULL
*/
HEADER* destory ( HEADER* listHeader )
{
	listHeader->treeRoot = destroyBST ( listHeader ); // destroy BST
	listHeader->hashAry = destroyHash ( listHeader ); // destroy Hash
	free ( listHeader ); // destroy HEADER
	return NULL;
}