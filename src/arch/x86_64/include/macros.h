
#ifndef MACROS_H
#define MACROS_H

#include <stdio.h>
#include <stdlib.h>
#include <Foxlang.h>

#define Object_immutable_HEAD 	Refcount object_refcount; \
								struct typeobj * object_type;

#define Object_mutable_HEAD 	Object_immutable_HEAD; \
								ObjectSize object_size;

#define BaseObject_HEAD_INIT(type)        \
			1, type,


#define VarBaseObject_HEAD_INIT(type, size) \
			BaseObject_HEAD_INIT(type) size,

#define OBJREFCOUNT (((BaseObject*)(o))		->object_type_refcount)
#define OBJSIZE 	(((VarBaseObject*)(o))	->object_type)
#define OBJTYPE 	(((BaseObject*)(o))		->object_type)


#endif