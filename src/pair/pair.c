#include "pair.h"

OWNED Pair * pair_init(OWNED Pair * pair, arch fst, arch snd, dispose_fn * cleanup1, dispose_fn * cleanup2)
{
    if (!pair)
    {
        pair = NEW(sizeof(Pair));
    }

    pair->First         = fst;
    pair->Second        = snd;
    pair->DisposeFirst  = cleanup1;
    pair->DisposeSecond = cleanup2;

    return pair;
}

/*
 * Possible overloads:
 * @li OWNED Pair * mk_pair(0, arch fst, arch snd)
 * @li OWNED Pair * mk_pair(1, arch fst, arch snd, dispose_fn * cleanup1, dispose_fn * cleanup2)
 * @li OWNED Pair * mk_pair(2, arch fst, arch snd, dispose_fn * cleanup1)
 * @li OWNED Pair * mk_pair(3, arch fst, arch snd, dispose_fn * cleanup2)
 */
OWNED Pair * mk_pair(int mode, ...)
{
    va_list ap;
    va_start(ap, mode);

    arch fst = 0;
    arch snd = 0;

    dispose_fn * cleanup1 = NIL;
    dispose_fn * cleanup2 = NIL;

    switch (mode)
    {
        case 0:
        {
            fst = va_arg(ap, arch);
            snd = va_arg(ap, arch);
        } break;

        case 1:
        {
            fst = va_arg(ap, arch);
            snd = va_arg(ap, arch);
            cleanup1 = va_start(ap, dispose_fn*);
            cleanup2 = va_start(ap, dispose_fn*);
        } break;

        case 2:
        {
            fst = va_arg(ap, arch);
            snd = va_arg(ap, arch);
            cleanup1 = va_start(ap, dispose_fn*);
        } break;

        case 3:
        {
            fst = va_arg(ap, arch);
            snd = va_arg(ap, arch);
            cleanup2 = va_start(ap, dispose_fn*);
        } break;

        default:
        {
            PANIC("%s(): unkown mode %d", mode);
        } break;
    }

    va_end(ap);

    return pair_init(NIL, fst, snd, cleanup1, cleanup2);
}

arch pair_fst(BORROWED Pair * pair)
{
}

arch pair_snd(BORROWED Pair * pair)
{
}

OWNED Result * pair_try_fst(BORROWED Pair * pair)
{
}

OWNED Result * pair_try_snd(BORROWED Pair * pair)
{
}

COPIED void * pair_dispose(OWNED void * arg)
{
    if (!arg)
    {
        return NIL;
    }

    OWNED Pair * pair = CAST(arg, Pair*);

    if (pair->DisposeFirst)
    {
        pair->DisposeFirst(CAST(pair->First, void*));
    }

    if (pair->DisposeSecond)
    {
        pair->DisposeSecond(CAST(pair->Second, void*));
    }

    return dispose(arg);
}
