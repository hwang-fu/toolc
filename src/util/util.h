#pragma once

#include <hwangfu/generic.h>
#include <hwangfu/memory.h>

/**
 * @since       09.11.2025
 * @author      Junzhe
 * @modified    09.11.2025
 */
u64 GreatestCommonDivisor(u64 a, u64 b);

/**
 * @since       09.11.2025
 * @author      Junzhe
 * @modified    09.11.2025
 */
u64 LeastCommonMultiple(u64 a, u64 b);

/**
 * @since       09.11.2025
 * @author      Junzhe
 * @modified    09.11.2025
 */
OWNED bool * SieveEratosthenes(u64 upto);
