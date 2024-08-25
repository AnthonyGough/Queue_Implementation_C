#include <proto_header.h>
#include <stdbool.h>
/**
 * QUEUE ADT API - The operations described in the functions below describe a fixed length Queue - also referred to
 * as a Bounded Queue. The Bounded Queue is limited to 'n' items (fixed number/maximum amount of items). It cannot be resized.
 * 
 * The QUEUE ADT in this case is implemented using a Singly Linked List as the underlying data structure.
 * Single Linked List - The singly linked list is a collection of nodes defined by self referencing structs. 
 * One node is connected to the next node in the singly linked list by the use of a pointer. The first node created 
 * represents the head of the singly linked list - it also defines the front of the queue. 
 * The queue has two impotant pointers:
 * 1. A pointer to the front of the queue (aka pointer to the head/head pointer).
 * 2. A pointer to the end of the queue (aka pointer to the tail of the queue/tail pointer). 
 * 
 * When a new node is added to the singly linked list, the node is added to the end of the linked list. 
 * This represents the enqueue operation - a new element is added and it is added to  the end of the queue. 
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
 
 * NOTE: This Queue is implemented as a Bounded Queue:- there is only room for 'n' elements in the queue. 
 * Once 'n' elements have been added to the queue no more can be added until a dequeue operation is executed. 
 * A Bounded Queue can be also described as a Circular Queue - the last element in the queue is connected to the 
 * first element in the queue which results in a circular structure. 
 * 
 * The functions described below emulate the operations of the Queue ADT API. Only implement these functions.
 * Helper functions should not be included in this Queue API file - write any additional helper functions 
 * in a separate C program file. 
 * 
 * Reference: Data Structures Handook - Data Structures at your fingertips 
 * Queues. (n.d.). Data Structures Handbook. https://www.thedshandbook.com/queues/
 */

‌


void destroy_queue(queue_t *queue) {
    node_t *node = queue->front_pos;
    node_t *tmp;

    while (node) {
      tmp=node;
      node=node->next;
      free(tmp);      
    }
}

node_t *dequeue(queue_t *queue) {
  node_t *front;
  if (queue->length>0) {
    queue->length--;
    front=queue->front_pos;
    if (queue->length>1) {
        queue->front_pos = queue->front_pos->next;
      } else {
        queue->front_pos=NULL;
        queue->end_pos=NULL;
      } 
  }
  return front;
}


void enqueue(queue_t *queue, node_data_t *node_data)
{
  queue->length++;
  node_t *new_node = malloc(sizeof(node_t));
  new_node->value = node_data->value;
  new_node->arrival = node_data->arrival;
  strcpy(new_node->node_desc, node_data->node_desc);
  new_node->next = NULL;
 
  /* First into queue*/
  if (queue->length==1) {
    queue->front_pos = new_node;
    queue->end_pos = new_node;
  } else {
    queue->end_pos->next = new_node;
    queue->end_pos = new_node;
  }
}

node_data_t *peek(queue_t *queue) {

}

bool isFull(queue_t *queue) {

}

bool isEmpty(queue_t *queue) {
    
}