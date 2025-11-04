#include "dequeue.h"

OWNED Dequeue * dq_init(OWNED Dequeue * dq, u64 capacity, dispose_fn * cleanup)
{
    SCP(dq);
    if (EQ(capacity, 0))
    {
        WARNINGF("%s(): Dequeue initialized capacity is zero, default to %lu.", __func__, DEQUEUE_DEFAULT_CAPACITY);
        capacity = DEQUEUE_DEFAULT_CAPACITY;
    }

    dq->Capacity      = capacity;
    dq->Size          = 0;
    dq->Elements          = NEW(capacity * sizeof(arch));
    dq->Dispose       = cleanup;

    return dq;
}

OWNED Dequeue * mk_dq()
{
    return NEW(sizeof(Dequeue));
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
            PANIC("%s(): NIL argument.", __func__);
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

void dq_pushfront(BORROWED Dequeue * dq, arch data)
{
    OWNED Result * result = dq_try_pushfront(dq, data);
    if (RESULT_GOOD(result))
    {
        result_dispose(result);
        goto dq_pushfront_exit_;
    }

    u64 errcode = (u64) result->Failure;
    result_dispose(result);
    switch (errcode)
    {
        case 0:
        {
            PANIC("%s(): NIL argument.", __func__);
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

dq_pushfront_exit_:
}

void dq_pushback(BORROWED Dequeue * dq, arch data)
{
    OWNED Result * result = dq_try_pushback(dq, data);
    if (RESULT_GOOD(result))
    {
        result_dispose(result);
        goto dq_pushback_exit_;
    }

    u64 errcode = (u64) result->Failure;
    result_dispose(result);
    switch (errcode)
    {
        case 0:
        {
            PANIC("%s(): NIL argument.", __func__);
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

dq_pushback_exit_:
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
            PANIC("%s(): NIL argument.", __func__);
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
            PANIC("%s(): NIL argument.", __func__);
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
            PANIC("%s(): NIL argument.", __func__);
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
            PANIC("%s(): NIL argument.", __func__);
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

    return mk_result(RESULT_SUCCESS, dq->Elements[idx]);
}

OWNED Result * dq_try_pushfront(BORROWED Dequeue * dq, arch data)
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

OWNED Result * dq_try_pushback(BORROWED Dequeue * dq, arch data)
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

    return RESULT_SUCCEED(CAST(dq->Elements[0], arch));
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

    return RESULT_SUCCEED(CAST(dq->Elements[size-1], arch));
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
}

OWNED Result * dq_try_get_size(BORROWED Dequeue * dq)
{
    if (!dq)
    {
        return RESULT_FAIL(0);
    }
}

u64 dq_get_capacity(BORROWED Dequeue * dq)
{
    SCP(dq);
}

OWNED Result * dq_try_get_capacity(BORROWED Dequeue * dq)
{
    if (!dq)
    {
        return RESULT_FAIL(0);
    }
}

void dq_fit(BORROWED Dequeue * dq, u64 newCapacity)
{
    SCP(dq);
}

bool dq_try_fit(BORROWED Dequeue * dq, u64 newCapacity)
{
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
}

bool dq_try_apply_at(BORROWED Dequeue * dq, u64 idx, dq_apply_fn * apply)
{
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
