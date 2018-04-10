#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <math.h>
#include <assert.h>

#include <Foxlang.h>

NumberMethods DictionaryObject_NumberMethods = {
	//normal
		//arithmetic
		0,	// add
		0,	// sub
		0,	// div
		0,	// truediv
		0,	// mod
		0,	// mul
		0,	// pow

		//logic
		0,	// and
		0,	// or
		0,	// xor
		0,	// not
		0,	// rshift
		0,	// lshift

		//other

	//inplace
		//arithmetic
		0,	// iadd
		0,	// isub
		0,	// idiv
		0,	// itruediv
		0,	// imod
		0,	// imul
		0,	// ipow

		//logic
		0,	// iand
		0,	// ior
		0,	// ixor
		0,	// inot
		0,	// irshift
		0,	// ilshift

		//other

	//unary
	0,	// pos;
	0,	// neg;
	0,	// inv;
};


void DictionaryObject_RESIZE(BaseObject * self_tmp,unsigned int size){
	DictionaryObject * self = (DictionaryObject *)self_tmp;
	ITEMSIZE()
}

void DictionaryObject_DESTRUCT(BaseObject * self_tmp){
	DictionaryObject * self = (DictionaryObject *)self_tmp;
	printf("dictionary <%p> deleting itself\n",self_tmp);
	free(self->values);
	free(self);
}


TypeObject IntegerType = {
	VarBaseObject_HEAD_INIT(&BaseObjectType,0)
	"dictionary",									//typename
	sizeof (DictionaryObject),						//startsize
	0,												//itemsize
	&IntegerObject_DESTRUCT,						//destructor!
	&DictionaryObject_NumberMethods,				//numbermethods
	0,												//hash
};

DictionaryObject * DictionaryObject_Init(){
	DictionaryObject * a = malloc(sizeof(DictionaryObject));
	ITEMSIZE(a) = DICTIONARY_DEFAULT_STARTSIZE;

	*a = (DictionaryObject){
		VarBaseObject_HEAD_INIT(&DictionaryType,DICTIONARY_DEFAULT_STARTSIZE),
		malloc(DICTIONARY_DEFAULT_STARTSIZE*DictionaryObjectPair),
	}
	return a;
}


