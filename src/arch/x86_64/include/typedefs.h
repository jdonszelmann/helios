
#ifndef TYPEDEFS_H
#define TYPEDEFS_H


struct baseobj;

typedef int Refcount;
typedef int ObjectSize;
typedef void (*destructor)(struct baseobj *);

#endif