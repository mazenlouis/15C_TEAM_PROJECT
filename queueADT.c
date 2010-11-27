/*
   QUEUE Abstract Data Type - function definitions:

           . createQueue
           . enqueue
           . dequeue
           . queueFront
           . queueRear
           . destroyQueue
           . emptyQueue
           . fullQueue
           . queueCount

*/

#include <stdio.h>
#include <stdlib.h>

#include "queueADT.h"

/* ======================== createQueue ======================== */
/* Allocates memory for a queue head node.
   Pre   : Nothing
   Post  : Head has been allocated and initialized
   Return: pointer to the queue head
           -or- NULL in case of overflow
*/

QUEUE *createQueue ( void )
{
    QUEUE *queue;

    queue = ( QUEUE *) malloc( sizeof( QUEUE ) );
    if( queue ) 
    {
        queue->front  = NULL;
        queue->rear   = NULL;
        queue->count  = 0;
    }

    return queue;

}// createQueue 

/* ======================== enqueue ======================== */
/* This function inserts data into a queue.
   Pre   : queue - a pointer to the queue header
           dataPtr - pointer to the data to be inserted
   Return: -  1 if success; 
           -  0 if heap overflow
*/
int enqueue( QUEUE *queue, void * dataInPtr )
{
    QUEUE_NODE *newPtr;
    int         success = 0;

    newPtr = ( QUEUE_NODE *) malloc( sizeof( QUEUE_NODE ) );
    if( newPtr != NULL ) 
    {
        success = 1;
    
        newPtr->dataPtr = dataInPtr;
        newPtr->link    = NULL;
      
        if( queue->front == NULL )        // insert to an empty queue 
            queue->front = newPtr;
        else
            queue->rear->link = newPtr;
      
        (queue->count)++;
        queue->rear = newPtr;
    }

    return success;

}// enqueue 

/* ======================== dequeue ======================== */
/* This function deletes one node from the queue.
   Pre   : queue - a pointer to the queue header
   Return: -  a pointer to user data if success; 
           -  NULL if the queue is empty
*/
int dequeue( QUEUE *queue, void **dataOutPtr )
{
    QUEUE_NODE *pDel;
    int         success = 0;

    if( queue->count != 0 )
    {
        success = 1;

        *dataOutPtr = queue->front->dataPtr;
        pDel = queue->front;

        if( queue->count == 1 )
           queue->rear = queue->front = NULL;
        else
          queue->front = queue->front->link;

        ( queue->count )--;
        free( pDel );
        
    }

    return success;

}// dequeue 


/* ======================== queueFront ======================== */
/* This function retrieves the data at the front of the queue
   without changing the queue contents.
   Pre   : queue - a pointer to the queue header
   Post  : dataOutPtr passed back to caller 
   Return: - 1 if success; 
           - 0 if the queue is empty(underflow)
*/
int queueFront( QUEUE *queue, void **dataOutPtr )
{
    int success = 0;

    if( queue->front != NULL )
    {
        success = 1;
        *dataOutPtr = queue->front->dataPtr;
    }

    return success;

}// queueFront

/* ======================== queueRear ======================== */
/* This function retrieves the data at the end of the queue
   without changing the queue contents.
   Pre   : queue - a pointer to the queue header
   Post  : dataOutPtr passed back to caller 
   Return: - 1 if success; 
           - 0 if the queue is empty(underflow)
*/
int queueRear( QUEUE *queue, void **dataOutPtr )
{
    int success = 0;

    if( queue->rear != NULL )
    {
        success = 1;
        *dataOutPtr = queue->rear->dataPtr;
    }

    return success;

}// queueRear 

/* ======================== destroyQueue ======================== */
/* This function releases all nodes to the heap
   Pre   : queue - a pointer to the queue header
   Return: - NULL
*/
QUEUE *destroyQueue( QUEUE *queue )
{
    QUEUE_NODE *pDel;

    if( queue )
    {
        while( queue->front != NULL )
        {
            free( queue->front->dataPtr );
            pDel = queue->front;
            queue->front = queue->front->link;
            free( pDel );
        }

        free( queue );
    }

    return NULL;

}// destroyQueue 

/* ======================== emptyQueue ======================== */
/* This function checks to see if a queue is empty
   Pre   : queue - a pointer to the queue header
   Return: true if empty, false if queue has data
*/
int emptyQueue( QUEUE *queue )
{
    
    return queue->count == 0;

}// emptyQueue 

/* ======================== fullQueue ======================== */
/* This function checks to see if a queue is full. The queue is
   full if memory cannot be allocated for another node.
   Pre     queue - a pointer to the queue header
   Return: true if full, false if room for another node.
*/
int fullQueue( QUEUE *queue )
{
    QUEUE_NODE *temptr;
    int         success = 1; 

    temptr = (QUEUE_NODE *) malloc(sizeof(QUEUE_NODE));
    if( temptr )
    {
        success = 0; // not full 
        free(temptr);
    }

    return success;

}// fullQueue 

/* ======================== queueCount ======================== */
/* This function returns the number of elements in the queue
   Pre   : queue - a pointer to the queue header
   Return: the number of elements in the queue
*/
int queueCount( QUEUE *queue )
{
    
    return queue->count;

}// queueCount 

