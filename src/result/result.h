#pragma once

#include "hwangfu/generic.h"
#include "hwangfu/memory.h"
#include "hwangfu/assertion.h"

typedef enum TResult TResult;

typedef struct Result Result;

/**
 * @since       03.11.2025
 * @author      Junzhe
 * @modified	04.11.2025
 *
 */
enum TResult
{
    RESULT_SUCCESS,
    RESULT_FAILURE,
};

/**
 * @since       03.11.2025
 * @author      Junzhe
 * @modified    04.11.2025
 *
 */
struct Result
{
    TResult Tag;
    union
    {
        arch Success;
        arch Failure;
    };
};

/**
 * @since       03.11.2025
 * @author      Junzhe
 * @modified	04.11.2025
 *
 */
OWNED Result * mk_result(TResult tag, arch value);

/**
 * @since       03.11.2025
 * @author      Junzhe
 * @modified	04.11.2025
 *
 */
OWNED Result * mk_result_success(arch success);

/**
 * @since       03.11.2025
 * @author      Junzhe
 * @modified	04.11.2025
 *
 */
OWNED Result * mk_result_failure(arch failure);

/**
 * @since       03.11.2025
 * @author      Junzhe
 * @modified	04.11.2025
 *
 */
arch result_unwrap(BORROWED Result * result);

/**
 * @since       03.11.2025
 * @author      Junzhe
 * @modified	04.11.2025
 *
 */
arch result_unwrap_else(BORROWED Result * result, arch alternative);

/**
 * @since       03.11.2025
 * @author      Junzhe
 * @modified	04.11.2025
 *
 */
arch result_unwrap_owned(OWNED Result * result);

/**
 * @since       03.11.2025
 * @author      Junzhe
 * @modified	04.11.2025
 *
 */
arch result_unwrap_else_owned(OWNED Result * result, arch alternative);

/**
 * @since       03.11.2025
 * @author      Junzhe
 * @modified	04.11.2025
 *
 * @brief       Safely dispose the @struct {Result}.
 *
 * NOTE:
 * You have handle the disposal of @field {Result.Success} or @field {Result.Failure} on you own.
 * This disposal function does nothing on them.
 */
COPIED void * result_dispose(OWNED void * arg);
