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
#define MEM_ERR printf( "Not enough memory\n" ), exit(201)
#define BUCKETSIZE 3

// Data Structures
typedef struct package {
	char *packageName;  // software package title – primary key
	char *version; // version
	int level;  // 0 – Undefined, 1 - Main, 2 - Restricted, 3 - Universe, 4 – Multiverse ; indicates license and level of support
	char *description;  // software description
} PACKAGE;

typedef struct bucket {
	char* key;
	PACKAGE* ptrPackage;
} BUCKET;

typedef struct hash {
	int buckets_used;
	BUCKET bucket[BUCKETSIZE];
} HASH;

typedef struct bstnode {
	PACKAGE* ptrPackage;
	struct node* left;
	struct node* right;
} BSTNODE;

typedef struct header {
	int count;
	int hashArySize;
	int bucketSize;
	HASH *hashAry;
	BSTNODE *treeRoot;
} HEADER;

// Function Prototypes
// Driver functions
void printMenu( void );
void menuManager( HEADER* listHeader );
char getChar ( void );
void loadData ( HEADER* listHeader );
void addPackage ( HEADER* listHeader );
void deletePackage ( HEADER* listHeader );
HEADER* initHashBST ( void );

// Hash Functions
void insertHash ( void );
void hashSearch ( void );
void listHash ( void );
void hashEff ( void );

//BST Functions
void insertTree ( void );
void listTree ( void );
void printTree ( void );

// File I/O Functions
void writeFile ( void );
