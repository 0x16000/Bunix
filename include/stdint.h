#ifndef STDINT_H
#define STDINT_H

// Signed integer types
typedef signed char        int8_t;
typedef signed short       int16_t;
typedef signed int         int32_t;
typedef signed long long   int64_t;

// Unsigned integer types
typedef unsigned char      uint8_t;
typedef unsigned short     uint16_t;
typedef unsigned int       uint32_t;
typedef unsigned long long uint64_t;

// Integer types capable of holding pointers
typedef int32_t            intptr_t;
typedef uint32_t           uintptr_t;

// Maximum size of a type, defined by the compiler's word size
typedef unsigned long      size_t;

// Integer constants for portability
#define INT8_MIN   (-128)
#define INT8_MAX   (127)
#define UINT8_MAX  (255)

#define INT16_MIN  (-32768)
#define INT16_MAX  (32767)
#define UINT16_MAX (65535)

#define INT32_MIN  (-2147483648)
#define INT32_MAX  (2147483647)
#define UINT32_MAX (4294967295)

#define INT64_MIN  (-9223372036854775808LL)
#define INT64_MAX  (9223372036854775807LL)
#define UINT64_MAX (18446744073709551615ULL)

// NULL pointer constant
#ifndef NULL
#define NULL ((void*)0)
#endif

#endif // STDINT_H

