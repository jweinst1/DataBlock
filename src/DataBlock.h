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

// Macros used to determine if expansion is neccesary.
#define DataBlock_FITS(dblock, sizeN) ((dblock->cap - dblock->len) > sizeN)
#define DataBlock_FULL(dblock) (dblock->cap == dblock->len)

// Gets pointer corresponding to address at which new data will be written
#define DataBlock_WRITER(dblock) (dblock->data + dblock->len)

// Gets a casted pointer corresponding to the address at which new data will be written.
#define DataBlock_WRITE_TYPE(dblock, type) (type*)(dblock->data + dblock->len)

// The amount of extra space to add after expansion
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

// Links two data blocks together
#define DataBlock_CONNCET(block1, block2) do { \
                block1->next = block2; \
                block2->prev = block1; \
} while(0)

#define DataBlock_DISCON(block1, block2) do { \
                block1->next = NULL; \
                block2->prev = NULL; \
} while(0)

#define DataBlock_IS_FRONT(block) (block->prev == NULL && block->next != NULL)

#define DataBlock_IS_SING(block) (block->prev == NULL && block->next == NULL)

struct DataBlock
{
        struct DataBlock* next;
        struct DataBlock* prev;
        size_t cap;
        size_t len;
        unsigned char data[0];
};

// Allocates and creates a new datablock of some size.
struct DataBlock* DataBlock_new(size_t size)
{
        struct DataBlock* newblock = DataBlock_NEW(size);
        newblock->len = 0;
        newblock->cap = size;
        DataBlock_NULLIFY(newblock);
        return newblock;
};

// Creates and allocates a new data block from existing array of bytes
struct DataBlock* DataBlock_from_data(unsigned char* data, size_t amount)
{
        // Cushions with some extra space
        struct DataBlock* newblock = DataBlock_NEW(amount + DataBlock_ADDSPC);
        newblock->len = amount;
        newblock->cap = amount + DataBlock_ADDSPC;
        DataBlock_NULLIFY(newblock);
        memcpy(newblock->data, data, amount);
        return newblock;
};

// Functional version of expansion macro.
void DataBlock_expand(struct DataBlock** block, size_t size)
{
        *block = realloc(*block, (*block)->cap + size + DataBlock_ADDSPC);
        (*block)->cap += size + DataBlock_ADDSPC;
};

// Generic write function using memcpy
void DataBlock_write(struct DataBlock* block, unsigned char* restrict data, size_t amount)
{
        if(!DataBlock_FITS(block, amount)) DataBlock_EXPAND(block, amount);
        memcpy(DataBlock_WRITER(block), data, amount);
        block->len += amount;
};

// Writes a single byte to the block.
// Increments length and checks if full.
void DataBlock_put_byte(struct DataBlock* block, unsigned char byte)
{
        if(DataBlock_FULL(block)) DataBlock_EXPAND(block, 20);
        block->data[block->len++] = byte;
};

// Writes a 32-bit integer into the block
void DataBlock_put_int(struct DataBlock* block, int integ)
{
        if(!DataBlock_FITS(block, sizeof(int))) DataBlock_EXPAND(block, 20);
        *(int*)DataBlock_WRITER(block) = integ;
        block->len += sizeof(int);
};

// Writes a 64-bit integer into the block
void DataBlock_put_long(struct DataBlock* block, long integ)
{
        if(!DataBlock_FITS(block, sizeof(long))) DataBlock_EXPAND(block, 20);
        *(long*)DataBlock_WRITER(block) = integ;
        block->len += sizeof(long);
};

// Writes another block into a current block
void DataBlock_put_block(struct DataBlock* block, struct DataBlock* other)
{
        size_t amount = other->len;
        if(!DataBlock_FITS(block, amount)) DataBlock_EXPAND(block, amount);
        memcpy(DataBlock_WRITER(block), other->data, amount);
        block->len += amount;
};

// Sets the length of the block to 0, such that the block's old data can be overwritten.
// This function conserves memory and does not free or allocate more memory.
static inline void
DataBlock_empty(struct DataBlock* block)
{
        block->len = 0;
};

// Connects two blocks and returns the left side block
static inline struct DataBlock*
DataBlock_connect(struct DataBlock* block1, struct DataBlock* block2)
{
        block1->next = block2;
        block2->prev = block1;
        return block1;
};

// Gets the front of the chain of blocks
static inline struct DataBlock*
DataBlock_front(struct DataBlock* block)
{
        while(block->prev != NULL) block = block->prev;
        return block;
};

// Gets the back of the chain of blocks.
static inline struct DataBlock*
DataBlock_back(struct DataBlock* block)
{
        while(block->next != NULL) block = block->next;
        return block;
};

// Appends one data block to the back of another.
void DataBlock_append(struct DataBlock* block1, struct DataBlock* block2)
{
        while(block1->next != NULL) block1 = block1->next;
        block1->next = block2;
        block2->prev = block1;
};




#endif
