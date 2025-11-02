#include "assertion.h"

FILE * AssertStream = nil;

static FILE * get_errorstream_()
{
    return AssertStream ? AssertStream : CERR;
}

static void space_()
{
    fputs(BLANK, get_errorstream_());
}

static void verrorstream_(BORROWED const char * fmt, va_list args)
{
    fputs(TAB, get_errorstream_());
    vfprintf(get_errorstream_(), fmt, args);
    fputs(LF, get_errorstream_());
}

static void metainfo_(BORROWED const char * filename, COPIED const int line)
{
    crayon_bold(get_errorstream_());
    fprintf(get_errorstream_(), "%s: line %d", filename, line);
    crayon_end(get_errorstream_());
    fputs(LF, get_errorstream_());
}

static void fatal_sign_()
{
    crayon_bold(get_errorstream_());
    crayon_fg_red(get_errorstream_());
    fputs("[FATAL]", get_errorstream_());
    crayon_end(get_errorstream_());
    space_();
}

void fatal_(BORROWED const char * filename, COPIED const int line, BORROWED const char * fmt, ...)
{
    fatal_sign_();

    metainfo_(filename, line);

    va_list args;
    va_start(args, fmt);
    verrorstream_(fmt, args);
    va_end(args);

    exit(EXIT_FAILURE);
}

static void error_sign_()
{
    crayon_bold(get_errorstream_());
    crayon_fg_magenta(get_errorstream_());
    fputs("[ERROR]", get_errorstream_());
    crayon_end(get_errorstream_());
    space_();
}

void errorf_(BORROWED const char * filename, COPIED const int line, BORROWED const char * fmt, ...) {
    error_sign_();

    metainfo_(filename, line);

    va_list args;
    va_start(args, fmt);
    verrorstream_(fmt, args);
    va_end(args);
}

static void warning_sign_()
{
    crayon_bold(get_errorstream_());
    crayon_fg_yellow(get_errorstream_());
    fputs("[WARNING]", get_errorstream_());
    crayon_end(get_errorstream_());
    space_();
}

void warningf_(BORROWED const char * filename, COPIED const int line, BORROWED const char * fmt, ...) {
    warning_sign_();

    metainfo_(filename, line);

    va_list args;
    va_start(args, fmt);
    verrorstream_(fmt, args);
    va_end(args);
}

static void info_sign_()
{
    crayon_bold(get_errorstream_());
    fputs("[INFO]", get_errorstream_());
    crayon_end(get_errorstream_());
    space_();
}

void info_(BORROWED const char * filename, COPIED const int line, BORROWED const char * fmt, ...) {
    info_sign_();

    metainfo_(filename, line);

    va_list args;
    va_start(args, fmt);
    verrorstream_(fmt, args);
    va_end(args);
}

static void debug_sign_()
{
    crayon_bold(CERR);
    crayon_fg_blue(CERR);
    fputs("[DEBUG]", CERR);
    crayon_end(CERR);
    fputs(BLANK, CERR);
}

void debug_(BORROWED const char * filename, COPIED const int line, BORROWED const char * fmt, ...) {
    debug_sign_();

    va_list args;
    va_start(args, fmt);
    fputs(TAB, CERR);
    vfprintf(CERR, fmt, args);
    fputs(LF, CERR);
    va_end(args);
}

static void trace_sign_()
{
    crayon_bold(get_errorstream_());
    crayon_fg_gray(get_errorstream_());
    fputs("[TRACE]", get_errorstream_());
    crayon_end(get_errorstream_());
    space_();
}

void tracef_(BORROWED const char * filename, COPIED const int line, BORROWED const char * fmt, ...)
{
    trace_sign_();

    metainfo_(filename, line);

    va_list args;
    va_start(args, fmt);
    verrorstream_(fmt, args);
    va_end(args);
}
