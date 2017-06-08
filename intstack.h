# ifndef _STACK_H
# define _STACK_H
# include <stdint.h>
# include <stdbool.h>

typedef struct intStack
{
	uint32_t size;
	uint32_t top; //indicates one index above the last in the stack 
	uint32_t *entries; 
} intStack;

intStack *newIntStack(); //sets memory for new intStack
void delIntStack(intStack*); // deletes intStack

uint32_t intPop(intStack *); //Returns top item and deletes it from the intStack
void intPush(intStack *, uint32_t); //Adds item to the top of the intStack 

bool emptyIntStack(intStack *); //returns true if intStack is empty
bool fullIntStack(intStack *); //returns true if intStack is full

# endif
