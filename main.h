/*
15C_TEAM_PROJECT - Team 6
main.h - main header

*/

// #includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <crtdbg.h>



 


// #defines
#define FLUSH while (getchar () != '\n')

// Data Structures
typedef struct package {
	char *packageName;  // software package title – primary key
	char *version; // version
	int level;  // 0 – Undefined, 1 - Main, 2 - Restricted, 3 - Universe, 4 – Multiverse ; indicates license and level of support
	char *description;  // software description
} PACKAGE;

typedef struct header {
	int count;
	int arySize;
	// pHash
	// pTree
	int bucketSize;
} HEADER;


// Function Prototypes

