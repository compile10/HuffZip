# include <stdint.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include "intstack.h"

intStack *newIntStack()
{
	intStack *x = malloc(sizeof(intStack)); 
	x -> size = 5000; // Sets size to the amount of characters for in ASCII.
	x -> entries = calloc(x->size, sizeof(uint32_t)); 
	return x;
}


void delIntStack(intStack *x) 
{
	free(x -> entries);
	x -> entries = NULL;
	free(x);
	x = NULL;
	
	return;
}

uint32_t intPop(intStack *x) 
{
	if(!(emptyIntStack(x))) // If it is empty, the function will return NULL.
	{
		uint32_t temp = x->entries[--x->top];
		return temp;
	}
	else
	{
		return 505505;
	}
}

void intPush(intStack *x, uint32_t new)
{
	if(fullIntStack(x) == false) //if the stack is not full add to the stack
	{
		x->entries[x->top] = new;
		++(x->top);
	}
	else //add extra space before adding to the stack
	{
		uint32_t reSize = (x->size)*2;
		x->entries = realloc(x->entries, reSize); 
		x->entries[x->top] = new;
		++(x->top);
	}
	return;
}

bool emptyIntStack(intStack *x)
{
	if(x->top == 0) // If the ceiling is 0, that means no numbers are below index 0.
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool fullIntStack(intStack *x)
{
	if(x->top == x->size) // If the top equals the max case scenario of size, then the stack is full.
	{
		return true;
	}
	else
	{
		return false;
	}
}
