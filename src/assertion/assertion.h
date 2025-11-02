#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "generic.h"
#include "crayon.h"

/*——————————————————————————————————————————————————————————————————————————————————————————*/
/*                                      Assertion Macros                                    */
/*——————————————————————————————————————————————————————————————————————————————————————————*/
/**
 * @since       02.11.2025
 * @author      Junzhe
 * @modified    02.11.2025
 *
 * @brief       Immediately terminate the program with a fatal message.
 *              Logs the fatal message (with file and line) using @code {fatal_()}
 *
 * @param ...   printf-style format string and optional arguments.
 */
#define FATAL(...)                                                      \
    do {                                                                \
        fatal_(__FILE__, __LINE__, ##__VA_ARGS__);                      \
    } while (0)

/**
 * @since       02.11.2025
 * @author      Junzhe
 * @modified    02.11.2025
 *
 * @brief       Immediately terminate the program with an error.
 *              Logs the error message (with file and line) using
 *              @code {errorf_()} and then calls @code {exit(EXIT_FAILURE)}.
 *
 * @param ...   printf-style format string and optional arguments.
 */
#define PANIC(...)                                                      \
    do {                                                                \
        errorf_(__FILE__, __LINE__, ##__VA_ARGS__);                     \
        exit(EXIT_FAILURE);                                             \
    } while (0)

/**
 * @since       02.11.2025
 * @author		Junzhe
 * @modified    02.11.2025
 *
 * @brief Print a error message with file and line automatically filled.
 *
 * This macro wraps errorf_(), passing the current __FILE__ and __LINE__.
 * Use it like printf: the first argument is a format string, followed by
 * optional values. The message is logged as an error but does not abort.
 *
 * @param fmt printf-style format string.
 * @param ... optional arguments for the format string.
 */
#define ERRORF(fmt, ...)                                                \
    errorf_(__FILE__, __LINE__, fmt, ##__VA_ARGS__)

/**
 * @since       02.11.2025
 * @author		Junzhe
 * @modified    02.11.2025
 *
 * @brief Print a warning message with file and line automatically filled.
 *
 * This macro wraps warningf_(), passing the current __FILE__ and __LINE__.
 * Use it like printf: the first argument is a format string, followed by
 * optional values. The message is logged as a warning but does not abort.
 *
 * @param fmt printf-style format string.
 * @param ... optional arguments for the format string.
 */
#define WARNINGF(fmt, ...)                                              \
    warningf_(__FILE__, __LINE__, fmt, ##__VA_ARGS__)

/**
 * @since       02.11.2025
 * @author		Junzhe
 * @modified    02.11.2025
 *
 * @brief Print a informational message with file and line automatically filled.
 *
 * This macro wraps info_(), passing the current __FILE__ and __LINE__.
 * Use it like printf: the first argument is a format string, followed by
 * optional values. The message is logged as an info but does not abort.
 *
 * @param fmt printf-style format string.
 * @param ... optional arguments for the format string.
 */
#define INFO(fmt, ...)                                                  \
    info_(__FILE__, __LINE__, fmt, ##__VA_ARGS__)

/**
 * @since       02.11.2025
 * @author		Junzhe
 * @modified    02.11.2025
 *
 * @brief   Print a debug message with file and line automatically filled.
 *
 * This macro wraps debug_(), passing the current __FILE__ and __LINE__.
 * Use it like printf: the first argument is a format string, followed by
 * optional values. Intended for diagnostic output during development.
 *
 * @param fmt printf-style format string.
 * @param ... optional arguments for the format string.
 */
#define DEBUG(fmt, ...)                                                 \
    debug_(__FILE__, __LINE__, fmt, ##__VA_ARGS__)

/**
 * @since       02.11.2025
 * @author		Junzhe
 * @modified    02.11.2025
 *
 * @brief   Print a trace message with file and line automatically filled.
 *
 * This macro wraps tracef_(), passing the current __FILE__ and __LINE__.
 * Use it like printf: the first argument is a format string, followed by
 * optional values. Intended for diagnostic output during development.
 *
 * @param fmt printf-style format string.
 * @param ... optional arguments for the format string.
 */
#define tracef(fmt, ...)                                                \
    tracef_(__FILE__, __LINE__, fmt, ##__VA_ARGS__)

/**
 * @since       02.11.2025
 * @author      Junzhe
 * @modified    02.11.2025
 *
 * @brief      Marks unimplemented functions.
 *
 * This macro acts as a placeholder for functionality that is yet to be
 * implemented. When executed, it calls @func {panic} and terminates the
 * program, displaying a message that includes the current function name.
 *
 * @note The program will exit immediately when this macro is reached.
 */
#define TODO                                                            \
    panic("TODO: %s()", __func__)



/**
 * @since       02.11.2025
 * @author		Junzhe
 * @modified	02.11.2025
 *
 * @brief Assert with a custom formatted message.
 *
 * If the expression evaluates to false, aborts with the
 * user-supplied message (with file and line number).
 *
 * @param expr Expression to evaluate.
 * @param ...  printf-style format string and optional arguments.
 */
#define ASSERTF(expr, ...)                                              \
        do {                                                            \
            if ( !(expr) )                                              \
                errorf_(__FILE__, __LINE__, __VA_ARGS__);               \
        } while (0)

/**
 * @since       02.11.2025
 * @author		Junzhe
 * @modified	02.11.2025
 *
 * @brief       Assert that an expression is @const {true}
 *
 * If the expression evaluates to @const {false}, program aborts with a generic
 * "Assertion failed" message including the expression string, file, and line number.
 *
 * @param expr The expression to evaluate.
 */
#define ASSERT_EXPR(expr)                                               \
    do {                                                                \
        if (!(expr)) {                                                  \
            errorf_(                                                    \
                    __FILE__,                                           \
                    __LINE__,                                           \
                    "Assertion failed: " BOLD "%s" ENDCRAYON, #expr);   \
            exit(EXIT_FAILURE);                                         \
        }                                                               \
    } while (0)

/**
 * @since       02.11.2025
 * @author		Junzhe
 * @modified	02.11.2025
 *
 * @brief   Assert that two values are EQual.
 *
 * Uses macro EQ() to compare the two operands.
 * If they differ, aborts with an error message with file and line number.
 *
 * @param o1 First operand.
 * @param o2 Second operand.
 */
#define ASSERT_EQ(o1, o2)                                               \
        ASSERTF(EQ(o1, o2), BOLD "%s" ENDCRAYON " should be equal to " BOLD "%s" ENDCRAYON, #o1, #o2)

/**
 * @since       02.11.2025
 * @author		Junzhe
 * @modified	02.11.2025
 *
 * @brief       Assert that two operands are not EQual.
 *
 * Uses @macro {NEQ()} to compare the two operands.
 * If they are EQual, aborts with an error message with file and line number.
 *
 * @param o1 First operand.
 * @param o2 Second operand.
 */
#define ASSERT_NEQ(o1, o2)                                              \
        ASSERTF(NEQ(o1, o2), BOLD "%s" ENDCRAYON " should not be equal to " BOLD "%s" ENDCRAYON, #o1, #o2)



/*——————————————————————————————————————————————————————————————————————————————————————————*/
/*                                      Helper Functions                                    */
/*——————————————————————————————————————————————————————————————————————————————————————————*/
/**
 * @since       02.11.2025
 * @author      Junzhe
 * @modified    02.11.2025
 *
 * @brief       Global Assertion Error Output Stream.
 *
 * This global variable represents a generic error output
 * stream used by customized diagnostic and logging functions.
 * By default, it points to @const {stderr}
 */
extern FILE * AssertStream;

/**
 * @since       02.11.2025
 * @author		Junzhe
 * @modified	02.11.2025
 *
 * @brief       To print a fatal message and aborts the program.
 *
 * @param filename  Source file where the error occurred.
 * @param line      Line number.
 * @param fmt       printf-style format string.
 */
void fatal_(BORROWED const char * filename, COPIED const int line, BORROWED const char * fmt, ...);

/**
 * @since       02.11.2025
 * @author		Junzhe
 * @modified	02.11.2025
 *
 * @brief       To print an error message to the @global {errorstream}.
 *
 * @param filename  Source file where the error occurred.
 * @param line      Line number.
 * @param fmt       printf-style format string.
 */
void errorf_(BORROWED const char * filename, COPIED const int line, BORROWED const char * fmt, ...);

/**
 * @since       02.11.2025
 * @author	    Junzhe
 * @modified	02.11.2025
 *
 * @brief       To print a warning message to the @global {errorstream}.
 *
 * @param filename  Source file where the error occurred.
 * @param line      Line number.
 * @param fmt       printf-style format string.
 */
void warningf_(BORROWED const char * filename, COPIED const int line, BORROWED const char * fmt, ...);

/**
 * @since       02.11.2025
 * @author		Junzhe
 * @modified	02.11.2025
 *
 * @brief       To print a informational message to the @global {errorstream}.
 *
 * @param filename  Source file where the error occurred.
 * @param line      Line number.
 * @param fmt       printf-style format string.
 */
void info_(BORROWED const char * filename, COPIED const int line, BORROWED const char * fmt, ...);

/**
 * @since       02.11.2025
 * @author		Junzhe
 * @modified	02.11.2025
 *
 * @brief       To print a debug message to the @const {stderr}.
 *
 * @param filename  Source file where debug is logged
 * @param line      Line number
 * @param fmt       printf-style format string
 */
void debug_(BORROWED const char * filename, COPIED const int line, BORROWED const char * fmt, ...);


/**
 * @since       02.11.2025
 * @author		Junzhe
 * @modified	02.11.2025
 *
 * @brief       To print a trace message to the @global {errorstream}.
 *
 * @param filename  Source file where debug is logged
 * @param line      Line number
 * @param fmt       printf-style format string
 */
void tracef_(BORROWED const char * filename, COPIED const int line, BORROWED const char * fmt, ...);

