#pragma once

#include <stdlib.h>
#include <string.h>

#include "hwangfu/generic.h"
#include "hwangfu/result.h"
#include "hwangfu/memory.h"
#include "hwangfu/assertion.h"

#ifndef DEQUEUE_DEFAULT_CAPACITY
#define DEQUEUE_DEFAULT_CAPACITY (20)
#endif // DEQUEUE_DEFAULT_CAPACITY

typedef struct Dequeue Dequeue;
typedef arch (dq_apply_fn) (arch);

/**
 * @since       03.11.2025
 * @author      Junzhe
 * @modified    03.11.2025
 */
struct Dequeue
{
    bool            IsInitialized   ;
    u64             Size            ;
    u64             Capacity        ;
    arch       *    Data            ;
    dispose_fn *    Dispose         ;
};

/**
 * @since       03.11.2025
 * @author      Junzhe
 * @modified    03.11.2025
 */
OWNED Dequeue * dq_init(OWNED Dequeue * dq, u64 capacity, dispose_fn * cleanup);

/**
 * @since       03.11.2025
 * @author      Junzhe
 * @modified    03.11.2025
 */
OWNED Dequeue * mk_dq();

/**
 * @since       03.11.2025
 * @author      Junzhe
 * @modified    03.11.2025
 */
OWNED Dequeue * mk_dq(dispose_fn * cleanup);

/**
 * @since       03.11.2025
 * @author      Junzhe
 * @modified    03.11.2025
 */
OWNED Dequeue * mk_dq2(u64 capacity, dispose_fn * cleanup);

/**
 * @since       03.11.2025
 * @author      Junzhe
 * @modified    03.11.2025
 */
arch dq_at(BORROWED Dequeue * dq, u64 idx);

/**
 * @since       03.11.2025
 * @author      Junzhe
 * @modified    03.11.2025
 */
void dq_pushfront(BORROWED Dequeue * dq, arch value);

/**
 * @since       03.11.2025
 * @author      Junzhe
 * @modified    03.11.2025
 */
void dq_pushback(BORROWED Dequeue * dq, arch value);

/**
 * @since       03.11.2025
 * @author      Junzhe
 * @modified    03.11.2025
 */
arch dq_front(BORROWED Dequeue * dq);

/**
 * @since       03.11.2025
 * @author      Junzhe
 * @modified    03.11.2025
 */
arch dq_back(BORROWED Dequeue * dq);

/**
 * @since       03.11.2025
 * @author      Junzhe
 * @modified    03.11.2025
 */
arch dq_popfront(BORROWED Dequeue * dq);

/**
 * @since       03.11.2025
 * @author      Junzhe
 * @modified    03.11.2025
 */
arch dq_popback(BORROWED Dequeue * dq);

/**
 * @since       03.11.2025
 * @author      Junzhe
 * @modified    03.11.2025
 */
OWNED Result * dq_try_at(BORROWED Dequeue * dq, u64 idx);

/**
 * @since       03.11.2025
 * @author      Junzhe
 * @modified    03.11.2025
 */
bool dq_try_pushfront(BORROWED Dequeue * dq, arch value);

/**
 * @since       03.11.2025
 * @author      Junzhe
 * @modified    03.11.2025
 */
bool dq_try_pushback(BORROWED Dequeue * dq, arch value);

/**
 * @since       03.11.2025
 * @author      Junzhe
 * @modified    03.11.2025
 */
OWNED Result * dq_try_front(BORROWED Dequeue * dq);

/**
 * @since       03.11.2025
 * @author      Junzhe
 * @modified    03.11.2025
 */
OWNED Result * dq_try_back(BORROWED Dequeue * dq);

/**
 * @since       03.11.2025
 * @author      Junzhe
 * @modified    03.11.2025
 */
OWNED Result * dq_try_popfront(BORROWED Dequeue * dq);

/**
 * @since       03.11.2025
 * @author      Junzhe
 * @modified    03.11.2025
 */
OWNED Result * dq_try_popback(BORROWED Dequeue * dq);

/**
 * @since       03.11.2025
 * @author      Junzhe
 * @modified    03.11.2025
 */
u64 dq_get_size(BORROWED Dequeue * dq);

/**
 * @since       03.11.2025
 * @author      Junzhe
 * @modified    03.11.2025
 */
OWNED Result * dq_try_get_size(BORROWED Dequeue * dq);

/**
 * @since       03.11.2025
 * @author      Junzhe
 * @modified    03.11.2025
 */
u64 dq_get_capacity(BORROWED Dequeue * dq);

/**
 * @since       03.11.2025
 * @author      Junzhe
 * @modified    03.11.2025
 */
OWNED Result * dq_try_get_capacity(BORROWED Dequeue * dq);

/**
 * @since       03.11.2025
 * @author      Junzhe
 * @modified    03.11.2025
 */
void dq_fit(BORROWED Dequeue * dq, u64 newCapacity);

/**
 * @since       03.11.2025
 * @author      Junzhe
 * @modified    03.11.2025
 */
bool dq_try_fit(BORROWED Dequeue * dq, u64 newCapacity);

/**
 * @since       03.11.2025
 * @author      Junzhe
 * @modified    03.11.2025
 *
 * @brief       If @param {dq} is @const {NIL}, the function also returns @const {True}.
 */
bool dq_is_empty(BORROWED Dequeue * dq);

/**
 * @since       03.11.2025
 * @author      Junzhe
 * @modified    03.11.2025
 *
 * @brief       Apply function @param {apply} to the given element.
 *              If @param {dq} is @const {NIL} or @param {idx} is out of range, abort.
 */
void dq_apply_at(BORROWED Dequeue * dq, u64 idx, dq_apply_fn * apply);

/**
 * @since       03.11.2025
 * @author      Junzhe
 * @modified    03.11.2025
 *
 * @brief       Apply function @param {apply} to the given element.
 *              If @param {dq} is @const {NIL} or @param {idx} is out of range, return @const {False}.
 */
bool dq_try_apply_at(BORROWED Dequeue * dq, u64 idx, dq_apply_fn * apply);

/**
 * @since       03.11.2025
 * @author      Junzhe
 * @modified    03.11.2025
 */
COPIED void * dq_dispose(OWNED void * arg);
