#ifndef OBJECT_H
#define OBJECT_H

typedef struct typeobj{
	Object_mutable_HEAD;

	char * typename;

	size_t start_size, item_size;

	destructor destruct_object;
	// getattrfunc getattribute;
	// setattrfunc setattribute;

	//comparemethods
	//numbermethods
	//sequencemethods (iterator)
	//methods
	//hash
	//call(able)
	//str
	//repr
	//docstring?

	//dict

	//instance init (__init__)

	//garbage collector things

	//inheritance (bases,mro)

	//allocs, frees (testing)

}TypeObject;

typedef struct baseobj{
	Object_immutable_HEAD;
}BaseObject;

typedef struct varbaseobj{
	Object_mutable_HEAD;
}VarBaseObject;

TypeObject BaseObjectType;
TypeObject VarBaseObjectType;


#define DECREF(o_tmp)									\
		do{												\
			BaseObject * o = (BaseObject *)o_tmp;		\
			o->object_refcount--;						\
			if(o->object_refcount <= 0)					\
				BaseObject_Dealloc(o_tmp);				\
		}while(0)

#define INCREF(o_tmp)									\
		do{												\
			BaseObject * o = (BaseObject *)o_tmp;		\
			o->object_refcount++;						\
		}while(0)


// void DECREF(BaseObject * o);

// void INCREF(BaseObject * o);

#endif