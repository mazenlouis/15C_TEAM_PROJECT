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