/* 

  QUEUE Abstract Data Type - header file

*/


// Type Definitions 

typedef struct queueNode
{
    void             *dataPtr;
    struct queueNode *link;
} QUEUE_NODE;


typedef struct
{  
    int  count;
    QUEUE_NODE *front;
    QUEUE_NODE *rear;
} QUEUE;


// Prototype Declarations 

int    enqueue     ( QUEUE *queue, void * dataInPtr );
int    dequeue     ( QUEUE *queue, void **dataOutPtr );
int    queueFront  ( QUEUE *queue, void **dataOutPtr );
int    queueRear   ( QUEUE *queue, void **dataOutPtr );
QUEUE *createQueue ( void );
QUEUE *destroyQueue( QUEUE *queue );
int    emptyQueue  ( QUEUE *queue );
int    fullQueue   ( QUEUE *queue );
int    queueCount  ( QUEUE *queue );


