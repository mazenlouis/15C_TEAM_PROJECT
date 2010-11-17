/* BST Libary Functions */

// #includes
#include "main.h"
#include "queueADT.h"

// Private Use Functions
static BSTNODE* _insert (HEADER* listHeader, BSTNODE* root, BSTNODE* newPackage);
static void _traverse (BSTNODE* root);
static void _traverseBFT (BSTNODE* root);

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
	if (comparePackage(root->ptrPackage, newPackage->ptrPackage) < 0)
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
void BST_Traverse (HEADER* listHeader) 
{
	if(listHeader->treeRoot)
		_traverse (listHeader->treeRoot);
	return;
} // end BST_Traverse 

/*	=================== _traverse =================== 
	Inorder tree traversal. To process a node, we use 
	the function passed when traversal was called.
	   Pre   Tree has been created (may be null) 
	   Post  All nodes processed 
*/
static void _traverse (BSTNODE* root) 
{
    if (root)
	{
        _traverse (root->left);
		printPackage ( root->ptrPackage );
        _traverse (root->right);
    }
    return;
}// _traverse

/*	=================== BST_Traverse_BFT =================== 
	Process tree using Breadth First traversal. 
	   Pre   Tree has been created (may be null) 
	         process visited packages during traversal 
	   Post  Package processed in Breadth First sequence 
*/
void BST_Traverse_BFT (HEADER* listHeader) 
{
	_traverseBFT (listHeader->treeRoot);
	return;
} // end BST_Traverse

/*	=================== _traverseBFT =================== 
	Breadth First tree traversal. To process a node, we use 
	the function printPackage.
	   Pre   Tree has been created (may be null) 
	   Post  All nodes processed 
*/
static void _traverseBFT (BSTNODE* root) 
{
    BSTNODE* currentNode;
	BSTNODE* tempNode;
	QUEUE* queue;

	queue = createQueue();
	if(!queue)
	{
		printf("\nMemory Overflow!\n");
		exit(201);
	}
	currentNode = root;

	while(currentNode != NULL)
	{
		printPackage ( root->ptrPackage );

		if(currentNode->left != NULL)
			enqueue(queue, currentNode->left);

		if(currentNode->right != NULL)
			enqueue(queue, currentNode->right);

		if(!emptyQueue(queue))
		{
				dequeue(queue, (void*)&tempNode);
				currentNode = tempNode;
		}
		else
			currentNode = NULL;
	}
	queue = destroyQueue(queue);	

	return;
}// _traverseBFT