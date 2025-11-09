#include "util.h"

u64 GreatestCommonDivisor(u64 a, u64 b)
{
    if (EQ(a, 0))
    {
        return b;
    }

    if (EQ(b, 0))
    {
        return a;
    }

    if (a < b)
    {
        return GreatestCommonDivisor(b, a);
    }

    while (NEQ(b, 0))
    {
        u64 r = a % b;
        a = b;
        b = r;
    }

    return a;
}

u64 LeastCommonMultiple(u64 a, u64 b)
{
    if (EQ(a, 0) || EQ(b, 0))
    {
        return 0;
    }

    u64 gcd = GreatestCommonDivisor(a, b);

    return a / gcd * b;
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
        if (!isPrime[p])
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
