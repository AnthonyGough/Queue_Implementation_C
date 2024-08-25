[![The C Standard Library](https://www.eldemy.com/assets/images/media/pictures/courses/c_programming_for_beginners.jpg)
# QUEUE ADT - C Implementation - C Standard Library
###  Core Data Structure: Singly Linked List
#####  Elements of the Queue: 
- Nodes implemented using self-referencing structs linked by pointers
- Pointers to head and tail of queue
- FIFO Data Structure - Nodes added to end of queue (Enqueue)

##### Queue API/Operations
- Enqueue (Add element to end of the queue)
- Dequeue (Remove the front element from the queue)
- Empty - Test if the queue is empty
- Destroy - Nodes freed (Dynamic memory deallocated)
- Peek - Node at front of queue returned but not removed
- IsFull - Theoretic Max Size reached - no more elements added to queue
- IsNull - True if pointers to head and tail of queue are NULL

***

## **Requirements**
1. **proto_header.h** (Function prototypes and ancillary data structures for queue implementastion)
2. **bounded_queue.c** (Implementation of the Queue ADT API/Operations)
3. **q_drive.c** (Driver file to test the queue operations correct
4. **makefile** (Provided to compile source code to **C** executable);

```
Compile source files using gcc
    gcc -o b_queue bounded_queue.c q_drive.c -I. -Wall
```


## Test Driver

Test driver will use a set of operations/function calls to verify that the implementation of the Queue is correct. Due to the nature of the underlying data structure (Linked-List) that is the core of the Queue, the FIFO nature of Queue operations and the additional functionality implemented in this Queue there are a number of cases that require verification to ensure the Queue implementation is correct.
