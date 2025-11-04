#pragma once

#include <stdlib.h>

#include "hwangfu/generic.h"
#include "hwangfu/assertion.h"

// -------------------------------------------------------------
// | Memory Safety Allocator Macros|
// -------------------------------------------------------------
/**
 * XFREE(ptr):
 *      1. Frees the pointer if not NIL.
 *      2. Sets the pointer to NIL after freeing.
 */
#define XFREE(ptr)                                                  \
        do {                                                        \
            if ( (ptr) ) free( ptr );                               \
            ptr = NIL;                                              \
        } while (0)

/**
 * NEW(bytes):
 *      1. Allocates `n` bytes from the heap.
 *      2. Aborts the program if failed to allocate.
 */
#define NEW(n)                                                      \
        new_( n )

/**
 * ZEROS(bytes):
 *      1. Allocates `n` bytes from the heap and nullify them all.
 *      2. Aborts the program if failed to allocate.
 */
#define ZEROS(n)                                                    \
        zeros_( n )


// -------------------------------------------------------------
// | Memory Allocation Helpers |
// -------------------------------------------------------------
OWNED void * new_(COPIED u64 bytes);
OWNED void * zeros_(COPIED u64 bytes);
OWNED void * realloc_safe(OWNED void * arg, COPIED u64 newSizeInBytes);
COPIED void * dispose(OWNED void * arg);
