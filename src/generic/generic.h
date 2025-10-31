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
#define cout (stdout)
#define cin  (stdin)
#define cerr (stderr)

// -------------------------------------------------------------
// | NULL macro |
// -------------------------------------------------------------
// Use `nil` as a universal null/zero value.
#define nil (0)

// -------------------------------------------------------------
// | Ownership Annotations |
// -------------------------------------------------------------
// These are semantic markers - useful for documentation, not functionality.
#define copied
#define borrowed
#define owned




