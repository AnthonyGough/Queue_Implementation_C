#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <inttypes.h>
#include <proto_header.h>



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

  queue_t *queue_construct = queue_init(max_queue_length);
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



void intialise_node(node_t *data, int id) {
  int rd_nm = rand() % (20-1+1) + 1;
  data->value = rd_nm;
  char str_num[4]= { 0 };
  char person_str[20] = "Person";
  sprintf(str_num, " %d", id);
  strcat(person_str, str_num);
  strcpy(data->node_desc, person_str);
}



void print_node(node_t *node) {
  printf("\nNode dequed is %s with ticket number %d\n", node->node_desc, node->value);
  
}



