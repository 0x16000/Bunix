#ifndef _SYS_CDEFS_H
#define _SYS_CDEFS_H 1

/* Macro to identify the compiler */
#if defined(__GNUC__)
# define __GNUC_PREREQ(maj, min) \
    ((__GNUC__ << 16) + __GNUC_MINOR__ >= ((maj) << 16) + (min))
#else
# define __GNUC_PREREQ(maj, min) 0
#endif

/* Compiler feature macros */
#define __CONCAT(x,y)   x ## y
#define __STRING(x)     #x

/* Attribute macros */
#if __GNUC_PREREQ(2,5)
# define __attribute__(x) __attribute__(x)
#else
# define __attribute__(x)
#endif

/* Visibility control */
#if __GNUC_PREREQ(4,0)
# define __visible      __attribute__((__visibility__("default")))
# define __hidden       __attribute__((__visibility__("hidden")))
#else
# define __visible
# define __hidden
#endif

/* Alignment control */
#if __GNUC_PREREQ(2,95)
# define __aligned(x)   __attribute__((__aligned__(x)))
#else
# define __aligned(x)
#endif

/* Function inlining */
#if __GNUC_PREREQ(3,1)
# define __always_inline inline __attribute__((__always_inline__))
#else
# define __always_inline inline
#endif

/* Pure/const functions */
#if __GNUC_PREREQ(2,96)
# define __pure         __attribute__((__pure__))
# define __const        __attribute__((__const__))
#else
# define __pure
# define __const
#endif

/* Non-returning functions */
#if __GNUC_PREREQ(2,5)
# define __noreturn     __attribute__((__noreturn__))
#else
# define __noreturn
#endif

/* Deprecated functions */
#if __GNUC_PREREQ(3,1)
# define __deprecated   __attribute__((__deprecated__))
#else
# define __deprecated
#endif

/* Weak symbols */
#if __GNUC_PREREQ(4,0)
# define __weak         __attribute__((__weak__))
#else
# define __weak
#endif

/* Symbol section control */
#if __GNUC_PREREQ(4,0)
# define __section(s)   __attribute__((__section__(#s)))
#else
# define __section(s)
#endif

/* C++ compatibility */
#ifdef __cplusplus
# define __BEGIN_DECLS  extern "C" {
# define __END_DECLS    }
# define __THROW        throw()
#else
# define __BEGIN_DECLS
# define __END_DECLS
# define __THROW
#endif

/* Pointer authentication (for ARMv8.3+) */
#if defined(__ARM_FEATURE_PAC_DEFAULT) && __GNUC_PREREQ(9,0)
# define __ptrauth(x)   __attribute__((__ptrauth__(x)))
#else
# define __ptrauth(x)
#endif

/* Branch prediction hints */
#if __GNUC_PREREQ(3,0)
# define __likely(x)    __builtin_expect(!!(x), 1)
# define __unlikely(x)  __builtin_expect(!!(x), 0)
#else
# define __likely(x)    (x)
# define __unlikely(x)  (x)
#endif

/* Offsetof macro */
#ifndef __offsetof
# if __GNUC_PREREQ(4,1)
#  define __offsetof(type, member) __builtin_offsetof(type, member)
# else
#  define __offsetof(type, member) ((size_t) &((type *)0)->member)
# endif
#endif

/* Static assertion */
#if __GNUC_PREREQ(4,6) || defined(__clang__)
# define __static_assert(expr, msg) _Static_assert(expr, msg)
#else
# define __static_assert(expr, msg) \
    typedef char __CONCAT(__static_assert_, __LINE__)[(expr) ? 1 : -1]
#endif

/* Byte order macros */
#define __LITTLE_ENDIAN 1234
#define __BIG_ENDIAN    4321
#define __PDP_ENDIAN    3412

#if defined(__i386__) || defined(__x86_64__) || defined(__arm__) || defined(__aarch64__)
# define __BYTE_ORDER __LITTLE_ENDIAN
#elif defined(__m68k__) || defined(__powerpc__) || defined(__sparc__)
# define __BYTE_ORDER __BIG_ENDIAN
#else
# error "Unknown architecture byte order"
#endif

/* Macro to prevent unused variable warnings */
#define __unused        __attribute__((__unused__))

/* Macro for packed structures */
#define __packed        __attribute__((__packed__))

/* Macro for aligned structures */
#define __aligned(x)    __attribute__((__aligned__(x)))

/* Macro for section placement */
#define __section(s)    __attribute__((__section__(#s)))

#endif /* _SYS_CDEFS_H */
