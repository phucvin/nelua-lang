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
#include <string.h>
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
#include <stdint.h>
/* Macro used for branch prediction. */
#if defined(__GNUC__) || defined(__clang__)
  #define NELUA_UNLIKELY(x) __builtin_expect(x, 0)
#else
  #define NELUA_UNLIKELY(x) (x)
#endif
#include <stdio.h>
#include <stdbool.h>
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
#include <stddef.h>
#define NELUA_NIL (nlniltype){}
/* Macro used sign that a type punning cast may alias (related to strict aliasing). */
#ifdef __GNUC__
  #define NELUA_MAYALIAS __attribute__((may_alias))
#else
  #define NELUA_MAYALIAS
#endif
/* ------------------------------ DECLARATIONS ------------------------------ */
static NELUA_INLINE void nelua_memory_copy(void* dest, void* src, uintptr_t n);
static NELUA_INLINE void nelua_write_stderr(const char* msg, uintptr_t len, bool flush);
static NELUA_NORETURN void nelua_abort(void);
typedef struct nlstring nlstring;
typedef uint8_t* nluint8_arr0_ptr;
struct nlstring {
  nluint8_arr0_ptr data;
  uintptr_t size;
};
NELUA_STATIC_ASSERT(sizeof(nlstring) == 16 && NELUA_ALIGNOF(nlstring) == 8, "Nelua and C disagree on type size or align");
static void nelua_assert_line_1(bool cond, nlstring msg);
typedef struct nlniltype {} nlniltype;
typedef struct nlniltype nltype;
typedef struct nelua_GeneralAllocator nelua_GeneralAllocator;
struct nelua_GeneralAllocator {};
static nelua_GeneralAllocator nelua_general_allocator;
typedef nelua_GeneralAllocator* nelua_GeneralAllocator_ptr;
static NELUA_INLINE void* nelua_GeneralAllocator_alloc_1(nelua_GeneralAllocator_ptr self, uintptr_t size, nlniltype flags);
static NELUA_INLINE void nelua_GeneralAllocator_dealloc(nelua_GeneralAllocator_ptr self, void* p);
static void* nelua_GeneralAllocator_xalloc_1(nelua_GeneralAllocator_ptr self, uintptr_t size, nlniltype flags);
static NELUA_NORETURN void nelua_panic_string(nlstring s);
typedef struct NELUA_MAYALIAS nluint8_arr48 {uint8_t v[48];} nluint8_arr48;
typedef union NELUA_MAYALIAS nluint8_arr48_cast {nluint8_arr48 a; uint8_t p[48];} nluint8_arr48_cast;
NELUA_STATIC_ASSERT(sizeof(nluint8_arr48) == 48 && NELUA_ALIGNOF(nluint8_arr48) == 1, "Nelua and C disagree on type size or align");
typedef nluint8_arr48* nluint8_arr48_ptr;
static nlstring nelua_strconv_1_int2str_1(nluint8_arr48_ptr buf, intptr_t x, nlniltype base);
static NELUA_NORETURN void nelua_panic_cstring(const char* s);
static NELUA_INLINE uintptr_t nelua_assert_bounds_nlusize(uintptr_t index, uintptr_t len);
typedef nlstring* nlstring_ptr;
static void nelua_nlstring_destroy(nlstring_ptr self);
static nlstring nelua_nlstring_copy(nlstring s);
static nlstring nelua_tostring_1(int64_t x);
static void nelua_print_1(nlstring a1);
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
void nelua_assert_line_1(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("memory.nelua:27:14: runtime error: ", 35, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n  check(dest and src, 'invalid pointer')\n             ^~~~~~~\n", 63, true);
    nelua_abort();
  }
}
void nelua_memory_copy(void* dest, void* src, uintptr_t n) {
  if(NELUA_UNLIKELY((n == 0))) {
    return;
  }
  nelua_assert_line_1(((dest != NULL) && (src != NULL)), ((nlstring){(uint8_t*)"invalid pointer", 15}));
  memcpy(dest, src, (size_t)n);
}
void* nelua_GeneralAllocator_alloc_1(nelua_GeneralAllocator_ptr self, uintptr_t size, nlniltype flags) {
  if(NELUA_UNLIKELY((size == 0))) {
    return (void*)NULL;
  }
  return malloc((size_t)size);
}
void nelua_GeneralAllocator_dealloc(nelua_GeneralAllocator_ptr self, void* p) {
  if(NELUA_UNLIKELY((p == (void*)NULL))) {
    return;
  }
  free(p);
}
void nelua_panic_string(nlstring s) {
  if(s.size > 0) {
    nelua_write_stderr((const char*)s.data, s.size, true);
  }
  nelua_abort();
}
void* nelua_GeneralAllocator_xalloc_1(nelua_GeneralAllocator_ptr self, uintptr_t size, nlniltype flags) {
  void* p = nelua_GeneralAllocator_alloc_1(self, size, NELUA_NIL);
  if(NELUA_UNLIKELY(((p == (void*)NULL) && (size > 0)))) {
    nelua_panic_string(((nlstring){(uint8_t*)"out of memory", 13}));
  }
  return p;
}
void nelua_panic_cstring(const char* s) {
  if(s) {
    nelua_write_stderr(s, strlen(s), true);
  }
  nelua_abort();
}
uintptr_t nelua_assert_bounds_nlusize(uintptr_t index, uintptr_t len) {
  if(NELUA_UNLIKELY((uintptr_t)index >= len)) {
    nelua_panic_cstring("array index: position out of bounds");
  }
  return index;
}
nlstring nelua_strconv_1_int2str_1(nluint8_arr48_ptr buf, intptr_t x, nlniltype base) {
  uintptr_t pos = 47U;
  buf->v[nelua_assert_bounds_nlusize(pos, 48)] = 0U;
  pos = (pos - 1);
  bool neg = (x < 0);
  if((x == 0)) {
    buf->v[nelua_assert_bounds_nlusize(pos, 48)] = 48U;
    pos = (pos - 1);
  } else {
    while((x != 0)) {
      intptr_t quot = (x / 10);
      intptr_t rema = (x - (quot * 10));
      if((rema < 0)) {
        rema = (-rema);
      }
      x = quot;
      buf->v[nelua_assert_bounds_nlusize(pos, 48)] = (uint8_t)(rema + 48);
      pos = (pos - 1);
    }
  }
  if(neg) {
    buf->v[nelua_assert_bounds_nlusize(pos, 48)] = 45U;
    pos = (pos - 1);
  }
  return (nlstring){.data = ((nluint8_arr0_ptr)(&buf->v[nelua_assert_bounds_nlusize((pos + 1), 48)])), .size = ((48 - pos) - 2)};
}
void nelua_nlstring_destroy(nlstring_ptr self) {
  if(NELUA_UNLIKELY((self->size == 0))) {
    return;
  }
  nelua_GeneralAllocator_dealloc((&nelua_general_allocator), (void*)self->data);
  self->data = ((nluint8_arr0_ptr)NULL);
  self->size = 0U;
}
nlstring nelua_nlstring_copy(nlstring s) {
  nlstring clone = (nlstring){0};
  if(NELUA_UNLIKELY((s.size == 0))) {
    return clone;
  }
  clone.data = ((nluint8_arr0_ptr)nelua_GeneralAllocator_xalloc_1((&nelua_general_allocator), (s.size + 1), NELUA_NIL));
  nelua_memory_copy((void*)clone.data, (void*)s.data, s.size);
  clone.data[s.size] = 0U;
  clone.size = s.size;
  return clone;
}
nlstring nelua_tostring_1(int64_t x) {
  nluint8_arr48 buf;
  nlstring s = nelua_strconv_1_int2str_1((&buf), (intptr_t)x, NELUA_NIL);
  return nelua_nlstring_copy(s);
}
void nelua_print_1(nlstring a1) {
  if(a1.size > 0) {
    fwrite(a1.data, 1, a1.size, stdout);
  }
  fputs("\n", stdout);
  fflush(stdout);
}
int nelua_main(int argc, char** argv) {
  {
    nelua_print_1(((nlstring){(uint8_t*)"## Memory management", 20}));
    nlstring str = nelua_tostring_1(1);
    nelua_print_1(str);
    nelua_nlstring_destroy((&str));
    nelua_print_1(str);
  }
  return 0;
}
int main(int argc, char** argv) {
  return nelua_main(argc, argv);
}

