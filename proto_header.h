#pragma once

#include <stddef.h>
#include <time.h>
#include <inttypes.h>



typedef struct node {
  int value;
  char node_desc[20]; 
  int64_t arrival; 
  struct node *next;
} node_t;


typedef struct queue {
  node_t *front_pos;
  node_t *end_pos;
  int curr_length;
  int capacity;
} queue_t;



void enqueue(queue_t *queue, node_t *new_node);
node_t *dequeue(queue_t *queue);
void print_queue(queue_t *queue);
void print_node(node_t *node);
void destroy_queue(queue_t *queue);
int64_t time_milli_stamp();
int isNumber(char values[]);

queue_t *queue_init(int max_queue_length);
void intialise_node(node_t *data, int id);
void nano_sleep_process();
