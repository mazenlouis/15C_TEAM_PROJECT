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


/*	================= printEff ===================
	Calculates and prints efficiency of hash table
	   Pre    hash
	   Post   hash table efficiency printed
	   Return void
*/
void printEff ( HEADER* listHeader )
{
	// Local Definitions
	float loadFactor = 0.0;
	int longestBuckets = 0.0;
	int numberOfCollisions = 0;

	// Statements
	calcHashEff ( listHeader, &loadFactor, &longestBuckets, &numberOfCollisions );
	printf("Hash Efficiency\n");
	printf("=======================================\n");
	printf("Load Factor            :  %.2f\n", loadFactor);
	printf("Longest Bucket         :  %d\n", longestBuckets);
	printf("Number of Collisions   :  %d\n", numberOfCollisions);

	return;
} // printEff