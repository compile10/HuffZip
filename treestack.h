# ifndef _STACK_H
# define _STACK_H
# include <stdint.h>
# include <stdbool.h>
# include "huffman.h"

typedef struct treeStack
{
	uint32_t size;
	uint32_t top; //indicates one index above the last in the stack 
	treeNode **entries; 
} treeStack;

treeStack *newTreeStack(); //sets memory for new treeStack
void delTreeStack(treeStack*); // deletes treeStack

treeNode *treePop (treeStack *); //Returns top item and deletes it from the treetStack
void treePush(treeStack *, treeNode *); //Adds item to the top of the treeStack 

bool empty(treeStack *); //returns true if treeStack is empty
bool full(treeStack *); //returns true if treeStack is full
# endif
