#ifndef OBJECT_H
#define OBJECT_H
#include <string.h>
#include <Foxlang.h>

typedef int HASH;
typedef HASH (*hashgenerator)(struct baseobj *);

typedef enum {
	EQ=0,
	NEQ=1,
	LT=2,
	GT=3,
	LTE=4,
	GTE=5,
} COMPARISON_OPERATOR;

COMPARISON_OPERATOR REVERSE_COMPARISON_OPERATOR[6];



#define Object_immutable_HEAD 	Refcount object_refcount; \
								struct typeobj * object_type; \
								int _static;

#define Object_mutable_HEAD 	Object_immutable_HEAD; \
								ObjectSize object_size;

#define BaseObject_HEAD_INIT(type)        \
			1,type,0,


#define VarBaseObject_HEAD_INIT(type, size) \
			BaseObject_HEAD_INIT(type) size,

#define OBJREFCOUNT(o) 	((BaseObject 	*)	o)	->object_refcount
#define OBJSIZE(o)		((VarBaseObject *)	o)	->object_size
#define OBJTYPE(o) 		((BaseObject 	*)	o)	->object_type
#define ITEMSIZE(o)		(OBJTYPE(o)				->item_size)

struct numbermethods;

typedef struct baseobj{
	Object_immutable_HEAD;
}BaseObject;

typedef struct varbaseobj{
	Object_mutable_HEAD;
}VarBaseObject;


typedef struct typeobj{
	Object_mutable_HEAD;

	char * typename;

	size_t start_size, item_size;

	destructor destruct_object;
	// getattrfunc getattribute;
	// setattrfunc setattribute;

	//comparemethods
	struct comparemethods * compare;
	struct numbermethods * number; //numbermethods
	struct itermethods * iter;
	//methods
	hashgenerator generate_hash; //hash
	//call(able)
	//str
	UnaryOperator reprfunction; //repr
	//docstring?

	//dict
	BaseObject * __dict__;

	//instance init (__init__)

	//garbage collector things

	//inheritance (bases,mro)

	//allocs, frees (testing)

}TypeObject;


TypeObject BaseObjectType;
TypeObject VarBaseObjectType;


#define DECREF(o_tmp)										\
		do{													\
			BaseObject * __o = (BaseObject *)o_tmp;			\
			__o->object_refcount--;							\
			if(__o->object_refcount <= 0 && !__o->_static)	\
				BaseObject_Dealloc(o_tmp);					\
		}while(0)

#define INCREF(o_tmp)									\
		do{												\
			BaseObject * __o = (BaseObject *)o_tmp;		\
			__o->object_refcount++;						\
		}while(0)

// int OBJCHECKTYPE(BaseObject * o, char * type);
#define OBJCHECKTYPE(o,type) strcmp(o->object_type->typename,type) == 0
			
BaseObject * BaseObject_Compare_NEQ(BaseObject * a, BaseObject * b);
BaseObject * BaseObject_Compare_EQ(BaseObject * a, BaseObject * b);
BaseObject * BaseObject_Compare_LT(BaseObject * a, BaseObject * b);
BaseObject * BaseObject_Compare_LTE(BaseObject * a, BaseObject * b);
BaseObject * BaseObject_Compare_GT(BaseObject * a, BaseObject * b);
BaseObject * BaseObject_Compare_GTE(BaseObject * a, BaseObject * b);

BaseObject * BaseObject_Compare(BaseObject * a, BaseObject * b,COMPARISON_OPERATOR op);
int BaseObject_Compare_BOOL(BaseObject * a, BaseObject * b,COMPARISON_OPERATOR op);

char * BaseObject_Repr_CHARPNT(BaseObject * self);
BaseObject * BaseObject_Repr(BaseObject * self);

void BaseObject_PRINTFUNC(BaseObject * self);

HASH BaseObject_Hash_HASH(BaseObject * self);
BaseObject * BaseObject_Hash(BaseObject * self);

BaseObject * BaseObject_AsInteger(BaseObject * o);

inline BaseObject * STATIC(BaseObject * a){
	a->_static=1;
	return a;
}

BaseObject * BaseObject_Iter(BaseObject * self);
BaseObject * BaseObject_IterNext(BaseObject * self);
BaseObject * BaseObject_IterPrev(BaseObject * self);

#endif