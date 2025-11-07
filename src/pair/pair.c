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
}

arch pair_fst(BORROWED Pair * pair)
{
}

arch pair_snd(BORROWED Pair * pair)
{
}

COPIED void * pair_dispose(OWNED void * arg)
{
}
