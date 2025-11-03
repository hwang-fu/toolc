#include "dequeue.h"

OWNED Dequeue * dq_init(OWNED Dequeue * dq, u64 capacity, dispose_fn * cleanup)
{
    SCP(dq);
    if (dq->IsInitialized)
    {
        PANIC("%s(): Dequeue is already initialized.", __func__);
    }
    if (EQ(capacity, 0))
    {
        PANIC("%s(): Dequeue initialized capacity is zero..", __func__);
    }

    dq->IsInitialized = True;
    dq->Capacity      = capacity;
    dq->Size          = 0;
    dq->Data          = NEW(capacity * sizeof(arch));
    dq->Dispose       = cleanup;

    return dq;
}

OWNED Dequeue * mk_dq()
{
    OWNED Dequeue * dq = NEW(sizeof(Dequeue));
    return dq;
}

OWNED Dequeue * mk_dq(dispose_fn * cleanup)
{
    return mk_dq2(DEQUEUE_DEFAULT_CAPACITY, cleanup);
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
    SCP(dq);
    ASSERT_EXPR(dq->Size > idx);
    return dq->Data[idx];
}

void dq_pushfront(BORROWED Dequeue * dq, arch value)
{
    SCP(dq);
}

void dq_pushback(BORROWED Dequeue * dq, arch value)
{
    SCP(dq);
}

arch dq_front(BORROWED Dequeue * dq)
{
    SCP(dq);
}

arch dq_back(BORROWED Dequeue * dq)
{
    SCP(dq);
}

arch dq_popfront(BORROWED Dequeue * dq)
{
    SCP(dq);
}

arch dq_popback(BORROWED Dequeue * dq)
{
    SCP(dq);
}

OWNED Result * dq_try_at(BORROWED Dequeue * dq, u64 idx)
{
    if (!dq)
    {
        return mk_result(RESULT_FAILURE, 0);
    }

    if (dq->Size <= idx)
    {
        return mk_result(RESULT_FAILURE, 1);
    }

    return mk_result(RESULT_SUCCESS, dq->Data[idx]);
}

bool dq_try_pushfront(BORROWED Dequeue * dq, arch value)
{
}

bool dq_try_pushback(BORROWED Dequeue * dq, arch value)
{
}

OWNED Result * dq_try_front(BORROWED Dequeue * dq)
{
}

OWNED Result * dq_try_back(BORROWED Dequeue * dq)
{
}

OWNED Result * dq_try_popfront(BORROWED Dequeue * dq)
{
}

OWNED Result * dq_try_popback(BORROWED Dequeue * dq)
{
}

u64 dq_get_size(BORROWED Dequeue * dq)
{
}

OWNED Result * dq_try_get_size(BORROWED Dequeue * dq)
{
}

u64 dq_get_capacity(BORROWED Dequeue * dq)
{
}

OWNED Result * dq_try_get_capacity(BORROWED Dequeue * dq)
{
}

void dq_fit(BORROWED Dequeue * dq, u64 newCapacity)
{
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
        disose_fn * cleanup = dq->Dispose;
        for (u64 i = 0; i < size; i++)
        {
            cleanup(CAST(dq->Data[i], void*));
        }
    }
    XFREE(dq->Data);

    return dispose(dq);
}
