#ifndef _STDDEF_H
#define _STDDEF_H

/* Basic type definitions */

/* Check if these types are already defined to avoid conflicts with GCC */
#ifndef uint8_t
typedef unsigned char   uint8_t;
#endif

#ifndef uint16_t
typedef unsigned short  uint16_t;
#endif

#ifndef uint32_t
typedef unsigned int    uint32_t;
#endif

#ifndef uint64_t
typedef unsigned long   uint64_t;
#endif

#ifndef int8_t
typedef signed char     int8_t;
#endif

#ifndef int16_t
typedef signed short    int16_t;
#endif

#ifndef int32_t
typedef signed int      int32_t;
#endif

#ifndef int64_t
typedef signed long     int64_t;
#endif

#ifndef size_t
typedef unsigned long   size_t;
#endif

#ifndef wchar_t
typedef unsigned int wchar_t;
#endif

#ifndef ptrdiff_t
typedef int             ptrdiff_t;
#endif

/* Null pointer constant */
#ifndef NULL
#define NULL ((void*)0)
#endif

/* Maximum values for integer types */
#ifndef SIZE_MAX
#define SIZE_MAX ((size_t)-1)
#endif

#ifndef PTRDIFF_MAX
#define PTRDIFF_MAX ((ptrdiff_t)(~((ptrdiff_t)1 << (8 * sizeof(ptrdiff_t) - 1))))
#endif

#ifndef PTRDIFF_MIN
#define PTRDIFF_MIN ((ptrdiff_t)(1 << (8 * sizeof(ptrdiff_t) - 1)))
#endif

/* Pointer arithmetic macros */
#define offsetof(type, member)  __builtin_offsetof(type, member)

/* Align macro for specific data types */
#define ALIGN_UP(x, align)  (((x) + (align) - 1) & ~((align) - 1))
#define ALIGN_DOWN(x, align) ((x) & ~((align) - 1))

/* Type macros */
#define sizeof_array(arr) (sizeof(arr) / sizeof((arr)[0]))

/* Restrict keyword */
#define restrict __restrict

/* For those who want to enforce compiler optimizations */
#define likely(x)   __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)

/* Atomic Operations (if needed, for OS-level atomic operations) */
#define atomic_compare_exchange(ptr, old_val, new_val) \
    __sync_bool_compare_and_swap(ptr, old_val, new_val)

/* Compiler-specific macros */
#define _Alignas(n)   __attribute__((aligned(n)))
#define _Alignof(t)   __alignof__(t)

/* Useful constant */
#define offsetof(type, member) __builtin_offsetof(type, member)

/* For dealing with function pointers */
typedef void (*void_fn_t)(void);
typedef int (*int_fn_t)(int);

#endif /* _STDDEF_H */
