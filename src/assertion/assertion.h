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
 * @modified    09.10.2025
 * @author      Junzhe
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

