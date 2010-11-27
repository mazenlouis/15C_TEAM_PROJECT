/* BST Libary Functions */

// #includes
#include "main.h"

// Private Use Functions
static BSTNODE* _insert (HEADER* listHeader, BSTNODE* root, BSTNODE* newPackage);
static void _traverse (BSTNODE* root, void (*process) (PACKAGE* package) );
void _print (BSTNODE *root, int   level);

/*	====================== comparePackage======================  
	Compare two package name's and return low, equal, high.
	    Pre  pack1 and pack2 are valid pointers to packages
	    Post return low (-1), equal (0), or high (+1)
*/
int  comparePackage   (PACKAGE* pack1, PACKAGE* pack2)
{
//	Local Definitions 
	int compared;

//	Statements 
	compared = strcmp(pack1->name, pack2->name);
	if ( compared < 0)
	      return -1;
	     
	if ( compared == 0)
	      return 0;

	return +1;
}	//end comparePackage

/*	================= BSTNODE_Create ===================
	This function creates a new BSTNODE to be inserted.
	   Pre    nothing
	   Post   newNode
	   Return Success (true) or Overflow (false)
*/
BSTNODE* BSTNODE_Create ( )
{
	BSTNODE* newNode;

	newNode = (BSTNODE*) malloc(sizeof(BSTNODE));
	if(!newNode)
		MEM_ERR;

	newNode->left = NULL;
	newNode->ptrPackage = NULL;
	newNode->right = NULL;

	return newNode;
} // BSTNODE_Create

/*	================= BST_Insert ===================
	This function inserts new packages into the tree.
	   Pre    listHedaer - header containing pointer to BST
	   Post   package inserted or memory overflow 
	   Return Success (true) or Overflow (false)
*/
int BST_Insert (HEADER* listHeader, PACKAGE* package)
{
	BSTNODE* newNode;

	newNode = BSTNODE_Create();
	newNode->ptrPackage = package;

	if (listHeader->treeRoot == NULL)
		listHeader->treeRoot = newNode;

	else
		_insert(listHeader, listHeader->treeRoot, newNode);
	    
	return 1;
}// BST_Insert 

/*	==================== _insert ====================
	This function uses recursion to insert the new data 
	into a leaf node in the BST tree.
	   Pre    Application has called BST_Insert, which  
	          passes root and data pointer
	   Post   Data have been inserted
	   Return pointer to [potentially] new root
*/
static BSTNODE* _insert (HEADER* listHeader, BSTNODE* root, BSTNODE* newPackage)
{
	if(!root)
		return newPackage;

	// Locate null subtree for insertion 
	if (comparePackage(root->ptrPackage, newPackage->ptrPackage) > 0)
	{
		root->left = _insert(listHeader, root->left, newPackage);
	    return root; 
	}     // new < node
	else
	{ // new data >= root data 		  
	    root->right = _insert(listHeader, root->right, newPackage);
	    return root;
	} // else new data >= root data 


	return root;
}// _insert


/*	=================== BST_Traverse =================== 
	Process tree using inorder traversal. 
	   Pre   Tree has been created (may be null) 
	         process visited package during traversal 
	   Post  Pacakge processed in LNR (inorder) sequence 
*/
void BST_Traverse (HEADER* listHeader, void (*process) (PACKAGE* package) ) 
{
	if(listHeader->treeRoot)
		_traverse (listHeader->treeRoot, process);
	return;
} // end BST_Traverse 

/*	=================== _traverse =================== 
	Inorder tree traversal. To process a node, we use 
	the function passed when traversal was called.
	   Pre   Tree has been created (may be null) 
	   Post  All nodes processed 
*/
static void _traverse (BSTNODE* root, void (*process) (PACKAGE* package)) 
{
    if (root)
	{
		_traverse (root->left, process);
		process ( root->ptrPackage );
        _traverse (root->right, process);
		
        
    }
    return;
}// _traverse

/*  ============================= BST_Print ============================= 
	This function prints the BST tree by calling a recursive inorder 
	traversal.
		Pre:	Tree must be initialized. Null tree is OK.
				Level is node level: root == 0
		Post:	Tree has been printed.
*/
void BST_Print (HEADER* listHeader) 
{
	_print (listHeader->treeRoot, 0);
    return;
}   // AVL_PRINT 

/*  ============================= _print ============================= 
	This function uses recursion to print the tree. At each level, the 
    level number is printed along with the node contents.
    Pre		root is the root of a tree or subtree
            level is the level of the tree: tree root is 0
    Post    Tree has been printed.
*/
void _print (BSTNODE *root, int   level) 
{
 	int i;
 	
  	if ( root )
 	{
		_print ( root->right, level + 1 );
		for (i = 0; i <= level; i++ )
 			printf (" " );
		printf( "%d: %s\n", level, root->ptrPackage->name  );
		_print ( root->left, level + 1 );
 	} 

	return;
 } 

/*	=================== BST_Count ==================
	Returns number of nodes in tree.
	   Pre     tree has been created 
	   Returns tree count 
*/
int BST_Count (HEADER* listHeader)
{
	return (listHeader->count);
}// BST_Count 