#pragma once

#include <stdarg.h>

#include <hwangfu/generic.h>
#include <hwangfu/result.h>
#include <hwangfu/assertion.h>

#ifndef HASHMAP_DEFAULT_CAPACITY
#define HASHMAP_DEFAULT_CAPACITY (20)
#endif // HASHMAP_DEFAULT_CAPACITY

#define hm_ins(hm, key, val)               _hm_ins(hm, key, CAST(val, arch))
#define hm_ins_owned_key(hm, key, val)     _hm_ins_owned_key(hm, key, CAST(val, arch))
#define hm_try_ins(hm, key, val)           _hm_try_ins(hm, key, CAST(val, arch))
#define hm_try_ins_owned_key(hm, key, val) _hm_try_ins_owned_key(hm, key, CAST(val, arch))

typedef struct Hashmap Hashmap;
typedef struct HashmapEntry HashmapEntry;

/**
 * @since       06.11.2025
 * @author      Junzhe
 * @modified    06.11.2025
 *
 */
struct Hashmap
{
    COPIED   u64             Capacity   ;
    COPIED   u64             Size       ;
    OWNED    HashmapEntry ** Buckets    ;
    BORROWED dispose_fn    * Dispose    ;
};

/**
 * @since       06.11.2025
 * @author      Junzhe
 * @modified    06.11.2025
 *
 */
OWNED Hashmap * hm_init(OWNED Hashmap * hm, u64 capacity, dispose_fn * cleanup);

/**
 * @since       06.11.2025
 * @author      Junzhe
 * @modified    06.11.2025
 *
 */
OWNED Hashmap * mk_hm(int mode, ...);

/**
 * @since       06.11.2025
 * @author      Junzhe
 * @modified    06.11.2025
 *
 */
void _hm_ins(BORROWED Hashmap * hm, BORROWED const char * key, arch val);

/**
 * @since       06.11.2025
 * @author      Junzhe
 * @modified    06.11.2025
 *
 */
void _hm_ins_owned_key(BORROWED Hashmap * hm, OWNED char * key, arch val);

/**
 * @since       06.11.2025
 * @author      Junzhe
 * @modified    06.11.2025
 *
 */
arch hm_get(BORROWED Hashmap * hm, BORROWED const char * key);

/**
 * @since       06.11.2025
 * @author      Junzhe
 * @modified    06.11.2025
 *
 */
arch hm_get_owned_key(BORROWED Hashmap * hm, OWNED char * key);

/**
 * @since       06.11.2025
 * @author      Junzhe
 * @modified    06.11.2025
 *
 */
void hm_del(BORROWED Hashmap * hm, BORROWED const char * key);

/**
 * @since       06.11.2025
 * @author      Junzhe
 * @modified    06.11.2025
 *
 */
void hm_del_owned_key(BORROWED Hashmap * hm, OWNED char * key);

/**
 * @since       06.11.2025
 * @author      Junzhe
 * @modified    06.11.2025
 *
 */
OWNED Result * hm_try_get(BORROWED Hashmap * hm, BORROWED const char * key);

/**
 * @since       06.11.2025
 * @author      Junzhe
 * @modified    06.11.2025
 *
 */
OWNED Result * hm_try_get_owned_key(BORROWED Hashmap * hm, OWNED char * key);

/**
 * @since       06.11.2025
 * @author      Junzhe
 * @modified    06.11.2025
 *
 */
OWNED Result * _hm_try_ins(BORROWED Hashmap * hm, BORROWED const char * key, arch val);

/**
 * @since       06.11.2025
 * @author      Junzhe
 * @modified    06.11.2025
 *
 */
OWNED Result * _hm_try_ins_owned_key(BORROWED Hashmap * hm, OWNED char * key, arch val);

/**
 * @since       06.11.2025
 * @author      Junzhe
 * @modified    06.11.2025
 *
 */
OWNED Result * hm_try_del(BORROWED Hashmap * hm, BORROWED const char * key);

/**
 * @since       06.11.2025
 * @author      Junzhe
 * @modified    06.11.2025
 *
 */
OWNED Result * hm_try_del_owned_key(BORROWED Hashmap * hm, OWNED char * key);

/**
 * @since       06.11.2025
 * @author      Junzhe
 * @modified    06.11.2025
 *
 */
u64 hm_get_size(BORROWED Hashmap * hm);

/**
 * @since       06.11.2025
 * @author      Junzhe
 * @modified    06.11.2025
 *
 */
OWNED Result * hm_try_get_size(BORROWED Hashmap * hm);

/**
 * @since       06.11.2025
 * @author      Junzhe
 * @modified    06.11.2025
 *
 */
COPIED void * hm_dispose(OWNED void * arg);
