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
	
	listHead = initHashBST();

	menuManager( listHead );

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
		    case '1' : ;
				       break;
		    case '2' : ;
				       break;
		    case '3' : ;
				       break;
			case '4' : ;
				       break;
		    case '5' : ;
				       break;
			case '6' : ;
                       break;
			case '7' : ;
				       break;
			case '8' : ;
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
