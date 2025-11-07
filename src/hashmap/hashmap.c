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

static void hm_fit_(BORROWED Hashmap * hm, const u64 newCapacity);
static OWNED Result * hm_try_fit_(BORROWED Hashmap * hm, const u64 newCapacity);

static void hm_ins_helper_(BORROWED HashmapEntry ** buckets, u64 idx, OWNED HashmapEntry * entry);

static OWNED HashmapEntry * mk_hme_(BORROWED char * key, arch val);
static COPIED void * hme_dispose_(OWNED void * arg, dispose_fn * cleanup);
static COPIED void * hme_dispose_recursive_(OWNED void * arg, dispose_fn * cleanup);

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

    u64          capacity = HASHMAP_DEFAULT_CAPACITY;
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

static void hm_ins_helper_(BORROWED HashmapEntry ** buckets, u64 idx, OWNED HashmapEntry * entry)
{
    if (!buckets)
    {
        PANIC("%s(): ", __func__);
    }

    if (!entry)
    {
        PANIC("%s(): ", __func__);
    }

    entry->Next = buckets[idx];
    buckets[idx] = entry;
}

void _hm_ins(BORROWED Hashmap * hm, BORROWED const char * key, arch val)
{
    OWNED Result * result = _hm_try_ins(hm, key, val);
    if (RESULT_GOOD(result))
    {
        dispose(result);
        return;
    }

    u64 errcode = result->Failure;
    dispose(result);
    switch (errcode)
    {
        case 0:
        {
            PANIC("%s(): hm argument is " CRAYON_TO_BOLD("NIL") ".", __func__);
        } break;

        case 1:
        {
            PANIC("%s(): key is " CRAYON_TO_BOLD("NIL") ".", __func__);
        } break;

        case 2:
        {
            PANIC("%s(): key is " CRAYON_TO_BOLD("\"\"") ".", __func__);
        } break;

        case 3:
        {
            PANIC("%s(): failed to fit the capacity.", __func__);
        } break;

        case 4:
        {
            PANIC("%s(): Key " CRAYON_TO_BOLD("\"%s\"") " already exists.", __func__, key);
        } break;

        default:
        {
            PANIC("%s(): Unknown error code %lu.", __func__, errcode);
        } break;
    }
}

void _hm_ins_owned_key(BORROWED Hashmap * hm, OWNED char * key, arch val)
{
    _hm_ins(hm, key, val);
    XFREE(key);
}

arch hm_get(BORROWED Hashmap * hm, BORROWED const char * key)
{
    OWNED Result * result = hm_try_get(hm, key);
    if (RESULT_GOOD(result))
    {
        return result_unwrap(result, NIL);
    }

    u64 errcode = result->Failure;
    dispose(result);
    switch (errcode)
    {
        case 0:
        {
            PANIC("%s(): hm argument is " CRAYON_TO_BOLD("NIL") ".", __func__);
        } break;

        case 1:
        {
            PANIC("%s(): key is " CRAYON_TO_BOLD("NIL") ".", __func__);
        } break;

        case 2:
        {
            PANIC("%s(): key is " CRAYON_TO_BOLD("\"\"") ".", __func__);
        } break;

        case 3:
        {
            PANIC("%s(): hm size is " CRAYON_TO_BOLD("0") ".", __func__);
        } break;

        case 4:
        {
            PANIC("%s(): Key " CRAYON_TO_BOLD("\"%s\"") " does not exist.", __func__, key);
        } break;

        default:
        {
            PANIC("%s(): Unknown error code %lu.", __func__, errcode);
        } break;
    }
}

arch hm_get_owned_key(BORROWED Hashmap * hm, OWNED char * key)
{
    OWNED Result * result = hm_try_get(hm, key);
    if (RESULT_GOOD(result))
    {
        XFREE(key);
        return result_unwrap(result, NIL);
    }

    u64 errcode = result->Failure;
    dispose(result);
    switch (errcode)
    {
        case 0:
        {
            PANIC("%s(): hm argument is " CRAYON_TO_BOLD("NIL") ".", __func__);
        } break;

        case 1:
        {
            PANIC("%s(): key is " CRAYON_TO_BOLD("NIL") ".", __func__);
        } break;

        case 2:
        {
            PANIC("%s(): key is " CRAYON_TO_BOLD("\"\"") ".", __func__);
        } break;

        case 3:
        {
            PANIC("%s(): hm size is " CRAYON_TO_BOLD("0") ".", __func__);
        } break;

        case 4:
        {
            PANIC("%s(): Key " CRAYON_TO_BOLD("\"%s\"") " does not exist.", __func__, key);
        } break;

        default:
        {
            PANIC("%s(): Unknown error code %lu.", __func__, errcode);
        } break;
    }
}

void hm_del(BORROWED Hashmap * hm, BORROWED const char * key)
{

    OWNED Result * result = hm_try_del(hm, key);
    if (RESULT_GOOD(result))
    {
        dispose(result);
        return;
    }

    u64 errcode = result->Failure;
    dispose(result);
    switch (errcode)
    {
        case 0:
        {
            PANIC("%s(): hm argument is " CRAYON_TO_BOLD("NIL") ".", __func__);
        } break;

        case 1:
        {
            PANIC("%s(): key is " CRAYON_TO_BOLD("NIL") ".", __func__);
        } break;

        case 2:
        {
            PANIC("%s(): key is " CRAYON_TO_BOLD("\"\"") ".", __func__);
        } break;

        case 3:
        {
            PANIC("%s(): hm size is " CRAYON_TO_BOLD("0") ".", __func__);
        } break;

        case 4:
        {
            PANIC("%s(): Key " CRAYON_TO_BOLD("\"%s\"") " does not exist.", __func__, key);
        } break;

        default:
        {
            PANIC("%s(): Unknown error code %lu.", __func__, errcode);
        } break;
    }
}

void hm_del_owned_key(BORROWED Hashmap * hm, OWNED char * key)
{
    hm_del(hm, key);
    XFREE(key);
}

OWNED Result * hm_try_get(BORROWED Hashmap * hm, BORROWED const char * key)
{
    if (!hm)
    {
        return RESULT_FAIL(0);
    }

    if (!key)
    {
        return RESULT_FAIL(1);
    }

    if (EQ(strlen_safe(key), 0))
    {
        return RESULT_FAIL(2);
    }

    if (EQ(hm->Size, 0))
    {
        return RESULT_FAIL(3);
    }

    u64 h        = fnv1a_hash_(key);
    u64 capacity = hm->Capacity;
    u64 idx      = h % capacity;

    BORROWED HashmapEntry * bucket = hm->Buckets[idx];
    while (bucket)
    {
        if (strcmp_safe(key, bucket->Key))
        {
            return RESULT_SUCCEED(bucket->Val);
        }
        bucket = bucket->Next;
    }

    return RESULT_FAIL(4);
}

OWNED Result * hm_try_get_owned_key(BORROWED Hashmap * hm, OWNED char * key)
{
    OWNED Result * result = hm_try_get(hm, key);
    XFREE(key);
    return result;
}

OWNED Result * _hm_try_ins(BORROWED Hashmap * hm, BORROWED const char * key, arch val)
{
    if (!hm)
    {
        return RESULT_FAIL(0);
    }

    if (!key)
    {
        return RESULT_FAIL(1);
    }

    if (EQ(strlen_safe(key), 0))
    {
        return RESULT_FAIL(2);
    }

    u64 size     = hm->Size;
    u64 capacity = hm->Capacity;
    if (WATERMARK(size, capacity) >= WATERMARK_HIGH)
    {
        do
        {
            capacity += 1;
            capacity *= 2;
        } while (WATERMARK(size, capacity) >= WATERMARK_LOW);

        if (!hm_try_fit_(hm, capacity))
        {
            return RESULT_FAIL(3);
        }
    }

    u64 h   = fnv1a_hash_(key);
    u64 idx = h % capacity;

    // Making sure that there is no duplicate key.
    if (hm->Buckets[idx])
    {
        BORROWED HashmapEntry * bucket = hm->Buckets[idx];
        while (bucket)
        {
            if (strcmp_safe(key, bucket->Key))
            {
                return RESULT_FAIL(4);
            }
            bucket = bucket->Next;
        }
    }

    hm_ins_helper_(hm->Buckets, idx, mk_hme_(key, val));

    hm->Size += 1;

    return RESULT_SUCCEED(0);
}

OWNED Result * _hm_try_ins_owned_key(BORROWED Hashmap * hm, OWNED char * key, arch val)
{
    OWNED Result * result = hm_try_ins(hm, key, val);
    XFREE(key);
    return result;
}

OWNED Result * hm_try_del(BORROWED Hashmap * hm, BORROWED const char * key)
{
    if (!hm)
    {
        return RESULT_FAIL(0);
    }

    if (!key)
    {
        return RESULT_FAIL(1);
    }

    if (EQ(strlen_safe(key), 0))
    {
        return RESULT_FAIL(2);
    }

    if (EQ(hm->Size, 0))
    {
        return RESULT_FAIL(3);
    }

    u64 h        = fnv1a_hash_(key);
    u64 capacity = hm->Capacity;
    u64 idx      = h % capacity;

    BORROWED HashmapEntry * bucket = hm->Buckets[idx];
    BORROWED HashmapEntry * prev   = NIL;
    while (bucket)
    {
        if (strcmp_safe(key, bucket->Key))
        {
            if (EQ(prev, NIL))
            {
                hm->Buckets[idx] = bucket->Next;
            }
            else
            {
                prev->Next = bucket->Next;
            }
            hme_dispose_(bucket, hm->Dispose);
            return RESULT_SUCCEED(0);
        }
        prev   = bucket;
        bucket = bucket->Next;
    }

    return RESULT_FAIL(4);
}

OWNED Result * hm_try_del_owned_key(BORROWED Hashmap * hm, OWNED char * key)
{
    OWNED Result * result = hm_try_del(hm, key);
    XFREE(key);
    return result;
}

bool hm_has(BORROWED Hashmap * hm, BORROWED const char * key)
{
    bool b = False;

    OWNED Result * result = hm_try_get(hm, key);
    if (RESULT_GOOD(result))
    {
        b = True;
    }
    dispose(result);

    return b;
}

bool hm_has_owned_key(BORROWED Hashmap * hm, OWNED char * key)
{
    bool b = False;

    OWNED Result * result = hm_try_get_owned_key(hm, key);
    if (RESULT_GOOD(result))
    {
        b = True;
    }
    dispose(result);

    return b;
}

u64 hm_get_size(BORROWED Hashmap * hm)
{
    OWNED Result * result = hm_try_get_size(hm);
    if (RESULT_GOOD(result))
    {
        return result_unwrap_owned(result, NIL);
    }

    u64 errcode = (u64) result->Failure;
    dispose(result);
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

u64 hm_get_capacity(BORROWED Hashmap * hm)
{
    OWNED Result * result = hm_try_get_capacity(hm);
    if (RESULT_GOOD(result))
    {
        return result_unwrap_owned(result, NIL);
    }

    u64 errcode = (u64) result->Failure;
    dispose(result);
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

OWNED Result * hm_try_get_capacity(BORROWED Hashmap * hm)
{
    if (!hm)
    {
        return RESULT_FAIL(0);
    }

    return RESULT_SUCCEED(hm->Capacity);
}

static void hm_fit_(BORROWED Hashmap * hm, const u64 newCapacity)
{
    OWNED Result * result = hm_try_fit_(hm, newCapacity);
    if (RESULT_GOOD(result))
    {
        dispose(result);
        return;
    }

    u64 errcode = result->Failure;
    dispose(result);
    switch (errcode)
    {
        case 0:
        {
            PANIC("%s(): hm argument is " CRAYON_TO_BOLD("NIL") ".", __func__);
        } break;

        case 1:
        {
            PANIC(
                    "%s(): old capacity " CRAYON_TO_BOLD("%lu") " is greater than or equal to the new capacity " CRAYON_TO_BOLD("%lu") ".", __func__,
                    hm->Capacity,
                    newCapacity);
        } break;

        default:
        {
            PANIC("%s(): Unknown error code %lu.", __func__, errcode);
        } break;
    }
}

static OWNED Result * hm_try_fit_(BORROWED Hashmap * hm, const u64 newCapacity)
{
    if (!hm)
    {
        return RESULT_FAIL(0);
    }

    u64 oldCapacity = hm->Capacity;
    if (oldCapacity >= newCapacity)
    {
        return RESULT_FAIL(1);
    }

    OWNED HashmapEntry ** newBuckets = ZEROS(newCapacity * sizeof(HashmapEntry*));
    OWNED HashmapEntry ** oldBuckets = hm->Buckets;

    for (u64 i = 0; i < oldCapacity; i++)
    {
        HashmapEntry * bucket = oldBuckets[i];
        while (bucket)
        {
            OWNED HashmapEntry * entry = bucket;
            bucket                     = bucket->Next;
            entry->Next                = NIL;

            u64 idx = fnv1a_hash_(entry->Key) % newCapacity;

            hm_ins_helper_(newBuckets, idx, entry);
        }
    }

    XFREE(oldBuckets);
    hm->Buckets  = newBuckets;
    hm->Capacity = newCapacity;

    return RESULT_SUCCEED(0);
}

static OWNED HashmapEntry * mk_hme_(BORROWED char * key, arch val)
{
    OWNED HashmapEntry * hme = NEW(sizeof(HashmapEntry));
    hme->Key                 = strdup_safe(key);
    hme->Val                 = val;
    hme->Next                = NIL;
    return hme;
}

static COPIED void * hme_dispose_(OWNED void * arg, dispose_fn * cleanup)
{
    if (!arg)
    {
        return NIL;
    }

    OWNED HashmapEntry * hme = CAST(arg, HashmapEntry*);

    XFREE(hme->Key);
    if (cleanup)
    {
        cleanup(CAST(hme->Val, void*));
    }

    return dispose(hme);
}

static COPIED void * hme_dispose_recursive_(OWNED void * arg, dispose_fn * cleanup)
{
    if (!arg)
    {
        return NIL;
    }

    OWNED HashmapEntry * hme = CAST(arg, HashmapEntry*);

    while (hme->Next)
    {
        hme_dispose_recursive_(hme->Next, cleanup);
    }

    XFREE(hme->Key);
    if (cleanup)
    {
        cleanup(CAST(hme->Val, void*));
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
        hme_dispose_recursive_(hm->Buckets[i], cleanup);
    }
    XFREE(hm->Buckets);

    return dispose(hm);
}
