/* Hash Libary Functions */

// #includes
#include "main.h"

/* ============================ hashKey =======================
	Hashes a string to an index int within range of listHeader->hashArySize
	   PRE  : listHeader - ptr to HEAEDER
			packageName - ptr to string
	   POST : 
	   RETURNS : returns int to index
*/
int hashKey ( HEADER *listHeader, char *packageName )
{
	//	Local Definitions
	int index = 0;
	int i = 0;

	//	Statements
	while ( packageName[i] != '\0' )
	{
		index = index + packageName[i];
		i++;
	}
	return index % listHeader->hashArySize;
}

/* ============================ createHash =======================
	Creates a hash table (size *2)-> next prime number and sets all
	buckets NULL and buckets_used to 0
	   PRE  : listHeader - ptr to HEAEDER
			size - number of packages to be loaded into hash table
	   POST : table allocated and initialized
	   RETURNS : 
*/
void createHash ( HEADER* listHeader, int size )
{
	//	Local Definitions
	int tableSize;
	int i, j;

	//	Statements
	tableSize = size * 2; 
	//make tableSize = to next prime number here

	listHeader->hashAry = (HASH*) calloc (tableSize , sizeof (HASH));
	if(!listHeader->hashAry)
		MEM_ERR;
	for (i = 0; i < size; i++)
	{
		listHeader->hashAry[i].buckets_used = 0;
		for (j = 0; j < listHeader->bucketSize; j++)
			listHeader->hashAry[i].bucket[j] = NULL;
	}
	listHeader->hashArySize = tableSize;
	return;
}

/* ============================ insertHash =======================
	inserts a package into a hash table with bucket collision
	   PRE  : listHeader - ptr to HEADER
			package - ptr to package to be inserted
	   POST : package is inserted or dropped
	   RETURNS : return 1 is success, 0 if fail
*/
int insertHash (HEADER* listHeader, PACKAGE* package)
{
	//	Local Definitions
	int index;
	int success = 0;
	//	Statements
	index =  hashKey ( listHeader, package->name );
	if (listHeader->hashAry[index].buckets_used < listHeader->bucketSize)
	{
		listHeader->hashAry[index].bucket[listHeader->hashAry[index].buckets_used] = package;
		(listHeader->hashAry[index].buckets_used)++;
		success = 1;
	}

	return success;
}

/* ============================ deleteHash =======================
	
	   PRE  : 
	   POST : 
	   RETURNS : 
*/
void deleteHash (HEADER* listHeader, char *packageName)
{
	//	Local Definitions
	//	Statements
	return;
}

/* ============================ hashSearch =======================
	
	   PRE  : 
	   POST : 
	   RETURNS : 
*/
PACKAGE* hashSearch (HEADER* listHeader, char *packageName)
{
	//	Local Definitions
	int index;
	int i = 0;
	
	//	Statements
	index =  hashKey ( listHeader, packageName );

	while(i < listHeader->hashAry[index].buckets_used)
	{
		if(strcmp( listHeader->hashAry[index].bucket[i]->name, packageName ) == 0 );
			return listHeader->hashAry[index].bucket[i];
		i++;
	}
	

	return NULL;
}

/* ============================ listHash =======================
	
	   PRE  : 
	   POST : 
	   RETURNS : 
*/
void listHash ( HEADER* listHeader )
{
	//	Local Definitions
	//	Statements
	return;
}

/* ============================ hashEff =======================
	
	   PRE  : 
	   POST : 
	   RETURNS : 
*/
void hashEff ( HEADER* listHeader )
{
	//	Local Definitions
	//	Statements
	return;
}

/* ============================ reHash =======================
	
	   PRE  : 
	   POST : 
	   RETURNS : 
*/
void reHash ( HEADER* listHeader )
{
	//	Local Definitions
	//	Statements
	return;
}