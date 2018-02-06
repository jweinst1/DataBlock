#ifndef DATA_BLOCK_HEADER
#define DATA_BLOCK_HEADER
/** DataBlock
 * @author = Joshua Weinstein
 * @github = jweinst1
 * @email = jweinst1@berkeley.edu
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// example of dynamic datablock objects

#define DataBlock_NEW(size) malloc(sizeof(struct DataBlock) + (sizeof(unsigned char) * size));

#define DataBlock_SIZE(sobj) (sobj->cap + sizeof(struct DataBlock))
#define DataBlock_SPACE(dblock) (dblock->cap - dblock->len)
#define DataBlock_FITS(dblock, sizeN) ((dblock->cap - dblock->len) > sizeN)
// The amount of
#define DataBlock_ADDSPC 5

// Nullifies both ends of a data block
#define DataBlock_NULLIFY(dblock) do { \
                dblock->next = NULL; \
                dblock->prev = NULL; \
} while (0)

#define DataBlock_EXPAND(dblock, amount) do { \
                dblock = realloc(dblock, dblock->cap + amount + DataBlock_ADDSPC); \
                dblock->cap += amount + DataBlock_ADDSPC; \
} while (0)

struct DataBlock
{
        struct DataBlock* next;
        struct DataBlock* prev;
        size_t cap;
        size_t len;
        unsigned char data[0];
};


struct DataBlock* DataBlock_new(size_t size)
{
        struct DataBlock* newblock = DataBlock_NEW(size);
        newblock->len = 0;
        newblock->cap = size;
        DataBlock_NULLIFY(newblock);
        return newblock;
};

// Functional version of expansion macro.
void DataBlock_expand(struct DataBlock** block, size_t size)
{
        *block = realloc(*block, (*block)->cap + size + DataBlock_ADDSPC);
        (*block)->cap += size + DataBlock_ADDSPC;
};




#endif
