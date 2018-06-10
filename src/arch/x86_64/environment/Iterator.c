#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <math.h>
#include <assert.h>
#include <stdarg.h>
#include <stdbool.h>

#include <Foxlang.h>

BaseObject * IteratorObject_Create(BaseObject * o){
	IteratorObject * it = IteratorObject_Init();
	INCREF(o);
	it->iterating=o;
	return (BaseObject *)it;
}

char * IteratorObject_Repr_CHARPNT(BaseObject * self_tmp){
	return DefaultRepr(self_tmp);
}

BaseObject * IteratorObject_Repr(BaseObject * self_tmp){
	char * res = IteratorObject_Repr_CHARPNT(self_tmp);
	BaseObject * str = StringObject_Fromstring(res);
	free(res);
	return (BaseObject *)str;
}

char * IteratorObject_Str_CHARPNT(BaseObject * self_tmp){
	return IteratorObject_Repr_CHARPNT(self_tmp);
}

BaseObject * IteratorObject_Str(BaseObject * self_tmp){
	return IteratorObject_Repr(self_tmp);
}

BaseObject * IteratorObject_BinaryEQ(BaseObject * self_tmp,BaseObject * other_tmp){
	IteratorObject * self = (IteratorObject *)self_tmp; 
	if(OBJCHECKTYPE(other_tmp,"Iterator")){
		IteratorObject * other = (IteratorObject *)other_tmp; 
		if(self->index == other->index){
			return True;
		}else{
			return False;
		}
	}else{
		return False;
	}
}


BaseObject * IteratorObject_UnaryBool(BaseObject * self_tmp){
	return True;
}

BaseObject * IteratorObject_iter(BaseObject * self_tmp){
	return IteratorObject_Create(self_tmp);
}

BaseObject * IteratorObject_iternext(BaseObject * self_tmp){
	IteratorObject * self = (IteratorObject *)self_tmp;
	if(OBJTYPE(self)->iter!=NULL && OBJTYPE(self)->iter->iternext!=NULL){
		BaseObject * res = OBJTYPE(self->iterating)->iter->iternext((BaseObject *)self);
		INCREF(res);
		self->index++;
		return res;
	}else{
		RAISE(ExceptionObject_FromCHARPNT("TypeError. object not iterable"));
	}
}

BaseObject * IteratorObject_iterprev(BaseObject * self_tmp){
	IteratorObject * self = (IteratorObject *)self_tmp;
	if(OBJTYPE(self)->iter!=NULL && OBJTYPE(self)->iter->iternext!=NULL){
		self->index--;
		BaseObject * res = OBJTYPE(self->iterating)->iter->iternext((BaseObject *)self);
		INCREF(res);
		return res;
	}else{
		RAISE(ExceptionObject_FromCHARPNT("TypeError. object not iterable"));
	}
}

CompareMethods IteratorObject_Compare = {
	IteratorObject_BinaryEQ,	// EQ
	0,	// NEQ
	0,	// LT
	0,	// GT
	0,	// LTE
	0,	// GTE
	IteratorObject_UnaryBool,	// ASBOOL
};

IterMethods IteratorObject_Iter = {
	0,									//length
	
	0,
	0,

	0,
	0,
	0,

	0,
	0,

	0,

	&IteratorObject_iter,				//iter
	&IteratorObject_iternext,			//iternext
	&IteratorObject_iterprev,			//iterprev
};

void IteratorObject_DESTRUCT(BaseObject * self_tmp){
	IteratorObject * self = (IteratorObject *)self_tmp;
	DECREF(self->iterating);
	free(self);
}

TypeObject IteratorType = {
	VarBaseObject_HEAD_INIT(&BaseObjectType,0)
	"Iterator",										//typename
	sizeof (IteratorObject),						//startsize
	0,												//itemsize
	&IteratorObject_DESTRUCT,						//destructor!
	&IteratorObject_Compare,						//comparemethods
	0,												//numbermethods
	&IteratorObject_Iter,							//itermethods
	0,												//hash
	&IteratorObject_Repr,							//repr
};


IteratorObject * IteratorObject_Init(){
	IteratorObject * a = malloc(sizeof(IteratorObject));
	
	*a = (IteratorObject) {
		BaseObject_HEAD_INIT(&IteratorType)
		NULL,
		0,
	};
	Fox_Initialize_Object((BaseObject *)a);
	return a;
}