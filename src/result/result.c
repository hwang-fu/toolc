#include "result.h"

OWNED Result * result_init_(OWNED Result * result, TResult tag, arch value)
{
    if (!result)
    {
        result = NEW(sizeof(Result));
    }

    switch (tag)
    {
        case RESULT_SUCCESS:
        {
            result->Success = value;
        } break;

        case RESULT_FAILURE:
        {
            result->Failure = value;
        } break;

        default:
        {
            PANIC("%s(): Unknown TResult value %d", __func__, tag);
        } break;
    }
    result->Tag = tag;

    return result;
}

OWNED Result * mk_result(TResult tag, arch value)
{
    return result_init_(NIL, tag, value);
}

OWNED Result * mk_result_success(arch success)
{
    return mk_result(RESULT_SUCCESS, success);
}

OWNED Result * mk_result_failure(arch failure)
{
    return mk_result(RESULT_FAILURE, failure);
}

arch result_unwrap(BORROWED Result * result, result_callback_fn * onerr)
{
    SCP(result);
    switch (result->Tag)
    {
        case RESULT_SUCCESS:
        {
            return result->Success;
        } break;

        case RESULT_FAILURE:
        {
            if (!onerr)
            {
                PANIC("%s(): Result is failed with error code %lu", __func__, result->Failure);
            }
            onerr(result->Failure);
        } break;

        default:
        {
            PANIC("%s(): Unknown TResult value %d", __func__, result->Tag);
        } break;
    }
}

arch result_unwrap_else(BORROWED Result * result, arch alternative)
{
    SCP(result);
    switch (result->Tag)
    {
        case RESULT_SUCCESS:
        {
            return result->Success;
        } break;

        case RESULT_FAILURE:
        {
            return alternative;
        } break;

        default:
        {
            PANIC("%s(): Unknown TResult value %d", __func__, result->Tag);
        } break;
    }
}

arch result_unwrap_owned(OWNED Result * result, result_callback_fn * onerr)
{
    SCP(result);
    arch value;
    switch (result->Tag)
    {
        case RESULT_SUCCESS:
        {
            value = result->Success;
        } break;

        case RESULT_FAILURE:
        {
            if (!onerr)
            {
                PANIC("%s(): Result is failed with error code %lu", __func__, result->Failure);
            }
            onerr(result->Failure);
        } break;

        default:
        {
            PANIC("%s(): Unknown TResult value %d", __func__, result->Tag);
        } break;
    }

    result_dispose(result);

    return value;
}

arch result_unwrap_else_owned(OWNED Result * result, arch alternative)
{
    SCP(result);
    arch value;
    switch (result->Tag)
    {
        case RESULT_SUCCESS:
        {
            value = result->Success;
        } break;

        case RESULT_FAILURE:
        {
            value = alternative;
        } break;

        default:
        {
            PANIC("%s(): Unknown TResult value %d", __func__, result->Tag);
        } break;
    }

    result_dispose(result);

    return value;
}

COPIED void * result_dispose(OWNED void * arg)
{
    if (!arg)
    {
        return NIL;
    }
    OWNED Result * res = CAST(arg, Result*);
    return dispose(res);
}
