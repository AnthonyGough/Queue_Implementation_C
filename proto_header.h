#pragma once

#include <stddef.h>
#include <time.h>
#include <inttypes.h>
#include <stdbool.h>



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


int ask_to_queue();
bool enqueue(queue_t *queue, node_t *new_node);
node_t *dequeue(queue_t *queue);
node_t *peek(queue_t *queue);
bool isFull(queue_t *queue);
bool isEmpty(queue_t *queue);
void print_queue(queue_t *queue);
void print_node(node_t *node);
int validate_new_length(queue_t *queue, int num_to_add);
void final_queue_state(queue_t *queue);
void destroy_queue(queue_t *queue);
int64_t time_milli_stamp();
int isNumber(char values[]);

queue_t *queue_init(int max_queue_length);
void create_node(node_t *data, int id);
void nano_sleep_process();
bool add_to_queue(queue_t *queue);
