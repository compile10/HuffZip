# ifndef _HUFFMAN_H
# define _HUFFMAN_H
# include <stdint.h>
# include <stdint.h>
# include <stdbool.h>
# include <unistd.h>
# include "code.h"
# include <string.h>
# include <stdlib.h>
# include <stdio.h>



# ifndef NIL
# define NIL (void *) 0
# endif

typedef struct DAH treeNode;

struct DAH
{
    uint8_t  symbol;
    uint64_t count;
    bool     leaf;
    treeNode  *left, *right;
};

treeNode *newNode(uint8_t s, bool l, uint64_t c);


void delTree(treeNode *t);


void dumpTree(treeNode *t, int file);


treeNode *loadTree(uint8_t savedTree [], uint16_t treeBytes);


int32_t stepTree(treeNode *root , treeNode **t, uint32_t code);

void buildCode(treeNode *t, code s, code table [256]);

static inline void delNode(treeNode *h) { free(h); return; }


static inline int8_t compare(treeNode *l, treeNode *r)  
{  
    return l->count - r->count;
}

treeNode *join(treeNode *l, treeNode *r);

static inline void spaces(int c) { for (int i = 0; i < c; i += 1) { putchar(' '); } return; }

void printTree(treeNode *t, int depth);


# endif
