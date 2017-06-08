# include <stdint.h>
# include <stdbool.h>
# include "huffman.h"
# include <unistd.h>
# include "code.h"
# include "treestack.h"
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <ctype.h>

treeNode *newNode(uint8_t s, bool l, uint64_t c)
{
    treeNode *node = malloc(sizeof(treeNode));
    node->symbol = s;
    node->count = c;
    node->leaf = l;
    node -> left = NULL;
    node -> right = NULL;	
    return node; 
}

int32_t stepTree (treeNode *root, treeNode **t, uint32_t code)
{
	treeNode *current;
		
	if( code == 0)
	{
		current = root -> left;
	}
	else
	{
		current = root -> right;
	}
	 		
	*t = current;
	
	if( current -> leaf == true)
	{
		return current -> symbol; 
	}
	
	return -1; 

}

void delTree(treeNode *t)
{
	if( t -> left )
	{
		delTree( t -> left);
	}
	if ( t -> right )
	{
		delTree( t -> right);
	}

	delNode(t);
	return; //used to return void *
}
void buildCode(treeNode *t, code s, code table[256]) // ->>>> dead as harambe's meme THANKS DAILY DOT ( ͡° ͜ʖ ͡°)
{
	uint32_t pop;		
	if( t -> left != NULL)
	{
		
		pushCode( &s, 0);																										
		buildCode( t -> left, s, table);
		popCode(&s, &pop);
	} 
	if( t -> right != NULL )
	{
		pushCode( &s, 1);
		buildCode( t -> right, s, table); 
		popCode(&s, &pop);
	}
	
	if(t -> leaf == true)
	{
		code r = newCode();
		uint32_t tempL = s.l;
		for(uint32_t i = 0; i < tempL; i++ )
		{
			uint32_t temp = 0;
			popCode(&s,&temp);
			pushCode(&r, temp);
		}
		r.l = tempL;
		table[(int)t -> symbol] = r;
		//table[t->symbol] = s;
	}
	return;

}

void dumpTree( treeNode *t, int file)
{
	uint8_t leaf = 'L';
	uint8_t stopit = 'I';
	if( t -> left )
	{
		dumpTree( t -> left, file);
	}
	if( t -> right )
	{	
		dumpTree( t -> right, file);

	}

	if( t -> leaf == true)
	{
		
		write(file,&leaf, sizeof(uint8_t));
		write(file, &(t -> symbol), sizeof(uint8_t)); 
	}
	else
	{
		write(file, &stopit, sizeof(uint8_t)); 
	}

}

treeNode *loadTree(uint8_t savedTree[] , uint16_t treeBytes)
{
	treeStack *stack = newTreeStack(); 
	
	treeNode *tempNode; 
	treeNode *tempRight;
	treeNode *tempLeft;


	for( uint16_t i = 0 ; i < treeBytes; i++)
	{
		if( savedTree[i] == 'L' )
		{
			i++;
			tempNode = newNode( savedTree[i], true, 0);
			treePush( stack, tempNode);
		}
		else if( savedTree[i]  == 'I')
		{
			tempRight = treePop(stack);
			tempLeft = treePop(stack);
			treePush( stack, join(tempLeft, tempRight));	
		}
	}		
	treeNode *final = treePop(stack);
	delTreeStack(stack);
	return final;
}


treeNode *join(treeNode *l, treeNode *r)
{
    treeNode *t = newNode('$', false, l->count + r->count);
    t->left = l;
    t->right = r;
    return t;
}



void printTree(treeNode *t, int depth)
{
	if (t) 
	{
		printTree(t->left, depth + 1);

		if (t->leaf)
		{
			if (isalnum(t->symbol))
			{
				spaces(4 * depth); printf("'%c' (%lu)\n", t->symbol, t->count);
			}
			else
			{
			spaces(4 * depth); printf("0x%X (%lu)\n", t->symbol, t->count);
			}
		}
		else
		{
			spaces(4 * depth); printf("$ (%lu)\n", t->count);
		}

		printTree(t->right, depth + 1); 
	}

	return;
}
