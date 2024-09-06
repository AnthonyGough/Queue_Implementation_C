#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>
#include <inttypes.h>
#include <sys/time.h>
#include <errno.h>
#include <proto_header.h>


#define MINSLEEP 5000000L
#define MAXSLEEP 10000000L

#define FUNCTION_CALL_ERROR -1

/**
 * Function to check each and every value in char array is a numeric character from 0 to 9 excluding
 * the null terminator.
 * 
 * \param value[] - array of chars
 * \return true iff every char belongs to set of numeric chars {'0', '1', '2'...'9'} else false
 */
int isNumber(char values[]) {
    int i;   
    for (i=0; values[i]!='\0';i++) {
        if (isdigit(values[i])==0) {
            return false;
        }
    }
    return true;
}

/**
 * Precondition: Queue has been initialised by invoking queue_init
 * Postcondition: The length of the queue/number of nodes in the queue are printed to stdout.
 *                Elements present in the queue are printed to stdout starting from and including the front 
 *                of the queue to the last element in the queue. When the pointer to the next node in the queue
 *                is the same as the element at the front of the queue the circular buffer has been completely traversed.
 *\param queue - Pointer to the queue object
 */
void print_queue(queue_t *queue) {
    node_t *node = queue->front_pos;
    int pos = 0;
    printf("\nThe length of the queue is %d\n", queue->curr_length);
    do {
        printf("\nNode at position %d contains %s with ticket number %d - arrived at time %lu\n",pos++, node->node_desc, node->value, node->arrival);
        node = node->next;
    } while (node!=queue->front_pos);
}


/**
 * Function to sleep process a random number of nanoseconds - the value of tv_nsec must be between 0-999999999
 * otherwise application may return an error. Sleep is a random value in the domain of MINSLEEP to MAXSLEEP using a
 * higher precision for sleep interval.
 */
void nano_sleep_process() {
    
    struct timespec ts;
    ts.tv_sec=0;
    ts.tv_nsec = ((rand() * rand()) % ((MAXSLEEP-MINSLEEP + 1) + MINSLEEP));
        
    if (nanosleep(&ts, NULL) == FUNCTION_CALL_ERROR) {
        if (errno==EINTR) {
            fprintf(stderr, "\nSleep interrupted by a signal handler - the remaining sleep time is recoverable\n");
        } else if (errno==EINVAL) {
            fprintf(stderr, "\nInvalid value range for tv_nsec - This is not a recoverable error\n");
            ts.tv_sec*=-1;
            ts.tv_nsec*=-1;
           // exit(EXIT_FAILURE);
        }
    }  
}

/**
 * Function returns a timestamp calculation using nanoseconds to create an arbitarty arrival time by calling
 * function twice and calculating the difference between the timestamp. This is an artificial measurement to
 * provide some method to tag a node with an ordered arrival time. 
 */
int64_t time_milli_stamp() {
    struct timespec now;
    timespec_get(&now, TIME_UTC);
    return ((int64_t)now.tv_sec) * 1000 + ((int64_t)now.tv_nsec)/1000000;
}