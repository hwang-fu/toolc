#include "hashmap.h"

/**
 * @since       06.11.2025
 * @author      Junzhe
 * @modified    06.11.2025
 *
 */
struct HashmapEntry
{
    OWNED char * Key;
    OWNED arch   Val;
    OWNED HashmapEntry * Next;
};

static u64 fnv1a_hash_(BORROWED const char * key);
static COPIED void * hme_dispose(OWNED void * arg, dispose_fn * cleanup);

static u64 fnv1a_hash_(BORROWED const char * key)
{
    u64 hash = 14695981039346656037UL;              // FNV offset basis
    for (; *key; ) {
        hash ^= (u64)(*key++);
        hash *= 1099511628211UL;                    // FNV prime
    }
    return hash;
}

OWNED Hashmap * hm_init(OWNED Hashmap * hm, u64 capacity, dispose_fn * cleanup)
{
    if (!hm)
    {
        hm = NEW(sizeof(Hashmap));
        WARNINGF(
                "%s(): allocating default memory space for hashmpa initialization.",
                __func__,
                HASHMAP_DEFAULT_CAPACITY);
    }

    if (EQ(capacity, 0))
    {
        capacity = HASHMAP_DEFAULT_CAPACITY;
        WARNINGF(
                "%s(): hashmap initialized capacity is zero, default to %lu.",
                __func__,
                HASHMAP_DEFAULT_CAPACITY);
    }

    hm->Capacity = capacity;
    hm->Size     = 0UL;
    hm->Buckets  = ZEROS(capacity * sizeof(HashmapEntry*));
    hm->Dispose  = cleanup;

    return hm;
}

/*
 * Possible overloads:
 * @li OWNED Dequeue * mk_hm(1, u64 capacity)
 * @li OWNED Dequeue * mk_hm(2, dispose_fn * cleanup)
 * @li OWNED Dequeue * mk_hm(3, u64 capacity, dispose_fn * cleanup)
 * @li OWNED Dequeue * mk_hm(4, dispose_fn * cleanup, u64 capacity)
 */
OWNED Hashmap * mk_hm(int mode, ...)
{
    va_list ap;
    va_start(ap, mode);

    u64          capacity = DEQUEUE_DEFAULT_CAPACITY;
    dispose_fn * cleanup  = NIL;
    switch (mode)
    {
        case 0:
        {
        } break;

        case 1:
        {
            capacity = va_arg(ap, u64);
        } break;

        case 2:
        {
            cleanup = va_arg(ap, dispose_fn*);
        } break;

        case 3:
        {
            capacity = va_arg(ap, u64);
            cleanup  = va_arg(ap, dispose_fn*);
        } break;

        case 4:
        {
            cleanup  = va_arg(ap, dispose_fn*);
            capacity = va_arg(ap, u64);
        } break;

        default:
        {
            PANIC("%s(): unkown mode %d", mode);
        } break;
    }

    va_end(ap);
    return hm_init(NIL, capacity, cleanup);
}

void _hm_ins(BORROWED Hashmap * hm, BORROWED const char * key, arch val)
{
}

void _hm_ins_owned_key(BORROWED Hashmap * hm, OWNED char * key, arch val)
{
}

arch hm_get(BORROWED Hashmap * hm, BORROWED const char * key)
{
}

arch hm_get_owned_key(BORROWED Hashmap * hm, OWNED char * key)
{
}

void hm_del(BORROWED Hashmap * hm, BORROWED const char * key)
{
}

void hm_del_owned_key(BORROWED Hashmap * hm, OWNED char * key)
{
}

OWNED Result * hm_try_get(BORROWED Hashmap * hm, BORROWED const char * key)
{
}

OWNED Result * hm_try_get_owned_key(BORROWED Hashmap * hm, OWNED char * key)
{
}

OWNED Result * _hm_try_ins(BORROWED Hashmap * hm, BORROWED const char * key, arch val)
{
}

OWNED Result * _hm_try_ins_owned_key(BORROWED Hashmap * hm, OWNED char * key, arch val)
{
}

OWNED Result * hm_try_del(BORROWED Hashmap * hm, BORROWED const char * key)
{
}

OWNED Result * hm_try_del_owned_key(BORROWED Hashmap * hm, OWNED char * key)
{
}

u64 hm_get_size(BORROWED Hashmap * hm)
{
    OWNED Result * result = hm_try_get_size(hm);
    if (RESULT_GOOD(result))
    {
        return result_unwrap_owned(result, NIL);
    }

    u64 errcode = (u64) result->Failure;
    result_dispose(result);
    switch (errcode)
    {
        case 0:
        {
            PANIC("%s(): NIL hm argument.", __func__);
        } break;

        default:
        {
            PANIC("%s(): Unknown error.", __func__);
        } break;
    }
}

OWNED Result * hm_try_get_size(BORROWED Hashmap * hm)
{
    if (!hm)
    {
        return RESULT_FAIL(0);
    }

    return RESULT_SUCCEED(hm->Size);
}

static COPIED void * hme_dispose(OWNED void * arg, dispose_fn * cleanup)
{
    if (!arg)
    {
        return NIL;
    }

    OWNED HashmapEntry * hme = CAST(arg, HashmapEntry*);

    while (hme->Next)
    {
        hme_dispose(hme->Next, cleanup);
    }

    XFREE(hme->Key);
    if (cleanup)
    {
        cleanup(hme->Val);
    }

    return dispose(hme);
}

COPIED void * hm_dispose(OWNED void * arg)
{
    if (!arg)
    {
        return NIL;
    }

    OWNED Hashmap * hm = CAST(arg, Hashmap*);

    u64          capacity = hm->Capacity;
    dispose_fn * cleanup  = hm->Dispose;
    for (uint64_t i = 0; i < capacity; i++)
    {
        hme_dispose(hm->Buckets[i], cleanup);
    }
    XFREE(hm->Buckets);

    return dispose(hm);
}
