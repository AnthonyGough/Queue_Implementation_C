#include <stddef.h>
#include <time.h>
#include <inttypes.h>
#pragma once

typedef struct node_data {
  int value;
  char node_desc[20];
  int64_t arrival;
} node_data_t;

typedef struct node {
  int value;
  char node_desc[20]; 
  int64_t arrival; 
  struct node *next;
} node_t;


typedef struct queue {
  node_t *front_pos;
  node_t *end_pos;
  size_t length;
} queue_t;



void enqueue(queue_t *queue, node_data_t *node_data);
node_t *dequeue(queue_t *queue);
void print_queue(queue_t *queue);
void print_node(node_t *node);
void destroy_queue(queue_t *queue);
int64_t time_milli_tstamp();