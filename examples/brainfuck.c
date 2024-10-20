/* ------------------------------ DIRECTIVES -------------------------------- */
/* Disable some warnings that the generated code can trigger. */
#if defined(__clang__) && __clang_major__ >= 3
  #pragma clang diagnostic ignored "-Wtype-limits"
  #pragma clang diagnostic ignored "-Wwrite-strings"
  #pragma clang diagnostic ignored "-Wunused"
  #pragma clang diagnostic ignored "-Wunused-parameter"
  #pragma clang diagnostic ignored "-Wmissing-field-initializers"
  #pragma clang diagnostic ignored "-Wparentheses-equality"
  #pragma clang diagnostic ignored "-Wtautological-compare"
  #pragma clang diagnostic ignored "-Wmissing-braces"
  #ifndef __cplusplus
    #pragma clang diagnostic ignored "-Wincompatible-pointer-types"
    #pragma clang diagnostic error   "-Wimplicit-function-declaration"
    #pragma clang diagnostic error   "-Wimplicit-int"
  #else
    #pragma clang diagnostic ignored "-Wnarrowing"
    #pragma clang diagnostic ignored "-Wc99-designator"
  #endif
#elif defined(__GNUC__) && __GNUC__ >= 5
  #pragma GCC diagnostic ignored "-Wtype-limits"
  #pragma GCC diagnostic ignored "-Wwrite-strings"
  #pragma GCC diagnostic ignored "-Wunused-parameter"
  #pragma GCC diagnostic ignored "-Wunused-value"
  #pragma GCC diagnostic ignored "-Wunused-variable"
  #pragma GCC diagnostic ignored "-Wunused-function"
  #pragma GCC diagnostic ignored "-Wunused-but-set-variable"
  #pragma GCC diagnostic ignored "-Wmissing-field-initializers"
  #ifndef __cplusplus
    #pragma GCC diagnostic ignored "-Wmissing-braces"
    #pragma GCC diagnostic ignored "-Wincompatible-pointer-types"
    #pragma GCC diagnostic ignored "-Wdiscarded-qualifiers"
    #pragma GCC diagnostic error   "-Wimplicit-function-declaration"
    #pragma GCC diagnostic error   "-Wimplicit-int"
  #else
    #pragma GCC diagnostic ignored "-Wnarrowing"
  #endif
#endif
#if defined(_WIN32) && !defined(_CRT_SECURE_NO_WARNINGS)
  #define _CRT_SECURE_NO_WARNINGS
#endif
/* Macro used to perform compile-time checks. */
#if __STDC_VERSION__ >= 201112L
  #define NELUA_STATIC_ASSERT _Static_assert
#elif __cplusplus >= 201103L
  #define NELUA_STATIC_ASSERT static_assert
#else
  #define NELUA_STATIC_ASSERT(x, y)
#endif
/* Macro used to get alignment of a type. */
#if __STDC_VERSION__ >= 201112L
  #define NELUA_ALIGNOF _Alignof
#elif __cplusplus >= 201103L
  #define NELUA_ALIGNOF alignof
#elif defined(__GNUC__)
  #define NELUA_ALIGNOF __alignof__
#elif defined(_MSC_VER)
  #define NELUA_ALIGNOF __alignof
#else
  #define NELUA_ALIGNOF(x)
#endif
/* Checks if Nelua and C agrees on pointer size. */
NELUA_STATIC_ASSERT(sizeof(void*) == 8 && NELUA_ALIGNOF(void*) == 8, "Nelua and C disagree on pointer size or alignment");
/* Enable 64 bit offsets for stdio APIs. */
#if !defined(_FILE_OFFSET_BITS) && __SIZEOF_LONG__ >= 8
  #define _FILE_OFFSET_BITS 64
#endif
/* Enable POSIX APIs in included headers. */
#if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && !defined(_GNU_SOURCE) && !defined(_DEFAULT_SOURCE)
  #if defined(__gnu_linux__)
    #define _GNU_SOURCE
  #else
    #define _XOPEN_SOURCE 600
  #endif
#endif
#define NELUA_NIL (nlniltype){}
#include <stdio.h>
/* Macro used sign that a type punning cast may alias (related to strict aliasing). */
#ifdef __GNUC__
  #define NELUA_MAYALIAS __attribute__((may_alias))
#else
  #define NELUA_MAYALIAS
#endif
#include <stdint.h>
#include <stdbool.h>
/* Macro used to force inlining a function. */
#ifdef __GNUC__
  #define NELUA_INLINE __attribute__((always_inline)) inline
#elif defined(_MSC_VER)
  #define NELUA_INLINE __forceinline
#elif __STDC_VERSION__ >= 199901L
  #define NELUA_INLINE inline
#else
  #define NELUA_INLINE
#endif
#include <stdlib.h>
/* Macro used to import/export extern C functions. */
#ifdef __cplusplus
  #define NELUA_EXTERN extern "C"
#else
  #define NELUA_EXTERN extern
#endif
/* Macro used to generate traceback on aborts when sanitizing. */
#if defined(__clang__) && defined(__has_feature)
  #if __has_feature(undefined_behavior_sanitizer)
    #define NELUA_UBSAN_UNREACHABLE __builtin_unreachable
  #endif
#elif defined(__gnu_linux__) && defined(__GNUC__) && __GNUC__ >= 5
  NELUA_EXTERN void __ubsan_handle_builtin_unreachable(void*) __attribute__((weak));
  #define NELUA_UBSAN_UNREACHABLE() {if(&__ubsan_handle_builtin_unreachable) __builtin_unreachable();}
#endif
#ifndef NELUA_UBSAN_UNREACHABLE
  #define NELUA_UBSAN_UNREACHABLE()
#endif
/* Macro used to specify a function that never returns. */
#if __STDC_VERSION__ >= 201112L
  #define NELUA_NORETURN _Noreturn
#elif defined(__GNUC__)
  #define NELUA_NORETURN __attribute__((noreturn))
#elif defined(_MSC_VER)
  #define NELUA_NORETURN __declspec(noreturn)
#else
  #define NELUA_NORETURN
#endif
#include <string.h>
/* Macro used for branch prediction. */
#if defined(__GNUC__) || defined(__clang__)
  #define NELUA_UNLIKELY(x) __builtin_expect(x, 0)
#else
  #define NELUA_UNLIKELY(x) (x)
#endif
/* ------------------------------ DECLARATIONS ------------------------------ */
typedef struct nlniltype {} nlniltype;
typedef struct nlniltype nltype;
typedef struct NELUA_MAYALIAS nlint32_arr1024 {int32_t v[1024];} nlint32_arr1024;
typedef union NELUA_MAYALIAS nlint32_arr1024_cast {nlint32_arr1024 a; int32_t p[1024];} nlint32_arr1024_cast;
NELUA_STATIC_ASSERT(sizeof(nlint32_arr1024) == 4096 && NELUA_ALIGNOF(nlint32_arr1024) == 4, "Nelua and C disagree on type size or align");
static nlint32_arr1024 examples_brainfuck_data;
static int32_t examples_brainfuck_ptr = 0;
static NELUA_INLINE void nelua_write_stderr(const char* msg, uintptr_t len, bool flush);
static NELUA_NORETURN void nelua_abort(void);
static NELUA_NORETURN void nelua_panic_cstring(const char* s);
static NELUA_INLINE int32_t nelua_assert_bounds_nlint32(int32_t index, uintptr_t len);
static int nelua_main(int argc, char** argv);
/* ------------------------------ DEFINITIONS ------------------------------- */
void nelua_write_stderr(const char* msg, uintptr_t len, bool flush) {
  if(len > 0 && msg) {
    fwrite(msg, 1, len, stderr);
  }
  if(flush) {
    fwrite("\n", 1, 1, stderr);
    fflush(stderr);
  }
}
void nelua_abort(void) {
  NELUA_UBSAN_UNREACHABLE();
  abort();
}
void nelua_panic_cstring(const char* s) {
  if(s) {
    nelua_write_stderr(s, strlen(s), true);
  }
  nelua_abort();
}
int32_t nelua_assert_bounds_nlint32(int32_t index, uintptr_t len) {
  if(NELUA_UNLIKELY((uintptr_t)index >= len || index < 0)) {
    nelua_panic_cstring("array index: position out of bounds");
  }
  return index;
}
int nelua_main(int argc, char** argv) {
  examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] = (examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] + 1);
  examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] = (examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] + 1);
  examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] = (examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] + 1);
  examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] = (examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] + 1);
  examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] = (examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] + 1);
  examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] = (examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] + 1);
  examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] = (examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] + 1);
  examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] = (examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] + 1);
examples_brainfuck_b11:;
  if((examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] == 0)) {
    goto examples_brainfuck_a11;
  }
  examples_brainfuck_ptr = (examples_brainfuck_ptr + 1);
  examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] = (examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] + 1);
  examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] = (examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] + 1);
  examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] = (examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] + 1);
  examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] = (examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] + 1);
examples_brainfuck_b17:;
  if((examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] == 0)) {
    goto examples_brainfuck_a17;
  }
  examples_brainfuck_ptr = (examples_brainfuck_ptr + 1);
  examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] = (examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] + 1);
  examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] = (examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] + 1);
  examples_brainfuck_ptr = (examples_brainfuck_ptr + 1);
  examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] = (examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] + 1);
  examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] = (examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] + 1);
  examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] = (examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] + 1);
  examples_brainfuck_ptr = (examples_brainfuck_ptr + 1);
  examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] = (examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] + 1);
  examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] = (examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] + 1);
  examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] = (examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] + 1);
  examples_brainfuck_ptr = (examples_brainfuck_ptr + 1);
  examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] = (examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] + 1);
  examples_brainfuck_ptr = (examples_brainfuck_ptr - 1);
  examples_brainfuck_ptr = (examples_brainfuck_ptr - 1);
  examples_brainfuck_ptr = (examples_brainfuck_ptr - 1);
  examples_brainfuck_ptr = (examples_brainfuck_ptr - 1);
  examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] = (examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] - 1);
  goto examples_brainfuck_b17;
examples_brainfuck_a17:;
  examples_brainfuck_ptr = (examples_brainfuck_ptr + 1);
  examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] = (examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] + 1);
  examples_brainfuck_ptr = (examples_brainfuck_ptr + 1);
  examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] = (examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] + 1);
  examples_brainfuck_ptr = (examples_brainfuck_ptr + 1);
  examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] = (examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] - 1);
  examples_brainfuck_ptr = (examples_brainfuck_ptr + 1);
  examples_brainfuck_ptr = (examples_brainfuck_ptr + 1);
  examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] = (examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] + 1);
examples_brainfuck_b46:;
  if((examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] == 0)) {
    goto examples_brainfuck_a46;
  }
  examples_brainfuck_ptr = (examples_brainfuck_ptr - 1);
  goto examples_brainfuck_b46;
examples_brainfuck_a46:;
  examples_brainfuck_ptr = (examples_brainfuck_ptr - 1);
  examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] = (examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] - 1);
  goto examples_brainfuck_b11;
examples_brainfuck_a11:;
  examples_brainfuck_ptr = (examples_brainfuck_ptr + 1);
  examples_brainfuck_ptr = (examples_brainfuck_ptr + 1);
  putchar((int)examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)]);
  examples_brainfuck_ptr = (examples_brainfuck_ptr + 1);
  examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] = (examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] - 1);
  examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] = (examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] - 1);
  examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] = (examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] - 1);
  putchar((int)examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)]);
  examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] = (examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] + 1);
  examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] = (examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] + 1);
  examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] = (examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] + 1);
  examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] = (examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] + 1);
  examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] = (examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] + 1);
  examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] = (examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] + 1);
  examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] = (examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] + 1);
  putchar((int)examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)]);
  putchar((int)examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)]);
  examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] = (examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] + 1);
  examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] = (examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] + 1);
  examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] = (examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] + 1);
  putchar((int)examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)]);
  examples_brainfuck_ptr = (examples_brainfuck_ptr + 1);
  examples_brainfuck_ptr = (examples_brainfuck_ptr + 1);
  putchar((int)examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)]);
  examples_brainfuck_ptr = (examples_brainfuck_ptr - 1);
  examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] = (examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] - 1);
  putchar((int)examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)]);
  examples_brainfuck_ptr = (examples_brainfuck_ptr - 1);
  putchar((int)examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)]);
  examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] = (examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] + 1);
  examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] = (examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] + 1);
  examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] = (examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] + 1);
  putchar((int)examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)]);
  examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] = (examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] - 1);
  examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] = (examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] - 1);
  examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] = (examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] - 1);
  examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] = (examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] - 1);
  examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] = (examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] - 1);
  examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] = (examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] - 1);
  putchar((int)examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)]);
  examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] = (examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] - 1);
  examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] = (examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] - 1);
  examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] = (examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] - 1);
  examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] = (examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] - 1);
  examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] = (examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] - 1);
  examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] = (examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] - 1);
  examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] = (examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] - 1);
  examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] = (examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] - 1);
  putchar((int)examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)]);
  examples_brainfuck_ptr = (examples_brainfuck_ptr + 1);
  examples_brainfuck_ptr = (examples_brainfuck_ptr + 1);
  examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] = (examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] + 1);
  putchar((int)examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)]);
  examples_brainfuck_ptr = (examples_brainfuck_ptr + 1);
  examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] = (examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] + 1);
  examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] = (examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)] + 1);
  putchar((int)examples_brainfuck_data.v[nelua_assert_bounds_nlint32(examples_brainfuck_ptr, 1024)]);
  return 0;
}
int main(int argc, char** argv) {
  return nelua_main(argc, argv);
}

