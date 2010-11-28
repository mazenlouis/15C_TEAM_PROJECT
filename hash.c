/* Hash Libary Functions */

// #includes
#include "main.h"


/* ============================ djb2HAsh =======================
	Hashes a string to an index int within range of listHeader->hashArySize
	Borrowed from http://www.cse.yorku.ca/~oz/hash.html
	   PRE  : listHeader - ptr to HEAEDER
			packageName - ptr to string
	   POST : 
	   RETURNS : returns int to index
*/
int djb2HAsh ( HEADER *listHeader, char *packageName )
{
	//	Local Definitions
	unsigned long hash = 5381;
	int c;

	//	Statements
	while (c = *packageName++)
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
	return hash % listHeader->hashArySize;
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
	int locn;
	int primes[168] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31,
					37, 41, 43, 47, 53, 59, 61, 67, 71, 73,
					79, 83, 89, 97, 101, 103, 107, 109, 113,
					127, 131, 137, 139, 149, 151, 157, 163,
					167, 173, 179, 181, 191, 193, 197, 199,
					211, 223, 227, 229, 233, 239, 241, 251,
					257, 263, 269, 271, 277, 281, 283, 293,
					307, 311, 313, 317, 331, 337, 347, 349,
					353, 359, 367, 373, 379, 383, 389, 397,
					401, 409, 419, 421, 431, 433, 439, 443,
					449, 457, 461, 463, 467, 479, 487, 491,
					499, 503, 509, 521, 523, 541, 547, 557,
					563, 569, 571, 577, 587, 593, 599, 601,
					607, 613, 617, 619, 631, 641, 643, 647,
					653, 659, 661, 673, 677, 683, 691, 701,
					709, 719, 727, 733, 739, 743, 751, 757,
					761, 769, 773, 787, 797, 809, 811, 821,
					823, 827, 829, 839, 853, 857, 859, 863,
					877, 881, 883, 887, 907, 911, 919, 929,
					937, 941, 947, 953, 967, 971, 977, 983,
					991, 997};

	//	Statements
	tableSize = size * 2; 
	
	binarySearch(primes, 168, tableSize, &locn);
	
	if (primes[locn] < tableSize)
	{
		locn++;
	}
	
	tableSize = primes[locn];

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
	listHeader->primaryBuckets = 0;
	return;
}

/* ============================ insertHash =======================
	inserts a package into a hash table with bucket collision
	   PRE  : listHeader - ptr to HEADER
			package - ptr to package to be inserted
	   POST : package is inserted or dropped
	   RETURNS : return 1 if success, 0 if fail
*/
int insertHash (HEADER* listHeader, PACKAGE* package)
{
	//	Local Definitions
	int index;
	int success = 0;

	//	Statements
	index =  djb2HAsh ( listHeader, package->name );
	if (loadFactor(listHeader) > HASH_MAX)
	{
		reHash(listHeader);
	}
	
	if (listHeader->hashAry[index].buckets_used < listHeader->bucketSize)
	{
		listHeader->hashAry[index].bucket[listHeader->hashAry[index].buckets_used] = package;
		if (!listHeader->hashAry[index].buckets_used)
		{
			listHeader->primaryBuckets++;
		}
		(listHeader->hashAry[index].buckets_used)++;
		success = 1;
	}
	return success;
}

/* ============================ deleteHash =======================
	deletes and frees a package from a hash table
	   PRE  : listHeader - ptr to HEADER
			packageName - ptr to name of package to be deleted
	   POST : package deleted
	   RETURNS : return 1 if success, 0 if fail
*/
int deleteHash (HEADER* listHeader, char *packageName)
{
	//	Local Definitions
	int index;
	int success = 0;
	int i = 0;
	
	//	Statements
	index =  djb2HAsh ( listHeader, packageName);
	
	while(i < listHeader->hashAry[index].buckets_used && !success)
	{
		if(strcmp( listHeader->hashAry[index].bucket[i]->name, packageName ) == 0 )
		{
			free (listHeader->hashAry[index].bucket[i]);
			while(i < listHeader->hashAry[index].buckets_used - 1)
			{
				listHeader->hashAry[index].bucket[i] = listHeader->hashAry[index].bucket[i + 1];
				i++;
			}
			listHeader->hashAry[index].bucket[i] = NULL;
			listHeader->hashAry[index].buckets_used--;
			success = 1;
		}
		i++;
	}
	return success;
}

/* ============================ hashSearch =======================
	
	   PRE  : listHeader - ptr to HEADER
			packageName - ptr to name of package to be deleted
	   POST : 
	   RETURNS : package if found
*/
PACKAGE* hashSearch (HEADER* listHeader, char *packageName)
{
	//	Local Definitions
	int index;
	int i = 0;
	
	//	Statements
	index =  djb2HAsh ( listHeader, packageName );

	while(i < listHeader->hashAry[index].buckets_used)
	{
		if(strcmp( listHeader->hashAry[index].bucket[i]->name, packageName ) == 0 );
			return listHeader->hashAry[index].bucket[i];
		i++;
	}
	

	return NULL;
}

/* ============================ listHash =======================
	Prints hash table
	   PRE  : listHeader - ptr to HEADER
	   POST : prints hash table
	   RETURNS : 
*/
void listHash ( HEADER* listHeader )
{
	//	Local Definitions
	int hashCt;
	int bktCt;
	
	//	Statements
	for (hashCt = 0; hashCt < listHeader->hashArySize; hashCt++)
	{
		for (bktCt = 0; bktCt < listHeader->hashAry[hashCt].buckets_used; bktCt++)
		{
			printf("%s\n", listHeader->hashAry[hashCt].bucket[bktCt]->name);
		}
	}
	return;
}

/* ============================ loadFactor =======================
	
	   PRE  : listHeader - ptr to HEADER
	   POST : 
	   RETURNS : load factor (primary buckets / size of hash table)
*/
float loadFactor ( HEADER* listHeader )
{
	//	Local Definitions
	//	Statements
	return ((float)listHeader->primaryBuckets/listHeader->hashArySize * 100);
}

/* ============================ reHash =======================
	
	   PRE  : listHeader - ptr to HEADER
	   POST : rehashes packages to new hash table. frees old table.
	   RETURNS : 
*/
void reHash ( HEADER* listHeader )
{
	//	Local Definitions
	HASH *tempAry;
	int size;
	int hashCt;
	int bktCt;
	
	//	Statements
	size = listHeader->hashArySize;
	tempAry = listHeader->hashAry;
	
	createHash(listHeader, size);
	
	for (hashCt = 0; hashCt < size; hashCt++)
	{
		if (tempAry[hashCt].buckets_used)
		{
			for (bktCt = 0; bktCt < tempAry[hashCt].buckets_used; bktCt++)
			{
				insertHash(listHeader, tempAry[hashCt].bucket[bktCt]);
			}
		}
	}

	free (tempAry);
	return;
}
/* ============================ destroyHash =======================
	
	   PRE  : listHeader - ptr to HEADER
	   POST : frees hash array
	   RETURNS : NULL
*/
HASH* destroyHash ( HEADER* listHeader )
{
	free ( listHeader->hashAry );
	return NULL;
}

/*	==================== binarySearch ====================
	Search an ordered list using Binary Search 
	   Pre   list must contain at least one element
	         size is the actual number of elements in the list
	         target is the value of element being sought
	   Post  FOUND: locn assigned index to target element 
	                return 1 (found)
	         NOT FOUND: locn = element below or above target 
	                    return 0 (not found)
*/
int binarySearch (int  list[],
                  int  size,
                  int  target, 
                  int *locn)
{
	int first;
	int mid;
	int last;

	first = 0;
	last = size - 1;
	while (first <= last)
	   {
	    mid = (first + last) / 2;
	    if (target > list[mid])       // look in upper half 
	       first = mid + 1;
	    else if (target < list[mid])  // look in lower half 
	       last = mid - 1;
	    else                          // found equal: force exit 
	       first = last + 1;
	   }
	*locn = mid;
	return target == list [mid];
}

/*	====================== calcHashEff ======================  
	Calculates the efficieny of a hash table
		Pre:	hash - ptr to hash table
		Post:	primePct - float ptr to Percentage of prime area filled
				avgLLnodes - float ptr to Avg nodes in linked lists
				longestLL - int ptr to longest link list
		Returns: void
*/
void calcHashEff( HEADER* listHeader, float *load, int *longestBuckets, int *numberOfCollisions )
{
	//	Local Definition
	int index;

	//	Statements
	*load =  0.0;
	*longestBuckets = *numberOfCollisions = 0;

	for(index = 0; index < listHeader->hashArySize; index++)
	{
		if(listHeader->hashAry[index].buckets_used > *longestBuckets)
			*longestBuckets = listHeader->hashAry[index].buckets_used;
		if(listHeader->hashAry[index].buckets_used > 1)
			(*numberOfCollisions)++;
	}
	
	*load = loadFactor ( listHeader );
	return;
} // calcHashEff