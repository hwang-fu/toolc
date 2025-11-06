#pragma once

#include <hwangfu/generic.h>
#include <hwangfu/result.h>
#include <hwangfu/assertion.h>

#ifndef HASHMAP_DEFAULT_CAPACITY
#define HASHMAP_DEFAULT_CAPACITY (20)
#endif // HASHMAP_DEFAULT_CAPACITY

typedef struct Hashmap Hashmap;
typedef struct HashmapEntry HashmapEntry;

struct HashmapEntry
{
    owned char * Key;
    owned arch   Val;
    owned HashmapEntry * Next;
};

struct Hashmap
{
    copied   u64             Capacity   ;
    copied   u64             Size       ;
    owned    HashmapEntry ** Buckets    ;
    borrowed dispose_fn    * Dispose    ;
};

