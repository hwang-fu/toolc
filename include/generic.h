#pragma once

#include <stdint.h>
#include <stdbool.h>

// -------------------------------------------------------------
// | Customized Type Aliases |
// -------------------------------------------------------------
#ifndef HWANGFU_BASE_TYPES
#define HWANGFU_BASE_TYPES
typedef float           f32     ;
typedef double          f64     ;

typedef char            i8      ;
typedef char            ascii   ;
typedef unsigned char   u8      ;

typedef int16_t         i16     ;
typedef uint16_t        u16     ;

typedef int32_t         i32     ;
typedef uint32_t        u32     ;

typedef int64_t         i64     ;
typedef uint64_t        u64     ;

typedef float*          F32Ptr  ;
typedef double*         F64Ptr  ;

typedef u8*             U8Ptr   ;
typedef u16*            U16Ptr  ;
typedef u32*            U32Ptr  ;
typedef u64*            U64Ptr  ;
typedef i8*             I8Ptr   ;
typedef i16*            I16Ptr  ;
typedef i32*            I32Ptr  ;
typedef i64*            I64Ptr  ;
typedef char*           cstring ;

typedef uintptr_t       arch    ;

typedef void* (dispose_fn) (void*);
typedef void* (handler_fn) (void*);
#endif // HWANGFU_BASE_TYPES

// -------------------------------------------------------------
// | Standard FILE Stream Aliases |
// -------------------------------------------------------------
#ifndef HWANGFU_C_FILE_STREAM
#define HWANGFU_C_FILE_STREAM
#define COUT (stdout)
#define CIN  (stdin)
#define CERR (stderr)
#endif // HWANGFU_C_FILE_STREAM

// -------------------------------------------------------------
// | NULL macro |
// -------------------------------------------------------------
#ifndef HWANGFU_NIL_MACRO
#define HWANGFU_NIL_MACRO
// Use `nil` / `NIL` as a universal null/zero value.
#define nil (0)
#define NIL (0)
#endif // HWANGFU_NIL_MACRO

// -------------------------------------------------------------
// | Ownership Annotations |
// -------------------------------------------------------------
#ifndef HWANGFU_OWNERSHIP
#define HWANGFU_OWNERSHIP
// These are semantic markers - useful for documentation, not functionality.
#define copied
#define borrowed
#define owned

#define COPIED
#define BORROWED
#define OWNED
#endif // HWANGFU_OWNERSHIP

// -------------------------------------------------------------
// | pointer / Reference helpers |
// -------------------------------------------------------------
#ifndef DEREF
/**
 * DEREF(ptr, type):
 *      DeREFerences a pointer with the expected type.
 */
#define DEREF(ptr, type)                                            \
        (*((type *)(ptr)))
#endif // DEREF

#ifndef REF
/**
 * REF(ptr):
 *      Get the address of a variable (pass-by-REFerence helper).
 */
#define REF(var)                                                    \
        (&(var))
#endif //

#ifndef CAST
/**
 * CAST(obj, type):
 *      Explicitly CAST object to type.
 */
#define CAST(obj, type)                                             \
        ((type) (obj))
#endif //

#ifndef NULLIFY
/**
 * NULLIFY(ptr):
 *      Sets the pointer to nil (zero).
 */
#define NULLIFY(ptr)                                                \
        (ptr) = nil
#endif //

// -------------------------------------------------------------
// | Comparison Helpers |
// -------------------------------------------------------------
#ifndef HWANGFU_COMPARISON_HELPERS
#define HWANGFU_COMPARISON_HELPERS
#define EQ(o1, o2)                                                  \
        ((o1) == (o2))

#define NEQ(o1, o2)                                                 \
        ((o1) != (o2))
#endif // HWANGFU_COMPARISON_HELPERS

// -------------------------------------------------------------
// | Arithmetic Helpers |
// -------------------------------------------------------------
#ifndef HWANGFU_ARITHMETIC_HELPERS
#define HWANGFU_ARITHMETIC_HELPERS
/**
 * ROUNDUP(n, d):
 *      1. Rounds up `n` to the nearest multiple of `d`.
 *      2. Useful for alignment or chunked memory blocks.
 *
 * ROUNDUP(10, 3) == 4
 */
#define ROUNDUP(n, d)                                               \
        (((n) + (d) - 1) / (d))

// A small enough number.
#define EPSILON (1e-11)

/**
 * WATERMARK(used, total):
 *      1. Calculates the usage ratio as a floating-point value.
 *      2. Returns a value in [0.0, 1.0] when `used <= total`.
 */
#define WATERMARK(used, total)                                      \
        ((total > 0) ? (f64)(used) / (f64)(total) : (f64) 1.0)

#define WATERMARK_HIGH  (.7)
#define WATERMARK_LOW   (.4)

#define INC(n)                                                      \
    (++(n))

#define DEC(n)                                                      \
    (--(n))

#define PLUS(n, amount)                                             \
    ((n) + (amount))

#define MINUS(n, amount)                                            \
    ((n) - (amount))

#define SHR32(x,n)              ((u32)(x) >> ((u32)(n) & 31u))
#define SHL32(x,n)              ((u32)(x) << ((u32)(n) & 31u))

#define SHR64(x,n)              ((u64)(x) >> ((u64)(n) & 63u))
#define SHL64(x,n)              ((u64)(x) << ((u64)(n) & 63u))

#define ROR32(x,n) ( (u32)( ((u32)(x) >> ((u32)(n) & 31u)) |            \
                             ((u32)(x) << ((-((u32)(n) & 31u)) & 31u)) ) )

#define ROL32(x,n) ( (u32)( ((u32)(x) << ((u32)(n) & 31u)) |            \
                             ((u32)(x) >> ((-((u32)(n) & 31u)) & 31u)) ) )

#define ROR64(x,n) ( (u64)(( (u64)(x) >> ((u64)(n) & 63u) ) |           \
                            ( (u64)(x) << ((-( (u64)(n) & 63u)) & 63u) )) )

#define ROL64(x,n) ( (u64)(( (u64)(x) << ((u64)(n) & 63u) ) |           \
                            ( (u64)(x) >> ((-( (u64)(n) & 63u)) & 63u) )) )

// ---------------------------------------------------------------------------
// Simple MIN/MAX macros.
//
// NOTE:
//   • Each argument may be evaluated more than once.
//     Therefore, do NOT pass expressions with side effects (like i++, func(), etc.).
//   • Safe only for plain variables or constants.
//
// Example:
//     int m = MIN3(x, y, z);
//     int m = MIN3(x++, y, z); // WILL BE WRONG!
// ---------------------------------------------------------------------------
#define MIN2(a, b)                                                      \
    (((a) < (b)) ? (a) : (b))

#define MIN3(a, b, c)                                                   \
    ((MIN2(a, b) < (c)) ? (MIN2(a, b)) : (c))

#define MIN4(a, b, c, d)                                                \
    ((MIN3(a, b, c) < (d)) ? (MIN3(a, b, c)) : (d))

#define MIN5(a, b, c, d, e)                                             \
    ((MIN4(a, b, c, d) < (e)) ? (MIN4(a, b, c, d)) : (e))

#define MIN6(a, b, c, d, e, f)                                          \
    ((MIN5(a, b, c, d, e) < (f)) ? (MIN5(a, b, c, d, e)) : (f))

#define MIN7(a, b, c, d, e, f, g)                                       \
    ((MIN6(a, b, c, d, e, f) < (g)) ? (MIN6(a, b, c, d, e, f)) : (g))

#define MIN8(a, b, c, d, e, f, g, h)                                    \
    ((MIN7(a, b, c, d, e, f, g) < (h)) ? (MIN7(a, b, c, d, e, f, g)) : (h))


#define MAX2(a, b)                                                      \
    (((a) > (b)) ? (a) : (b))

#define MAX3(a, b, c)                                                   \
    ((MAX2(a, b) > (c)) ? (MAX2(a, b)) : (c))

#define MAX4(a, b, c, d)                                                \
    ((MAX3(a, b, c) > (d)) ? (MAX3(a, b, c)) : (d))

#define MAX5(a, b, c, d, e)                                             \
    ((MAX4(a, b, c, d) > (e)) ? (MAX4(a, b, c, d)) : (e))

#define MAX6(a, b, c, d, e, f)                                          \
    ((MAX5(a, b, c, d, e) > (f)) ? (MAX5(a, b, c, d, e)) : (f))

#define MAX7(a, b, c, d, e, f, g)                                       \
    ((MAX6(a, b, c, d, e, f) > (g)) ? (MAX6(a, b, c, d, e, f)) : (g))

#define MAX8(a, b, c, d, e, f, g, h)                                    \
    ((MAX7(a, b, c, d, e, f, g) > (h)) ? (MAX7(a, b, c, d, e, f, g)) : (h))


#endif // HWANGFU_ARITHMETIC_HELPERS

// -------------------------------------------------------------
// | Special ASCII Characters |
// -------------------------------------------------------------
#ifndef SPECIAL_ASCII_CHARS
#define SPECIAL_ASCII_CHARS
#define CR              ("\r")
#define LF              ("\n")
#define CRLF            ("\r\n")
#define TAB             ("\t")
#define BLANK           (" ")
#define WHITESPACES     (CRLF TAB BLANK)

#define SPACE           (' ')
#define HORIZONTAL_TAB  ('\t')
#define CARRIAGE_RETURN ('\r')
#define LINE_FEED       ('\n')
#endif // SPECIAL_ASCII_CHARS

// -------------------------------------------------------------
// | Customized Boolean Type |
// -------------------------------------------------------------
#ifndef HWANGFU_BOOLEAN_T
#define HWANGFU_BOOLEAN_T
typedef bool            Bool        ;
#define True            (true)
#define False           (false)
#endif // HWANGFU_BOOLEAN_T



