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

#define DEFAULT_INITIAL_QUEUE_SIZE 5

#define MAX_QUEUE_SIZE 15


int main(int argc, char *argv[]) {

  if (argc!=3) {
    fprintf (stderr, "Usage: %s  initial_queue_length max_queue_length\n", argv[0]);
    return EXIT_FAILURE;
  }

  if ((!isNumber(argv[1])) ||  (!isNumber(argv[2]))) {
    fprintf(stderr, "Usage: %s initial_queue_length max_queue_length\nintial_queue_length: a numeric char between 0 and 9\
      \nmax_queue_length: a numerical char between 1 and %d\n\n", argv[0], MAX_QUEUE_SIZE);
      return EXIT_FAILURE;
  }
 
  if (atoi(argv[2])>MAX_QUEUE_SIZE) {
    fprintf(stderr, "Usage: %s initial_queue_length max_queue_length\nintial_queue_length: a numeric char between 0 and 9\
      \nmax_queue_length: a numerical char between 1 and %d\n\n", argv[0], MAX_QUEUE_SIZE);
      return EXIT_FAILURE;
  }

  srand(time(NULL));
  int init_queue_length = atoi(argv[1]);
  int max_queue_length = atoi(argv[2]);                    

  queue_t *queue_construct = malloc(sizeof(queue_t));
  setup_queue_data_structure(queue_construct, max_queue_length);  
  node_t *data;
  int64_t now = time_milli_stamp();
  
  for (int i=0; i < init_queue_length; i++) {
    data = malloc(sizeof(node_t));
    intialise_node(data, i);
   
    nano_sleep_process();  
    
    data->arrival =  time_milli_stamp() - now;
    enqueue(queue_construct, data);
    
  }

  print_queue(queue_construct);
  node_t *node = dequeue(queue_construct);
  print_queue(queue_construct);
  print_node(node);
  destroy_queue(queue_construct);
  free(queue_construct);
}

void nano_sleep_process() {
  struct timespec ts;
  ts.tv_sec=0;
  ts.tv_nsec = ((rand() * rand()) % ((MAXSLEEP-MINSLEEP + 1) + MINSLEEP));
  nanosleep(&ts, NULL);   
}

void intialise_node(node_t *data, int id) {
  int rd_nm = rand() % (20-1+1) + 1;
  data->value = rd_nm;
  char str_num[4]= { 0 };
  char person_str[20] = "Person";
  sprintf(str_num, " %d", id);
  strcat(person_str, str_num);
  strcpy(data->node_desc, person_str);
}

void setup_queue_data_structure(queue_t *queue_construct, int max_capacity)
{
  queue_construct->end_pos = NULL;
  queue_construct->front_pos = NULL;
  queue_construct->curr_length = 0;
  queue_construct->capacity = max_capacity;
}

int64_t time_milli_stamp() {
  struct timespec now;
  timespec_get(&now, TIME_UTC);
  return ((int64_t)now.tv_sec) * 1000 + ((int64_t)now.tv_nsec)/1000000;
}

void print_node(node_t *node) {
  printf("\nNode dequed is %s with ticket number %d\n", node->node_desc, node->value);
}



void print_queue(queue_t *queue) {
  node_t *node = queue->front_pos;
  int pos = 0;
  printf("\nThe length of the queue is %d\n", queue->curr_length);
  while (node) {
    printf("\nNode at position %d contains %s with ticket number %d - arrived at time %lu\n",pos++, node->node_desc, node->value, node->arrival);
    node = node->next;
  }
}