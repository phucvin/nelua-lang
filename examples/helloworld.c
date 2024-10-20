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
#include <stdint.h>
#include <stdio.h>
/* ------------------------------ DECLARATIONS ------------------------------ */
typedef struct nlstring nlstring;
typedef uint8_t* nluint8_arr0_ptr;
struct nlstring {
  nluint8_arr0_ptr data;
  uintptr_t size;
};
NELUA_STATIC_ASSERT(sizeof(nlstring) == 16 && NELUA_ALIGNOF(nlstring) == 8, "Nelua and C disagree on type size or align");
static void nelua_print_1(nlstring a1);
static int nelua_main(int argc, char** argv);
/* ------------------------------ DEFINITIONS ------------------------------- */
void nelua_print_1(nlstring a1) {
  if(a1.size > 0) {
    fwrite(a1.data, 1, a1.size, stdout);
  }
  fputs("\n", stdout);
  fflush(stdout);
}
int nelua_main(int argc, char** argv) {
  nelua_print_1(((nlstring){(uint8_t*)"hello world", 11}));
  return 0;
}
int main(int argc, char** argv) {
  return nelua_main(argc, argv);
}

