#include <proto_header.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * QUEUE ADT API - The operations described in the functions below describe a fixed length Queue - also referred to
 * as a Bounded Queue. The Bounded Queue is limited to a maximum of 'n' items (fixed number/maximum amount of items). 
 * It cannot be resized. * 
 * The QUEUE ADT in this case is implemented using a Singly Linked List as the underlying data structure.
 * Single Linked List - The singly linked list is a collection of nodes defined by self referencing structs. 
 * One node is connected to the next node in the singly linked list by the use of a pointer. The first node created 
 * represents the head of the singly linked list - it also defines the front of the queue. 
 * The queue has two impotant pointers:
 * 1. A pointer to the front of the queue (aka pointer to the head/head pointer).
 * 2. A pointer to the end of the queue (aka pointer to the tail of the queue/tail pointer). 
 * 
 * When a new node is added to the singly linked list, the node is added to the end of the linked list. 
 * This represents the enqueue operation - a new element is added to the end of the queue. 
 * When an element is removed from the queue this is a dequeue operation. When a dequeue operation is called, 
 * the element at the front of the queue is removed. 
 * (In real life when the person at the front of a queue leaves each person in the queue has to move forward one
 * position. Each person is now one position closer to the front of the queue.)
 * 
 * NOTE: In the QUEUE ADT movement is figurative not literal. In reality movements within the queue from a dequeue
 * operation, or the addition of an element to the queue from an enqueue operation are enacted by changing which 
 * node is pointed to by the head pointer and which node is pointed to by the tail pointer respectively. 
 * 
 * A queue is a FIFO (First In First Out) data structure. It is also a LILO (Last In Last Out) data structure:
 
 * NOTE: This Bounded Queue is implemented as a Circular Queue - the last element in the queue is connected to the 
 * first element in the queue by a pointer which results in a circular structure. 
 * 
 * The functions described below emulate the operations of the Queue ADT API. 
 * Helper functions should not be included in this Queue API file - write any additional helper functions 
 * in a separate C program file. 
 * 
 * Reference: Data Structures Handook - Data Structures at your fingertips 
 * Queues. (n.d.). Data Structures Handbook. https://www.thedshandbook.com/queues/
 */


/**
 * Precondition: queue_init() has not previously been invoked in the application instance
 * Postcondition: Memory for a queue_t ADT has been allocated and the length attribute
 *                for the queue has been initialised. The number of elements in the queue is 0.
 * \param queue_length is the maximum number of elements that the bounded queue/circular queue
 *               may contain.  
 * \returns a pointer the the bounded queue/circular queue.
 */
queue_t *queue_init(int max_queue_length) {
  queue_t *bounded_queue = malloc(sizeof(queue_t));
  bounded_queue->curr_length = 0;
  bounded_queue->capacity = max_queue_length;
  return bounded_queue;
}


/**
 * Precondition: queue_init() has been invoked to create an empty queue.
 * Postcondition: Queue is no longer present/available to the application and all allocated memory
 * has been deallocated.
 * Function to remove the queue and all the associated nodes that made up the queue ADT. Any memory
 * allocated to the queue ADT is freed. 
 * \param queue - A pointer to the queue that was dynamically allocated when the queue was created. 
 * 
 */
void destroy_queue(queue_t *queue) {
    node_t *node = queue->front_pos;
    node_t *tmp;

    do { 
      tmp=node;
      node=node->next;
      free(tmp);      
    } while(node!=queue->front_pos);
}

/**
 * Precondition: queue_init() has been invoked to create the queue ADT. The queue must contain
 * at least one element for the function to be called. queue->front_pos != NULL
 * Postcondition: The element/node pointed to by the head pointer (the front of the queue) is no longer
 * part of the queue. The head pointer will point to the next node in the queue which can be defined as
 * the node pointed to by dequeued_node->next. The node defined as dequeued_node->next is now the first 
 * element/node in the queue. The number of elements/nodes stored in the queue is decremented by 1.
 * \param queue - A pointer to the queue ADT returned from invoking queue_init() to create the queue_t ADT
 * \returns the node at the front of the queue if there is at least one node/element in the queue. If the
 *          queue is empty then API will exit with a status of -1. The function should not be invoked on an
 *          empty queue.
 */
node_t *dequeue(queue_t *queue) {
  if (queue->curr_length==0) {
    fprintf(stderr, "\nUnable to dequeue from an empty queue. The queue must contain at least one element to perform a dequeue\n");
    exit(EXIT_FAILURE);
  }
  node_t *dq_node = queue->front_pos;
  
  if (queue->curr_length==1) {
    queue->front_pos=NULL;
    queue->end_pos=NULL;
  } else {
    queue->front_pos = queue->front_pos->next;
  }     
  queue->curr_length--;
  return dq_node;
}

bool check_buffer_capacity(queue_t *queue) {
  return true;
}

void enqueue(queue_t *queue, node_t *new_node)
{
  queue->curr_length++;  
  new_node->next = queue->front_pos;

 
  /* First into queue*/
  if (queue->curr_length==1) {
    queue->front_pos = new_node;
    queue->end_pos = new_node;
  } else {   
    queue->end_pos->next = new_node; 
    queue->end_pos = new_node;
    
  }
  new_node->next = queue->front_pos;
}

/* node_data_t *peek(queue_t *queue) {

}

bool isFull(queue_t *queue) {

}

bool isEmpty(queue_t *queue) {

} */