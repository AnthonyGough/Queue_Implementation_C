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
    create_node(data, i);
   
    nano_sleep_process();  
    
    data->arrival =  time_milli_stamp() - now;
    enqueue(queue_construct, data);
    
  }
  
  print_queue(queue_construct);
  if (!isEmpty(queue_construct)) {
    printf("\nDequeue person from the queue - first person in queue will be removed.\n");
    node_t *node = dequeue(queue_construct);
    print_node(node);
  } else {
    printf("\nQueue is empty - cannot dequeue\n");
  }
  print_queue(queue_construct); 
  
  
  int num = ask_to_queue();
  int final = validate_new_length(queue_construct, num);
  for (int i=0; i < final; i++) {
    if (add_to_queue(queue_construct)) {
      printf("\nNew person added to queue successfully\n");
      print_queue(queue_construct);
    } else {
      printf("\nCould not add new person - check queue!!\n");
      break;
    }
  }

  final_queue_state(queue_construct);
  
  
  printf("\nFinal queue structure\n");
  print_queue(queue_construct);      
  
  printf("\nRemoving all nodes in the queue\n");
  int total = queue_construct->curr_length;
  for (int i=0; i < total; i++) {
    node_t *removed_node = dequeue(queue_construct);
    print_node(removed_node);
  }         
  final_queue_state(queue_construct);      
  
  
  free(queue_construct);
}

void final_queue_state(queue_t *queue) {
  if (isEmpty(queue)) {
    printf("\nQueue is empty - no nodes in the queue\n");  
    return;
  }
  if (isFull(queue)) {
    printf("\nQueue is full - no spare space in the queue. Currently all %d spaces occupied.\n", queue->curr_length);    
  } 
  printf("\nCurrently %d nodes in the queue.", queue->curr_length);
  if (queue->curr_length!=1) {
    printf("\n%s is at the front of the queue and %s is at the end of the queue\n", peek(queue)->node_desc, queue->end_pos->node_desc);
  } else {
    printf("\nOnly one node in the queue - %s is the single person in the queue\n", peek(queue)->node_desc);
  }  
}

int ask_to_queue() {
  int num=0;
  do {
    printf("\nHow many to add to queue - ");
    if (scanf("%d", &num)!=1) {
      while (getchar()!='\n');
      fprintf(stderr, "\nInvalid input - please enter a single number.\n");
    } else if (num==0) {
      fprintf(stderr, "Please enter a number greater than zero (0)\n");
    }
  } while (num==0);
  return num;
}

int validate_new_length(queue_t *queue, int num_to_add) {
  if (queue->curr_length + num_to_add > queue->capacity) {
    printf("\nUnable to add %d persons to queue - will exceed capacity\nCan only add %d persons to queue\n",
                    num_to_add, queue->capacity-queue->curr_length);
    return queue->capacity-queue->curr_length;
  }
  return num_to_add;
}

bool add_to_queue(queue_t *queue) {    
    node_t *data = malloc(sizeof(node_t));
    data->arrival = queue->end_pos->arrival + (rand() % 10);
    create_node(data,rand() % 100);
    data->arrival = queue->end_pos->arrival + rand() % 30; 
    if (enqueue(queue, data)) {
      return true;
    }
 
    return false;
}



void create_node(node_t *data, int id) {
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



