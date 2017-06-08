# ifndef _QUEUE_H
# define _QUEUE_H
# include <stdint.h>
# include <stdbool.h>

typedef treeNode *item; // treeNode defined in huffman.h

typedef struct queue
{
    uint32_t size; // Size of the queue.
    uint32_t head , tail; // Indexes of the head and tail.
    item *Q; // item array.
} queue;

queue *newQueue(uint32_t); // Creates new queue.
void delQueue(queue *); // Deletes the whole queue.

bool emptyQ(queue *); // Checks if the queue is empty.
bool fullQ(queue *); // Checks if the queue is full.

bool enqueue(queue *, item ); // Adds a treeNode to the queue.
bool dequeue(queue *, item *); // Removes the lowest treeNode from the queue.

#endif
