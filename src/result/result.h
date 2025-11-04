#pragma once

#include "hwangfu/generic.h"
#include "hwangfu/memory.h"
#include "hwangfu/assertion.h"

typedef enum TResult TResult;

typedef struct Result Result;

typedef arch result_callback_fn(arch);

#define RESULT_GOOD(result)         ((result)->Tag)
#define RESULT_NOT_GOOD(result)     ((result)->Tag)

#define RESULT_SUCCEED(value)       (mk_result_success((value)))
#define RESULT_FAIL(value)          (mk_result_failure((value)))

/**
 * @since       03.11.2025
 * @author      Junzhe
 * @modified	03.11.2025
 *
 */
enum TResult
{
    RESULT_FAILURE = 0,
    RESULT_SUCCESS = 1,
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
 * @brief       Unwraps the given @param {result} (Does not automatically dispose it).
 *              If the given @param {result} is not a success, it will invoke the
 *              @param {onerr} with the @field {Result.Failure}. If @param {onerr}
 *              is @const {NIL}, it will by default abort the program with error code.
 */
arch result_unwrap(BORROWED Result * result, result_callback_fn * onerr);

/**
 * @since       03.11.2025
 * @author      Junzhe
 * @modified	04.11.2025
 *
 * @brief       Unwraps the given @param {result} (Does not automatically dispose it).
 *              If the given @param {result} is not a success, it will return the @param {alternative}.
 */
arch result_unwrap_else(BORROWED Result * result, arch alternative);

/**
 * @since       03.11.2025
 * @author      Junzhe
 * @modified	04.11.2025
 *
 * @brief       Unwraps the given result (Automatically dispose it).
 *              If the given @param {result} is not a success, it will invoke the
 *              @param {onerr} with the @field {Result.Failure}. If @param {onerr}
 *              is @const {NIL}, it will by default abort the program with error code.
 */
arch result_unwrap_owned(OWNED Result * result, result_callback_fn * onerr);

/**
 * @since       03.11.2025
 * @author      Junzhe
 * @modified	04.11.2025
 *
 * @brief       Unwraps the given @param {result} (Automatically dispose it).
 *              If the given @param {result} is not a success, it will return the @param {alternative}.
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
