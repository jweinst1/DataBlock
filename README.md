# DataBlock

*A C library for handling dynamic, binary chunks of data.*

`DataBlock` is a C-header library that provides a unique data structure called a `DataBlock`, intended for easy handling of chunks of bytes, or binary data. `DataBlock` is packaged as a header to make it easy to embed and include in your project.

## Installation

To use DataBlock, simply include the `src/Datablock.h` file in the source directory.

### Tests

To build the test suite, in the directory, run `make all`, then run the test executable, `./bin/DataBlockTest`.

## Mechanics

DataBlock is based around a model of a two-way linked list, except every node also functions as a buffer itself. The blocks are singly allocated sections of data which had a header portion, that includes the previous block, next block, the capacity, and the length, and the body, which contains the actual binary data.

The `DataBlock` structure is implemented like this.

```c

struct DataBlock
{
        struct DataBlock* next;
        struct DataBlock* prev;
        size_t cap;
        size_t len;
        unsigned char data[0];
};
```

The entire block is allocated into a single block of memory. This allows it to be variably sized.
Additionally, blocks can be written into one another, such as with the function `DataBlock_put_block()`.

### Structure

DataBlock's can be linked together in a chain, to form a stream-like data structure. DataBlock's can be used to implement a dynamic stream of data, that can be easily cut or expanded when needed.

For example, the `DataBlock_print_debug()` method prints out something like this.

```
___Block_1_______
Header::
@self = 0x7ff3aac02660
@next = 0x7ff3aac02690
@prev = 0x0
@length = 5
@capacity = 10
Body::
(0.) -> 5
(1.) -> 5
(2.) -> 5
(3.) -> 5
(4.) -> 5
___Block_1_end___
___Block_2_______
Header::
@self = 0x7ff3aac02690
@next = 0x7ff3aac026c0
@prev = 0x7ff3aac02660
@length = 10
@capacity = 15
Body::
(0.) -> 66
(1.) -> 66
(2.) -> 66
(3.) -> 66
(4.) -> 66
(5.) -> 66
(6.) -> 66
(7.) -> 66
(8.) -> 66
(9.) -> 66
___Block_2_end___
___Block_3_______
Header::
@self = 0x7ff3aac026c0
@next = 0x0
@prev = 0x7ff3aac02690
@length = 10
@capacity = 15
Body::
(0.) -> 66
(1.) -> 66
(2.) -> 66
(3.) -> 66
(4.) -> 66
(5.) -> 66
(6.) -> 66
(7.) -> 66
(8.) -> 66
(9.) -> 66
___Block_3_end___
```

The `header` of each DataBlock contains info about the block, its next and previous sister blocks, its length, and it's capacity.

The `len` property of each block can be reset to zero, allowing the existing data to be overwritten, which can conserve space.


## License

`DataBlock` is licensed under the MIT license.
