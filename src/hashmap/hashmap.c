#include "hashmap.h"

/**
 * @since       06.11.2025
 * @author      Junzhe
 * @modified    06.11.2025
 *
 */
struct HashmapEntry
{
    OWNED char * Key;
    OWNED arch   Val;
    OWNED HashmapEntry * Next;
};

OWNED Hashmap * hm_init(OWNED Hashmap * hm, u64 capacity, dispose_fn * cleanup)
{
}

OWNED Hashmap * mk_hm(int mode, ...)
{
}

void _hm_ins(BORROWED Hashmap * hm, BORROWED const char * key, arch val)
{
}

void _hm_ins_owned_key(BORROWED Hashmap * hm, OWNED char * key, arch val)
{
}

arch hm_get(BORROWED Hashmap * hm, BORROWED const char * key)
{
}

arch hm_get_owned_key(BORROWED Hashmap * hm, OWNED char * key)
{
}

void hm_del(BORROWED Hashmap * hm, BORROWED const char * key)
{
}

void hm_del_owned_key(BORROWED Hashmap * hm, OWNED char * key)
{
}

OWNED Result * hm_try_get(BORROWED Hashmap * hm, BORROWED const char * key)
{
}

OWNED Result * hm_try_get_owned_key(BORROWED Hashmap * hm, OWNED char * key)
{
}

OWNED Result * _hm_try_ins(BORROWED Hashmap * hm, BORROWED const char * key, arch val)
{
}

OWNED Result * _hm_try_ins_owned_key(BORROWED Hashmap * hm, OWNED char * key, arch val)
{
}

OWNED Result * hm_try_del(BORROWED Hashmap * hm, BORROWED const char * key)
{
}

OWNED Result * hm_try_del_owned_key(BORROWED Hashmap * hm, OWNED char * key)
{
}

u64 hm_get_size(BORROWED Hashmap * hm)
{
}

OWNED Result * hm_try_get_size(BORROWED Hashmap * hm)
{
}
