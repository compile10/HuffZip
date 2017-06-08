// PIAZZA POST @ 1042 Darrell Long
# include <stdint.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include "huffman.h"
# include "queue.h"

# define SWAP(A,B) {item Temp = A; A = B; B = Temp;}

queue *newQueue(uint32_t s) // Creates a new Queue.
{
    queue *x = malloc(sizeof(queue));
    x->size = s;
    x->head = 1;
    x->tail = 0;
    x->Q = calloc(s+1, sizeof(item));
    return x;
}

void delQueue(queue *q)
{
    free(q->Q); // Deletes the queue array and the queue itself.
    q->Q = NULL;
    free(q);
    q = NULL;
    return;
}

bool emptyQ(queue *q) // Checks if the queue by seeing if the q->tail is zero.
{
    if(q->tail == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool fullQ(queue *q) // Maybe increase size of x->Q.
{
    if(q->tail == q->size+1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void reInsertHeap(queue *q, uint32_t last) // Reinserts a node into the heap by the tail.
{
    uint32_t newNode = last, parent = last/2;
    
    while(q->head <= parent) 
    // Basically the treeNode goes up the heap until it becomes the root itself or it hits a number
    // that is lower than itself.
    {
        if((q->Q[parent])->count > (q->Q[newNode]->count))
        {
            SWAP(q->Q[parent], q->Q[newNode]);
        }
        else
        {
            break;
        }
        newNode = parent; // Then the newNode becomes the becomes the parent for the next part of the while loop.
        parent = newNode/2;
    }
    return;
}

void reDequeueHeap(queue *q)
{
    // Takes the lowest number from the root and then replace the head of the array with the heap's tail. Then 
    // reHeaps the whole heap until the new root is in the correct place on the heap.
    uint32_t parent = q->head, lChild = parent*2, rChild = lChild+1;
    uint32_t leastChild;
    while(lChild <= q->tail)
    {
        if(lChild == q->tail)
        {
            leastChild = lChild;
        }
        else if((q->Q[lChild])->count <= (q->Q[rChild])->count)
        {
            leastChild = lChild;
        }
        else
        {
            leastChild = rChild;
        }
        
        if((q->Q[parent])->count <= (q->Q[leastChild])->count)
        {
            break;
        }
        else
        {
            SWAP(q->Q[parent], q->Q[leastChild]);
        }
        parent = leastChild;
        lChild = parent*2;
        rChild = lChild+1;
    }
    return;
}

bool enqueue(queue *q, item i)
{
    // If the queue is full, the enqueue returns false.
    if(fullQ(q))
    {
        return false;
    }
    // If not, the q->tail receives the new item, and then they reheap the heap, until the new q->tail is
    // in the corrent place of the heap.
    ++(q->tail);
    q->Q[q->tail] = i;
    if(q->tail != q->head)
    {
        reInsertHeap(q, q->tail); // Does not heap is the heap has only one treeNode.
    }
    return true;
}

bool dequeue(queue *q, item *i)
{
    // If the queue is empty, the enqueue returns false.
    if(emptyQ(q))
    {
        return false;
    }
    *i = (q->Q[q->head]); // Dequeues the treeNode from the queue array.
    if(i == NULL) // If i is NULL, that means the queue is empty.
    {
	return false;
    }    
    q->Q[q->head] = q->Q[q->tail]; // Sets old tail to the head.
    --(q->tail); // Sets the tail back.
    if(emptyQ(q) || q->head == q->tail)
    {
        return true;
    }
    reDequeueHeap(q); // Then reheaps the whole entire heap.
    return true;
}
