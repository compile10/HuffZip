// bv.h — Bit Vector interface
// // Author: Prof. Darrell Long
# ifndef _BV_H
# define _BV_H
# include <stdint.h>
# include <stdlib.h>
# include "code.h"

typedef struct bitV {
        uint8_t *v;
        uint32_t l;
} bitV;

# define clrBit(x, k) x->v[k / 8] &= ~(0x1 << k % 8)

# define valBit(x, k) ((x->v[k / 8] & (0x1 << k % 8)) != 0)

# define lenVec(x) (x->l)

static inline bitV *newVec(uint32_t l)
{
        bitV *v = (bitV *) malloc(sizeof(bitV));
        v->v = (uint8_t *) calloc(l / 8 + 1, sizeof(uint8_t));
        v->l = l;
        return v;
}

static inline void delVec(bitV *v)
{
        free(v->v); 
	free(v);
        return;
}

static inline void setBit(bitV *bv, uint64_t k)
{
        bv->v[k / 8] |=  (0x1 << k % 8);
        return;
}

static inline void appendCode(bitV *bv, uint64_t *indexBit, code *c)
{
        bool codeNotEmpty = true;
        code insertCode = *c;
        uint32_t popTemp;

        while( codeNotEmpty == true ) 
        {
                if(*indexBit == bv->l) //makes bitvector larger if full
                {
			bv->l = (bv->l) * 2;
                        bv->v = (uint8_t *)realloc(bv->v, (bv->l));
                }

                codeNotEmpty = popCode(&insertCode, &popTemp); 

		if( codeNotEmpty == true )
		{
                	if(popTemp == 1)
                	{
                        	setBit(bv, *indexBit);
                	}
			else
			{
				clrBit(bv, *indexBit);
			}

			++(*indexBit);
		}
    
        }

        return;
}
# endif
