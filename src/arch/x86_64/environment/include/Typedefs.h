
#ifndef TYPEDEFS_H
#define TYPEDEFS_H


// Check windows
#if _WIN32 || _WIN64
   #if _WIN64
     #define ENV64BIT
  #else
    #define ENV32BIT
  #endif
#endif

// Check GCC
#if __GNUC__
  #if __x86_64__ || __ppc64__
    #define ENV64BIT
  #else
    #define ENV32BIT
  #endif
#endif

#include <stdint.h>

struct baseobj;


#ifdef ENV64BIT
typedef uint64_t IntegerObject_basedatatype;
#endif
#ifdef ENV32BIT
typedef uint32_t IntegerObject_basedatatype;
#endif

typedef int Refcount;
typedef int ObjectSize;
typedef void (*destructor)(struct baseobj *);

#endif