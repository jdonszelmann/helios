#ifndef ITERATOR_H
#define ITERATOR_H

typedef struct baseobj * (*IterFunc)(struct baseobj *);

typedef struct itermethods{
	UnaryFunc len;
	
	BinaryFunc concat;
	BinaryFunc repeat;

	BinaryFunc add;
	BinaryFunc remove;
	BinaryFunc removei;

	BinaryFunc getitem;
	TernaryFunc setitem;

	BinaryFunc contains;

	IterFunc iter;
	UnaryFunc iternext;
	UnaryFunc iterprev;

}IterMethods;

typedef struct{
	Object_immutable_HEAD;
	BaseObject * iterating;
	int index;
}IteratorObject;

TypeObject IteratorType;

void IteratorObject_DESTRUCT(BaseObject * self_tmp);
IteratorObject * IteratorObject_Init();

char * IteratorObject_Repr_CHARPNT(BaseObject * self_tmp);
BaseObject * IteratorObject_Repr(BaseObject * self_tmp);
BaseObject * IteratorObject_Str(BaseObject * self_tmp);
char * IteratorObject_Str_CHARPNT(BaseObject * self_tmp);

BaseObject * IteratorObject_BinaryEQ(BaseObject * self_tmp,BaseObject * other_tmp);
BaseObject * IteratorObject_UnaryBool(BaseObject * self_tmp);

BaseObject * IteratorObject_Create(BaseObject * o);
#endif