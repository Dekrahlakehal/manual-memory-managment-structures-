# Manual Memory Management Structures

A small C project focused on learning how dynamic memory works by building a custom growable byte buffer.

## Project Goal

This project demonstrates core systems-programming ideas:

- heap allocation with `malloc`
- resizing memory with `realloc`
- pointer arithmetic
- struct-based data ownership
- freeing memory safely with `free`

## Files

- `buffer.c` — the main C source file for the buffer implementation

## Core Concepts

### ByteBuffer

The `ByteBuffer` struct stores:

- `data`: pointer to the raw byte storage
- `capacity`: total allocated bytes
- `size`: how many bytes are currently used

### Lifecycle

1. Create the buffer
2. Append data safely
3. Resize if needed
4. Free all allocated memory

## Typical Workflow

- Allocate the buffer container itself
- Allocate the raw byte array for storage
- Append bytes to the end of the buffer
- If capacity is too small, grow the storage
- When done, free the internal array and the struct

## Why this matters

This is a foundational pattern in C for:

- network packet handling
- file buffers
- custom string builders
- binary data processing

## Compile

```bash
gcc -std=c11 -Wall -Wextra -pedantic buffer.c -o buffer
```

## Run

```bash
./buffer
```

## Notes

This is intentionally a learning project. It is designed to make the mental model behind dynamic memory and buffer management more concrete.
