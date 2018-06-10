#ifndef DEFAULT_H
#define DEFAULT_H

#include <Foxlang.h>

inline char * DefaultRepr(BaseObject * o){
	BaseObject * res = StringObject_Fromformat("%s object at %p",OBJTYPE(o)->typename,o);
	char * str = StringObject_Str_CHARPNT(res);
	BaseObject_Dealloc(res);
	return str;
}

#endif
