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
#define INPUTFILE "test-packages.txt"
#define OUTPUTFILE "Output-packages.txt"

// Data Structures
typedef struct package {
	char *name;  // software package title – primary key
	char *version; // version
	char *level; // indicates license and level of support
	char *description;  // software description
} PACKAGE;

typedef struct hash {
	int buckets_used;
	PACKAGE *bucket[BUCKETSIZE];
} HASH;

typedef struct bstnode {
	PACKAGE *ptrPackage;
	struct node *left;
	struct node *right;
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
int insertPackage ( PACKAGE* );

// Hash Functions
void insertHash ( PACKAGE* package );
void hashSearch ( PACKAGE* package );
void listHash ( HEADER* listHeader );
void hashEff ( HEADER* listHeader );

//BST Functions
void insertTree ( PACKAGE* package );
void listTree ( HEADER* listHeader );
void printTree ( HEADER* listHeader );

// File I/O Functions
void writeFile ( HEADER* listHeader );
PACKAGE *allocatePackage( char *packageNameTemp, char *versionTemp, char* levelTemp, char *descriptionTemp);
int parseLine (char *line, char *packageNameTemp, char *versionTemp, char *levelTemp, char *descriptionTemp);

// Screen Output Functions
int printPackage ( PACKAGE *package );
int printFileOut (  );
void printUnsorted ( HEADER *listHeader );
void printSorted ( HEADER *listHeader );