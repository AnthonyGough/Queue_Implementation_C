#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <inttypes.h>
#include <proto_header.h>

#define MINSLEEP 5000000L
#define MAXSLEEP 10000000L

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


int main(int argc, char *argv[]) {

  queue_t *queue_construct = malloc(sizeof(queue_t));
  queue_construct->end_pos=NULL;
  queue_construct->front_pos=NULL;
  queue_construct->length = 0;
  
  
  srand(time(NULL));
  node_data_t *data;
  
  int64_t now = time_milli_tstamp();
  
  for (int i=0; i < 5; i++) {
    data = malloc(sizeof(node_data_t));
    int rd_nm = rand() % (20-1+1) + 1;
    data->value = rd_nm;
    char str_num[4]= { 0 };
    char person_str[20] = "Person";
    sprintf(str_num, " %d", i);
    strcat(person_str, str_num);
    strcpy(data->node_desc, person_str);
    struct timespec ts;
    ts.tv_sec=0;
    ts.tv_nsec = ((rand() * rand()) % ((MAXSLEEP-MINSLEEP + 1) + MINSLEEP));
    nanosleep(&ts, NULL);     
    
    data->arrival =  time_milli_tstamp() - now;
    enqueue(queue_construct, data);
    free(data);
  }

  print_queue(queue_construct);
  node_t *node = dequeue(queue_construct);
  print_queue(queue_construct);
  print_node(node);
  destroy_queue(queue_construct);
  free(queue_construct);
}

int64_t time_milli_tstamp() {
  struct timespec now;
  timespec_get(&now, TIME_UTC);
  return ((int64_t)now.tv_sec) * 1000 + ((int64_t)now.tv_nsec)/1000000;
}

void print_node(node_t *node) {
  printf("\nNode dequed is %s with ticket number %d\n", node->node_desc, node->value);
}

void destroy_queue(queue_t *queue) {
    node_t *node = queue->front_pos;
    node_t *tmp;

    while (node) {
      tmp=node;
      node=node->next;
      free(tmp);      
    }
}

void print_queue(queue_t *queue) {
  node_t *node = queue->front_pos;
  int pos = 0;
  printf("\nThe length of the queue is %ld\n", queue->length);
  while (node) {
    printf("\nNode at position %d contains %s with ticket number %d - arrived at time %lu\n",pos++, node->node_desc, node->value, node->arrival);
    node = node->next;
  }
}