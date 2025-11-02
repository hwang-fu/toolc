#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "generic.h"
#include "crayon.h"

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

