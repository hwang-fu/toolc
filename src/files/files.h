#pragma once

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdarg.h>

#include <hwangfu/generic.h>
#include <hwangfu/memory.h>
#include <hwangfu/result.h>
#include <hwangfu/assertion.h>

/**
 * @since       23.11.2025
 * @author      Junzhe
 * @modified    27.11.2025
 *
 */
#define assert_filename(filename)                                               \
        do {                                                                    \
            if (!filename)                                                      \
            {                                                                   \
                panic("Error @%s(): filename is nil.", __FUNCTION__);           \
            }                                                                   \
            if (0 == strlen_safe(filename))                                     \
            {                                                                   \
                panic("Error @%s(): filename is \"\"", __FUNCTION__);           \
            }                                                                   \
        } while (0)

/**
 * @since       23.11.2025
 * @author      Junzhe
 * @modified    27.11.2025
 *
 * @brief       Returns a fd based on the given @arg {filename}, aborts if failed.
 *
 * Possible overloads:
 * @li int mk_fd(filename, 0);              // read-write
 * @li int mk_fd(filename, 1);              // read-only
 * @li int mk_fd(filename, 2);              // write-only, append
 * @li int mk_fd(filename, 3);              // write-only, open and truncate to empty if exists.
 */
int mk_simple_fd(BORROWED const char * filename, int mode);

/**
 * @since       23.11.2025
 * @author      Junzhe
 * @modified    27.11.2025
 *
 */
OWNED Result * fd_simple_read(int fd, u64 size);

/**
 * @since       23.11.2025
 * @author      Junzhe
 * @modified    27.11.2025
 *
 */
bool fd_simple_write(int fd, BORROWED const u8 * data, u64 size);

/**
 * @since       23.11.2025
 * @author      Junzhe
 * @modified    27.11.2025
 *
 */
void fd_simple_close(int fd);

/**
 * @since       23.11.2025
 * @author      Junzhe
 * @modified    27.11.2025
 *
 */
bool filename_is_regular(borrowed const char * filename);

/**
 * @since       23.11.2025
 * @author      Junzhe
 * @modified    27.11.2025
 *
 */
bool filename_is_directory(borrowed const char * filename);

/**
 * @since       23.11.2025
 * @author      Junzhe
 * @modified    27.11.2025
 *
 */
bool filename_is_symbolic_link(borrowed const char * filename);

/**
 * @since       23.11.2025
 * @author      Junzhe
 * @modified    27.11.2025
 *
 */
bool filename_is_character_device(borrowed const char * filename);

/**
 * @since       23.11.2025
 * @author      Junzhe
 * @modified    27.11.2025
 *
 */
bool filename_is_block_device(borrowed const char * filename);

/**
 * @since       23.11.2025
 * @author      Junzhe
 * @modified    27.11.2025
 *
 */
bool filename_is_fifo(borrowed const char * filename);

/**
 * @since       23.11.2025
 * @author      Junzhe
 * @modified    27.11.2025
 *
 */
bool filename_is_socket(borrowed const char * filename);

/**
 * @since       23.11.2025
 * @author      Junzhe
 * @modified    27.11.2025
 *
 */
bool filename_exists(borrowed const char * filename);

/**
 * @since       23.11.2025
 * @author      Junzhe
 * @modified    27.11.2025
 *
 */
bool filename_is_readable(borrowed const char * filename);

/**
 * @since       23.11.2025
 * @author      Junzhe
 * @modified    27.11.2025
 *
 */
bool filename_is_writable(borrowed const char * filename);

/**
 * @since       23.11.2025
 * @author      Junzhe
 * @modified    27.11.2025
 *
 */
bool filename_is_executable(borrowed const char * filename);
