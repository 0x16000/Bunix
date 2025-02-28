#ifndef TYPES_H
#define TYPES_H

// Ensure fixed-width types for portability
typedef signed char        int8_t;
typedef unsigned char      uint8_t;
typedef short              int16_t;
typedef unsigned short     uint16_t;
typedef int                int32_t;
typedef unsigned int       uint32_t;
typedef long long          int64_t;
typedef unsigned long long uint64_t;

// Size type (usually defined by the compiler)
typedef unsigned int       size_t;  // Or you could use unsigned long or unsigned long long

// Pointer types for holding pointer values
typedef intptr_t           intptr;  // Integer type large enough to hold a pointer
typedef uintptr_t          uintptr; // Unsigned integer type large enough to hold a pointer

#endif // TYPES_H
