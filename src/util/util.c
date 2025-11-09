#include "util.h"

u64 GreatestCommonDivisor(u64 a, u64 b)
{
}

u64 LeastCommonMultiple(u64 a, u64 b)
{
}

OWNED bool * SieveEratosthenes(u64 upto)
{
    OWNED bool * isPrime = NEW((upto + 1) * sizeof(bool));
    for (u64 i = 0; i <= upto; i++)
    {
        isPrime[i] = True;
    }

    for (u64 p = 2; p * p <= upto; p++)
    {
        if (!isPrime[i])
        {
            continue;
        }

        for (u64 multiple = p * p; multiple <= upto; multiple += p)
        {
            isPrime[multiple] = False;
        }
    }

    return isPrime;
}
