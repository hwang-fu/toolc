#pragma once

#include <stdint.h>
#include <stdbool.h>

// -------------------------------------------------------------
// | Customized Type Aliases |
// -------------------------------------------------------------
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

// -------------------------------------------------------------
// | Standard FILE Stream Aliases |
// -------------------------------------------------------------
#define COUT (stdout)
#define CIN  (stdin)
#define CERR (stderr)

// -------------------------------------------------------------
// | NULL macro |
// -------------------------------------------------------------
// Use `nil` / `NIL` as a universal null/zero value.
#ifndef nil
#define nil (0)
#endif // nil
#ifndef NIL
#define NIL (0)
#endif // NIL

// -------------------------------------------------------------
// | Ownership Annotations |
// -------------------------------------------------------------
// These are semantic markers - useful for documentation, not functionality.
#ifndef copied
#define copied
#endif // copied

#ifndef borrowed
#define borrowed
#endif // borrowed

#ifndef owned
#define owned
#endif // owned

#ifndef COPIED
#define COPIED
#endif // COPIED

#ifndef BORROWED
#define BORROWED
#endif // BORROWED

#ifndef OWNED
#define OWNED
#endif // OWNED

// -------------------------------------------------------------
// | pointer / REFerence helpers |
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
// | comparison helpers |
// -------------------------------------------------------------
#ifndef EQ
#define EQ(o1, o2)                                                  \
        ((o1) == (o2))
#endif // EQ

#ifndef NEQ
#define NEQ(o1, o2)                                                 \
        ((o1) != (o2))
#endif // NEQ


