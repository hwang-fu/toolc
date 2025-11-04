#include "memory.h"

OWNED void * new_(COPIED u64 bytes)
{
    OWNED void * ptr = malloc( bytes );
    SCP(ptr);
    return ptr;
}

OWNED void * zeros_(COPIED u64 bytes)
{
    OWNED void * ptr = calloc(bytes, sizeof(char));
    SCP(ptr);
    return ptr;
}

OWNED void * realloc_safe(OWNED void * arg, COPIED u64 newSizeInBytes)
{
    OWNED void * ptr = realloc(arg, newSizeInBytes);
    SCP(ptr);
    return ptr;
}

COPIED void * dispose(OWNED void * arg)
{
    XFREE(arg);
    return nil;
}
