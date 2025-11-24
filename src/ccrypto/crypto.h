#pragma once

#include <stdlib.h>
#include <string.h>

#include <hwangfu/generic.h>
#include <hwangfu/memory.h>
#include <hwangfu/assertion.h>
#include <hwangfu/cstr.h>

typedef struct SHA256 SHA256;

/**
 * @since       24.11.2025
 * @author      Junzhe
 * @modified    24.11.2025
 */
struct SHA256
{
    u8 Digest[32];
};

/**
 * @since       24.11.2025
 * @author      Junzhe
 * @modified    24.11.2025
 */
OWNED SHA256 * mk_sha256(BORROWED void * body, u64 bytes);

/**
 * @since       24.11.2025
 * @author      Junzhe
 * @modified    24.11.2025
 */
OWNED char * sha256_cstring(BORROWED SHA256 * h);

/**
 * @since       24.11.2025
 * @author      Junzhe
 * @modified    24.11.2025
 */
OWNED char * sha256_cstring_owned(OWNED SHA256 * h);

/**
 * @since       24.11.2025
 * @author      Junzhe
 * @modified    24.11.2025
 */
OWNED char * sha256_display(FILE * stream, BORROWED SHA256 * h);
