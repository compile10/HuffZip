# include <stdint.h>
# include <stdbool.h>
# include "treestack.h"
# include "huffman.h"

treeStack *newTreeStack()
{
	treeStack *x = malloc(sizeof(treeStack)); 
	x -> size = 256; // Sets size to the amount of characters for in ASCII.
	x -> entries = calloc(x->size, sizeof(treeNode *)); // Double check.
	x -> top = 0;	
	return x;
}

void delTreeStack(treeStack *x) 
{
	free(x->entries); 
	x -> entries = NULL;
	free(x);
	x = NULL;
	
	return;
}

treeNode *treePop(treeStack *x) 
{
	if(!(empty(x))) // If it is empty, the function will return NIL.
	{
		treeNode *temp = x->entries[(--x->top)]; // The top is lowered by one and its index will be popped off.
		return temp;
	}
	else
	{
		return NIL;
	}
}

void treePush(treeStack *x, treeNode *new)
{
	if( full(x) == false) //if the stack is not full add to the stack
	{
		x -> entries[x -> top] = new;
		x -> top++;
	}
	else //add extra space before adding to the stack
	{
		x -> entries = realloc(x, x->top * x->top); 
		x -> entries[x -> top] = new;
		x -> top++;
	}

	return;
}

bool empty(treeStack *x)
{
	if( x -> top == 0) // If the ceiling is 0, that means no numbers are below index 0.
	{
		return true;
	}	
	return false;
	
}

bool full(treeStack *x)
{
	if( x -> top == x -> size) // If the top equals the max case scenario of size, then the stack is full.
	{
		return true;
	}
	return false;
	
}
