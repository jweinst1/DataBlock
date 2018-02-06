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

## License

`DataBlock` is licensed under the MIT license.
