#include "result.h"

void result_init_(BORROWED Result * result, TResult tag, arch value)
{
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

    result->Tag         = tag;
    result->IsUnwrapped = True;
}

OWNED Result * mk_result(TResult tag, arch value)
{
    OWNED Result * res = NEW(sizeof(Result));
    result_init_(res, tag, value);
    return res;
}

OWNED Result * mk_result_success(arch success)
{
    return mk_result(RESULT_SUCCESS, success);
}

OWNED Result * mk_result_failure(arch failure)
{
    return mk_result(RESULT_FAILURE, failure);
}

arch result_unwrap(BORROWED Result * result)
{
    SCP(result);
    if (result->IsUnwrapped)
    {
        PANIC("%s(): Result is already unwrapped.", __func__);
    }

    switch (result->Tag)
    {
        case RESULT_SUCCESS:
        {
            return result->Success;
        } break;

        case RESULT_FAILURE:
        {
            PANIC("%s(): Result is failed with error message \"%s\"", __func__, CAST(result->Failure, char*));
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
    if (result->IsUnwrapped)
    {
        PANIC("%s(): Result is already unwrapped.", __func__);
    }

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

arch result_unwrap_owned(OWNED Result * result)
{
    SCP(result);
    if (result->IsUnwrapped)
    {
        PANIC("%s(): Result is already unwrapped.", __func__);
    }

    arch value;
    switch (result->Tag)
    {
        case RESULT_SUCCESS:
        {
            value = result->Success;
        } break;

        case RESULT_FAILURE:
        {
            PANIC("%s(): Result is failed with error message \"%s\"", __func__, CAST(result->Failure, char*));
        } break;

        default:
        {
            PANIC("%s(): Unknown TResult value %d", __func__, result->Tag);
        } break;
    }

    result->IsUnwrapped = True;
    result_dispose(result);

    return value;
}

arch result_unwrap_else_owned(OWNED Result * result, arch alternative)
{
    SCP(result);
    if (result->IsUnwrapped)
    {
        PANIC("%s(): Result is already unwrapped.", __func__);
    }

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

    result->IsUnwrapped = True;
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
    if (!res->IsUnwrapped)
    {
        PANIC("%s(): Result is not unwrapped before disposal.", __func__);
    }
    return dispose(res);
}
