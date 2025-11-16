#include "vector.h"

/**
 * @since       16.11.2025
 * @author      Junzhe
 * @modified    16.11.2025
 */
struct VectorItem
{
    arch         Value;
    dispose_fn * Dispose;
};



static OWNED VectorItem * mk_vector_item_(arch value, dispose_fn * cleanup);
static COPIED void * vector_item_dispose_(OWNED void * arg);



static OWNED VectorItem * mk_vector_item_(arch value, dispose_fn * cleanup)
{
    OWNED VectorItem * item = NEW(sizeof(VectorItem));
    item->Value             = value;
    item->Dispose           = cleanup;
    return item;
}

static COPIED void * vector_item_dispose_(OWNED void * arg)
{
    if (!arg)
    {
        return NIL;
    }

    OWNED VectorItem * item = CAST(arg, VectorItem*);
    if (item->Dispose) {
        item->Dispose(CAST(item->Value, void*));
    }
    return dispose(item);
}



OWNED Vector * vector_init(OWNED Vector * vec, u64 capacity)
{
    if (!vec)
    {
        vec = NEW(sizeof(Vector));
    }

    vec->Size     = 0;
    vec->Capacity = capacity;
    vec->Items    = NEW(capacity * sizeof(VectorItem*));

    return vec;
}

/**
 * Possible overloads:
 * @li OWNED Vector * mk_vector(0)
 * @li OWNED Vector * mk_vector(1, u64 capacity)
 */
OWNED Vector * mk_vector(int mode, ...)
{
    va_list ap;
    va_start(ap, mode);

    u64          capacity = VECTOR_DEFAULT_CAPACITY;
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

        default:
        {
            PANIC("%s(): unkown mode %d", mode);
        } break;
    }

    va_end(ap);
    return vector_init(NIL, capacity);
}

arch vector_at(BORROWED Vector * vec, u64 idx)
{
    OWNED Result * result = vector_try_at(vec, idx);
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
            PANIC("%s(): NIL vector argument.", __func__);
        } break;

        case 1:
        {
            PANIC("%s(): the vector size is %lu but trying to access element at index %lu..", __func__, vec->Size, idx);
        } break;

        default:
        {
            PANIC("%s(): Unknown error.", __func__);
        } break;
    }
}

arch vector_front(BORROWED Vector * vec)
{
    OWNED Result * result = vector_try_front(vec);
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
            PANIC("%s(): NIL vector argument.", __func__);
        } break;

        case 1:
        {
            PANIC("%s(): the vector is still empty.", __func__);
        } break;

        default:
        {
            PANIC("%s(): Unknown error.", __func__);
        } break;
    }
}

arch vector_back(BORROWED Vector * vec)
{
    OWNED Result * result = vector_try_back(vec);
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
            PANIC("%s(): NIL vector argument.", __func__);
        } break;

        case 1:
        {
            PANIC("%s(): the vector is still empty.", __func__);
        } break;

        default:
        {
            PANIC("%s(): Unknown error.", __func__);
        } break;
    }
}

arch vector_popfront(BORROWED Vector * vec)
{
    OWNED Result * result = vector_try_popfront(vec);
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
            PANIC("%s(): NIL vector argument.", __func__);
        } break;

        case 1:
        {
            PANIC("%s(): the vector is still empty.", __func__);
        } break;

        default:
        {
            PANIC("%s(): Unknown error.", __func__);
        } break;
    }
}

arch vector_popback(BORROWED Vector * vec)
{
    OWNED Result * result = vector_try_popback(vec);
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
            PANIC("%s(): NIL vector argument.", __func__);
        } break;

        case 1:
        {
            PANIC("%s(): the vector is still empty.", __func__);
        } break;

        default:
        {
            PANIC("%s(): Unknown error.", __func__);
        } break;
    }
}

OWNED Result * vector_try_at(BORROWED Vector * vec, u64 idx)
{
    if (!vec)
    {
        return RESULT_FAIL(0);
    }

    if (vec->Size <= idx)
    {
        return RESULT_FAIL(1);
    }

    return RESULT_SUCCEED(vec->Items[idx]->Value);
}

OWNED Result * vector_try_front(BORROWED Vector * vec)
{
    if (!vec)
    {
        return RESULT_FAIL(0);
    }

    if (EQ(vec->Size, 0))
    {
        return RESULT_FAIL(1);
    }

    return RESULT_SUCCEED(vec->Items[0]->Value);
}

OWNED Result * vector_try_back(BORROWED Vector * vec)
{
    if (!vec)
    {
        return RESULT_FAIL(0);
    }

    u64 size = vec->Size;
    if (EQ(size, 0))
    {
        return RESULT_FAIL(1);
    }

    return RESULT_SUCCEED(vec->Items[size-1]->Value);
}

OWNED Result * vector_try_popfront(BORROWED Vector * vec)
{
    if (!vec)
    {
        return RESULT_FAIL(0);
    }

    if (EQ(vec->Size, 0))
    {
        return RESULT_FAIL(1);
    }

    VectorItem * item = vec->Items[0];
    arch data = item->Value;
    dispose(item);

    memmove(vec->Items + 0, vec->Items + 1, (--vec->Size) * sizeof(VectorItem*));

    return RESULT_SUCCEED(data);
}

OWNED Result * vector_try_popback(BORROWED Vector * vec)
{
    if (!vec)
    {
        return RESULT_FAIL(0);
    }

    if (EQ(vec->Size, 0))
    {
        return RESULT_FAIL(1);
    }

    VectorItem * item = vec->Items[--vec->Size];
    arch data = item->Value;
    dispose(item);

    return RESULT_SUCCEED(data);
}

void _vector_pushfront(BORROWED Vector * vec, arch value, dispose_fn * cleanup)
{
    OWNED Result * result = _vector_try_pushfront(vec, value, cleanup);
    if (RESULT_GOOD(result))
    {
        result_dispose(result);
        goto _vector_pushfront_exit_;
    }

    u64 errcode = (u64) result->Failure;
    result_dispose(result);
    switch (errcode)
    {
        case 0:
        {
            PANIC("%s(): NIL vector argument.", __func__);
        } break;

        case 1:
        {
            PANIC("%s(): failed to grow the capacity.", __func__);
        } break;

        default:
        {
            PANIC("%s(): Unknown error.", __func__);
        } break;
    }

_vector_pushfront_exit_:
}

void _vector_pushback(BORROWED Vector * vec, arch value, dispose_fn * cleanup)
{
    OWNED Result * result = _vector_try_pushback(vec, value, cleanup);
    if (RESULT_GOOD(result))
    {
        result_dispose(result);
        goto _vector_pushback_exit_;
    }

    u64 errcode = (u64) result->Failure;
    result_dispose(result);
    switch (errcode)
    {
        case 0:
        {
            PANIC("%s(): NIL vector argument.", __func__);
        } break;

        case 1:
        {
            PANIC("%s(): failed to grow the capacity.", __func__);
        } break;

        default:
        {
            PANIC("%s(): Unknown error.", __func__);
        } break;
    }

_vector_pushback_exit_:
}

OWNED Result * _vector_try_pushfront(BORROWED Vector * vec, arch value, dispose_fn * cleanup)
{
    if (!vec)
    {
        return RESULT_FAIL(0);
    }

    u64 capacity = vec->Capacity;
    u64 size     = vec->Size;
    if (WATERMARK(size, capacity) >= WATERMARK_HIGH)
    {
        do
        {
            capacity += 1;
            capacity *= 2;
        } while (WATERMARK(size, capacity) >= WATERMARK_LOW);

        if (!vector_try_fit(vec, capacity))
        {
            return RESULT_FAIL(1);
        }
    }

    memmove(vec->Items + 1, vec->Items + 0, vec->Size++ * sizeof(VectorItem*));
    vec->Items[0] = mk_vector_item_(value, cleanup);

    return RESULT_SUCCEED(0);
}

OWNED Result * _vector_try_pushback(BORROWED Vector * vec, arch value, dispose_fn * cleanup)
{
    if (!vec)
    {
        return RESULT_FAIL(0);
    }

    u64 capacity = vec->Capacity;
    u64 size     = vec->Size;
    if (WATERMARK(size, capacity) >= WATERMARK_HIGH)
    {
        do
        {
            capacity += 1;
            capacity *= 2;
        } while (WATERMARK(size, capacity) >= WATERMARK_LOW);

        if (!vector_try_fit(vec, capacity))
        {
            return RESULT_FAIL(1);
        }
    }

    vec->Items[vec->Size++] = mk_vector_item_(value, cleanup);

    return RESULT_SUCCEED(0);
}

void vector_fit(BORROWED Vector * vec, u64 newCapacity)
{
    OWNED Result * result = vector_try_fit(vec, newCapacity);
    if (RESULT_GOOD(result))
    {
        result_dispose(result);
        goto vec_fit_exit_;
    }

    u64 errcode = (u64) result->Failure;
    result_dispose(result);
    switch (errcode)
    {
        case 0:
        {
            PANIC("%s(): NIL vector argument.", __func__);
        } break;

        case 1:
        {
            PANIC(
                "%s(): the old capacity is %lu greater than or equal to the new capacity is %lu.",
                __func__, vec->Capacity, newCapacity);
        } break;

        default:
        {
            PANIC("%s(): Unknown error.", __func__);
        } break;
    }

vec_fit_exit_:
}

OWNED Result * vector_try_fit(BORROWED Vector * vec, u64 newCapacity)
{
    if (!vec)
    {
        return RESULT_FAIL(0);
    }

    u64 oldCapacity = vec->Capacity;
    if (oldCapacity >= newCapacity)
    {
        return RESULT_FAIL(1);
    }

    vec->Items    = realloc_safe(vec->Items, newCapacity * sizeof(VectorItem*));
    vec->Capacity = newCapacity;

    return RESULT_SUCCEED(0);
}

u64 vector_get_size(BORROWED Vector * vec)
{
    SCP(vec);
    return vec->Size;
}

OWNED Result * vector_try_get_size(BORROWED Vector * vec)
{
    if (!vec)
    {
        return RESULT_FAIL(0);
    }

    return RESULT_SUCCEED(vec->Size);
}

u64 vector_get_capacity(BORROWED Vector * vec)
{
    SCP(vec);
    return vec->Capacity;
}

OWNED Result * vector_try_get_capacity(BORROWED Vector * vec)
{
    if (!vec)
    {
        return RESULT_FAIL(0);
    }

    return RESULT_SUCCEED(vec->Capacity);
}

bool vector_is_empty(BORROWED Vector * vec)
{
    if (!vec)
    {
        return False;
    }
    return EQ(vec->Size, 0);
}

COPIED void * vector_dispose(OWNED void * arg)
{
    if (!arg)
    {
        return NIL;
    }

    OWNED Vector * vec = CAST(arg, Vector*);

    u64 size = vec->Size;
    for (u64 i = 0; i < size; i++)
    {
        vector_item_dispose_(vec->Items[i]);
    }

    dispose(vec->Items);
    return dispose(vec);
}
