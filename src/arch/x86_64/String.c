
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <math.h>
#include <assert.h>

#include <Foxlang.h>


BaseObject * StringObject_Fromstring(char * value){
	StringObject * a = StringObject_Init();
	OBJTYPE(a)->item_size = strlen(value);
	a->value = value;
	return (BaseObject *)a;
}

char * StringObject_Repr_CHARPNT(BaseObject * o_tmp){
	StringObject * o = (StringObject *)o_tmp;
	return o->value;
}


BaseObject * StringObject_BinaryEQ(BaseObject * self_tmp,BaseObject * other_tmp){
	if(!OBJCHECKTYPE(self_tmp,"string")){
		//exception handler
	}
	StringObject * self = (StringObject *)self_tmp; 
	if(OBJCHECKTYPE(other_tmp,"string")){
		StringObject * other = (StringObject *)other_tmp; 
		if(strcmp(self->value,other->value) == 0){
			return True;
		}else{
			return False;
		}
	}else{
		return False;
	}
}



HASH StringObject_Hash(BaseObject * self_tmp){
	if(!OBJCHECKTYPE(self_tmp,"string")){
		//exception handler
	}
	StringObject * self = (StringObject *)self_tmp;
	HASH hash = 0;//NOT IMPLEMENTED
	return hash;
}

BaseObject * StringObject_UnaryBool(BaseObject * self_tmp){
	if(!OBJCHECKTYPE(self_tmp,"string")){
		//exception handler
	}
	StringObject * self = (StringObject *)self_tmp;
	if(strlen(self->value) == 0){
		return False;
	}
	return True;
}


void StringObject_DESTRUCT(BaseObject * self_tmp){
	StringObject * self = (StringObject *)self_tmp;
	printf("string <%p> deleting itself\n",self_tmp);
	free(self->value);
	free(self);
}


CompareMethods StringObject_Compare = {
	StringObject_BinaryEQ,	// EQ
	0,	// NEQ
	0,	// LT
	0,	// GT
	0,	// LTE
	0,	// GTE
	StringObject_UnaryBool,	// ASBOOL
};


TypeObject StringType = {
	VarBaseObject_HEAD_INIT(&BaseObjectType,0)
	"string",										//typename
	sizeof (StringObject),							//startsize
	0,												//itemsize
	&StringObject_DESTRUCT,							//destructor!
	&StringObject_Compare,							//comparemethods
	0,												//numbermethods
	&StringObject_Hash,								//hash
};

StringObject * StringObject_Init(){
	StringObject * a = malloc(sizeof(StringObject));
	
	*a = (StringObject) {
		BaseObject_HEAD_INIT(&StringType)
		""
	};
	return a;
}