#include "dequeue.h"

OWNED Dequeue * dq_init(OWNED Dequeue * dq, u64 capacity, dispose_fn * cleanup)
{
    if (!dq)
    {
        dq = NEW(sizeof(Dequeue));
    }

    if (EQ(capacity, 0))
    {
        WARNINGF("%s(): Dequeue initialized capacity is zero, default to %lu.", __func__, DEQUEUE_DEFAULT_CAPACITY);
        capacity = DEQUEUE_DEFAULT_CAPACITY;
    }

    dq->Capacity      = capacity;
    dq->Size          = 0;
    dq->Elements      = NEW(capacity * sizeof(arch));
    dq->Dispose       = cleanup;

    return dq;
}

OWNED Dequeue * mk_dq(int mode, ...)
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
    return dq_init(NIL, capacity, cleanup);
}

OWNED Dequeue * mk_dq2(u64 capacity, dispose_fn * cleanup)
{
    return dq_init(
        NEW(sizeof(Dequeue)),
        capacity,
        cleanup
    );
}

arch dq_at(BORROWED Dequeue * dq, u64 idx)
{
    OWNED Result * result = dq_try_at(dq, idx);
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
            PANIC("%s(): NIL dq argument.", __func__);
        } break;

        case 1:
        {
            PANIC("%s(): the dequeue size is %lu but trying to access element at index %lu..", __func__, dq->Size, idx);
        } break;

        default:
        {
            PANIC("%s(): Unknown error.", __func__);
        } break;
    }
}

void _dq_pushfront(BORROWED Dequeue * dq, arch data)
{
    OWNED Result * result = _dq_try_pushfront(dq, data);
    if (RESULT_GOOD(result))
    {
        result_dispose(result);
        goto _dq_pushfront_exit_;
    }

    u64 errcode = (u64) result->Failure;
    result_dispose(result);
    switch (errcode)
    {
        case 0:
        {
            PANIC("%s(): NIL dq argument.", __func__);
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

_dq_pushfront_exit_:
}

void _dq_pushback(BORROWED Dequeue * dq, arch data)
{
    OWNED Result * result = _dq_try_pushback(dq, data);
    if (RESULT_GOOD(result))
    {
        result_dispose(result);
        goto _dq_pushback_exit_;
    }

    u64 errcode = (u64) result->Failure;
    result_dispose(result);
    switch (errcode)
    {
        case 0:
        {
            PANIC("%s(): NIL dq argument.", __func__);
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

_dq_pushback_exit_:
}

arch dq_front(BORROWED Dequeue * dq)
{
    OWNED Result * result = dq_try_front(dq);
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
            PANIC("%s(): NIL dq argument.", __func__);
        } break;

        case 1:
        {
            PANIC("%s(): the dequeue is still empty.", __func__);
        } break;

        default:
        {
            PANIC("%s(): Unknown error.", __func__);
        } break;
    }
}

arch dq_back(BORROWED Dequeue * dq)
{
    OWNED Result * result = dq_try_back(dq);
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
            PANIC("%s(): NIL dq argument.", __func__);
        } break;

        case 1:
        {
            PANIC("%s(): the dequeue is still empty.", __func__);
        } break;

        default:
        {
            PANIC("%s(): Unknown error.", __func__);
        } break;
    }
}

arch dq_popfront(BORROWED Dequeue * dq)
{
    OWNED Result * result = dq_try_popfront(dq);
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
            PANIC("%s(): NIL dq argument.", __func__);
        } break;

        case 1:
        {
            PANIC("%s(): the dequeue is still empty.", __func__);
        } break;

        default:
        {
            PANIC("%s(): Unknown error.", __func__);
        } break;
    }
}

arch dq_popback(BORROWED Dequeue * dq)
{
    OWNED Result * result = dq_try_popback(dq);
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
            PANIC("%s(): NIL dq argument.", __func__);
        } break;

        case 1:
        {
            PANIC("%s(): the dequeue is still empty.", __func__);
        } break;

        default:
        {
            PANIC("%s(): Unknown error.", __func__);
        } break;
    }
}

OWNED Result * dq_try_at(BORROWED Dequeue * dq, u64 idx)
{
    if (!dq)
    {
        return RESULT_FAIL(0);
    }

    if (dq->Size <= idx)
    {
        return RESULT_FAIL(1);
    }

    return RESULT_SUCCEED(dq->Elements[idx]);
}

OWNED Result * _dq_try_pushfront(BORROWED Dequeue * dq, arch data)
{
    if (!dq)
    {
        return RESULT_FAIL(0);
    }

    u64 capacity = dq->Capacity;
    u64 size     = dq->Size;
    if (WATERMARK(size, capacity) >= WATERMARK_HIGH)
    {
        do
        {
            capacity += 1;
            capacity *= 2;
        } while (WATERMARK(size, capacity) >= WATERMARK_LOW);

        if (!dq_try_fit(dq, capacity))
        {
            return RESULT_FAIL(1);
        }
    }

    memmove(dq->Elements + 1, dq->Elements + 0, dq->Size++ * sizeof(arch));
    dq->Elements[0] = data;

    return RESULT_SUCCEED(0);
}

OWNED Result * _dq_try_pushback(BORROWED Dequeue * dq, arch data)
{
    if (!dq)
    {
        return RESULT_FAIL(0);
    }

    u64 capacity = dq->Capacity;
    u64 size     = dq->Size;
    if (WATERMARK(size, capacity) >= WATERMARK_HIGH)
    {
        do
        {
            capacity += 1;
            capacity *= 2;
        } while (WATERMARK(size, capacity) >= WATERMARK_LOW);

        if (!dq_try_fit(dq, capacity))
        {
            return RESULT_FAIL(1);
        }
    }

    dq->Elements[dq->Size++] = data;

    return RESULT_SUCCEED(0);
}

OWNED Result * dq_try_front(BORROWED Dequeue * dq)
{
    if (!dq)
    {
        return RESULT_FAIL(0);
    }

    if (EQ(dq->Size, 0))
    {
        return RESULT_FAIL(1);
    }

    return RESULT_SUCCEED(dq->Elements[0]);
}

OWNED Result * dq_try_back(BORROWED Dequeue * dq)
{
    if (!dq)
    {
        return RESULT_FAIL(0);
    }

    u64 size = dq->Size;
    if (EQ(size, 0))
    {
        return RESULT_FAIL(1);
    }

    return RESULT_SUCCEED(dq->Elements[size-1]);
}

OWNED Result * dq_try_popfront(BORROWED Dequeue * dq)
{
    if (!dq)
    {
        return RESULT_FAIL(0);
    }

    if (EQ(dq->Size, 0))
    {
        return RESULT_FAIL(1);
    }

    arch data = dq->Elements[0];

    memmove(dq->Elements + 0, dq->Elements + 1, (--dq->Size) * sizeof(arch));

    return RESULT_SUCCEED(data);
}

OWNED Result * dq_try_popback(BORROWED Dequeue * dq)
{
    if (!dq)
    {
        return RESULT_FAIL(0);
    }

    if (EQ(dq->Size, 0))
    {
        return RESULT_FAIL(1);
    }

    return RESULT_SUCCEED(dq->Elements[--dq->Size]);
}

u64 dq_get_size(BORROWED Dequeue * dq)
{
    SCP(dq);
    return dq->Size;
}

OWNED Result * dq_try_get_size(BORROWED Dequeue * dq)
{
    if (!dq)
    {
        return RESULT_FAIL(0);
    }

    return RESULT_SUCCEED(dq->Size);
}

u64 dq_get_capacity(BORROWED Dequeue * dq)
{
    SCP(dq);
    return dq->Capacity;
}

OWNED Result * dq_try_get_capacity(BORROWED Dequeue * dq)
{
    if (!dq)
    {
        return RESULT_FAIL(0);
    }

    return RESULT_SUCCEED(dq->Capacity);
}

void dq_fit(BORROWED Dequeue * dq, u64 newCapacity)
{
    OWNED Result * result = dq_try_fit(dq, newCapacity);
    if (RESULT_GOOD(result))
    {
        result_dispose(result);
        goto dq_fit_exit_;
    }

    u64 errcode = (u64) result->Failure;
    result_dispose(result);
    switch (errcode)
    {
        case 0:
        {
            PANIC("%s(): NIL dq argument.", __func__);
        } break;

        case 1:
        {
            PANIC(
                "%s(): the old capacity is %lu greater than or equal to the new capacity is %lu.",
                __func__, dq->Capacity, newCapacity);
        } break;

        default:
        {
            PANIC("%s(): Unknown error.", __func__);
        } break;
    }

dq_fit_exit_:
}

OWNED Result * dq_try_fit(BORROWED Dequeue * dq, u64 newCapacity)
{
    if (!dq)
    {
        return RESULT_FAIL(0);
    }

    u64 oldCapacity = dq->Capacity;
    if (oldCapacity >= newCapacity)
    {
        return RESULT_FAIL(1);
    }

    dq->Elements = realloc_safe(dq, newCapacity);
    dq->Capacity = newCapacity;

    return RESULT_SUCCEED(0);
}

bool dq_is_empty(BORROWED Dequeue * dq)
{
    if (!dq)
    {
        return False;
    }

    return EQ(dq->Size, 0);
}

void dq_apply_at(BORROWED Dequeue * dq, u64 idx, dq_apply_fn * apply)
{
    OWNED Result * result = dq_try_apply_at(dq, idx, apply);
    if (RESULT_GOOD(result))
    {
        result_dispose(result);
        goto dq_apply_exit_;
    }

    u64 errcode = (u64) result->Failure;
    result_dispose(result);
    switch (errcode)
    {
        case 0:
        {
            PANIC("%s(): NIL dq argument.", __func__);
        } break;

        case 1:
        {
            PANIC("%s(): idx %lu is out of range [0, %lu].", __func__, idx, dq->Size-1);
        } break;

        case 2:
        {
            PANIC("%s(): NIL apply function.", __func__);
        } break;

        default:
        {
            PANIC("%s(): Unknown error.", __func__);
        } break;
    }

dq_apply_exit_:
}

OWNED Result * dq_try_apply_at(BORROWED Dequeue * dq, u64 idx, dq_apply_fn * apply)
{
    if (!dq)
    {
        return RESULT_FAIL(0);
    }

    if (dq->Size <= idx)
    {
        return RESULT_FAIL(1);
    }

    if (!apply)
    {
        return RESULT_FAIL(2);
    }

    dq->Elements[idx] = apply(dq->Elements[idx]);

    return RESULT_SUCCEED(0);
}

COPIED void * dq_dispose(OWNED void * arg)
{
    if (!arg)
    {
        return NIL;
    }

    OWNED Dequeue * dq = CAST(arg, Dequeue*);

    u64 size = dq->Size;
    if (dq->Dispose)
    {
        dispose_fn * cleanup = dq->Dispose;
        for (u64 i = 0; i < size; i++)
        {
            cleanup(CAST(dq->Elements[i], void*));
        }
    }
    XFREE(dq->Elements);

    return dispose(dq);
}
