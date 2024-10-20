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
#include <math.h>
#define NELUA_NIL (nlniltype){}
#include <stdint.h>
#include <stdio.h>
/* ------------------------------ DECLARATIONS ------------------------------ */
static NELUA_INLINE double nelua_math_floor_1(double x);
static NELUA_INLINE double nelua_math_sqrt_1(double x);
typedef struct nlniltype {} nlniltype;
typedef struct nlniltype nltype;
static int64_t examples_fibonacci_fibonacci(int64_t n);
static void nelua_print_1(int64_t a1);
static int64_t examples_fibonacci_fibonacci_1(int64_t n, int64_t current, int64_t next);
static int64_t examples_fibonacci_fibonacci_2(int64_t n);
static int64_t examples_fibonacci_fibonacci_3(int64_t n);
static int nelua_main(int argc, char** argv);
/* ------------------------------ DEFINITIONS ------------------------------- */
double nelua_math_floor_1(double x) {
  return floor(x);
}
double nelua_math_sqrt_1(double x) {
  return sqrt(x);
}
int64_t examples_fibonacci_fibonacci(int64_t n) {
  if((n <= 2)) {
    return 1;
  }
  return (examples_fibonacci_fibonacci((n - 1)) + examples_fibonacci_fibonacci((n - 2)));
}
void nelua_print_1(int64_t a1) {
  fprintf(stdout, "%lli", (long long)a1);
  fputs("\n", stdout);
  fflush(stdout);
}
int64_t examples_fibonacci_fibonacci_1(int64_t n, int64_t current, int64_t next) {
  if((n == 0)) {
    return current;
  }
  return examples_fibonacci_fibonacci_1((n - 1), next, (current + next));
}
int64_t examples_fibonacci_fibonacci_2(int64_t n) {
  int64_t first = 0;
  int64_t second = 1;
  for(int64_t i = 1, _end = n; i <= _end; i += 1) {
    int64_t _asgntmp_1 = second;
    int64_t _asgntmp_2 = first;
    first = _asgntmp_1;
    second = _asgntmp_2;
    second = (second + first);
  }
  return first;
}
int64_t examples_fibonacci_fibonacci_3(int64_t n) {
  double p = ((1.0 + nelua_math_sqrt_1(5.0)) / 2.0);
  double q = (1.0 / p);
  return (int64_t)nelua_math_floor_1(((pow(p, n) + pow(q, n)) / nelua_math_sqrt_1(5.0)));
}
int nelua_main(int argc, char** argv) {
  {
    nelua_print_1(examples_fibonacci_fibonacci(10));
  }
  {
    nelua_print_1(examples_fibonacci_fibonacci_1(10, 0, 1));
  }
  {
    nelua_print_1(examples_fibonacci_fibonacci_2(10));
  }
  {
    nelua_print_1(examples_fibonacci_fibonacci_3(10));
  }
  return 0;
}
int main(int argc, char** argv) {
  return nelua_main(argc, argv);
}

