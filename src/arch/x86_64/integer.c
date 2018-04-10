
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <math.h>
#include <assert.h>

#include <Foxlang.h>


BaseObject * IntegerObject_Fromstring(char * value){
	IntegerObject * a = IntegerObject_Init(0);

	#ifdef ENV64BIT
	a->value = strtoull(value, NULL, 10);
	#endif
	#ifdef ENV32BIT
	a->value = strtoul(value, NULL, 10);
	#endif

	if(errno == ERANGE){
		//exception handler
	}
	return (BaseObject *)a;
}

char * IntegerObject_Repr(BaseObject * o_tmp){
	IntegerObject * o = (IntegerObject *)o_tmp;
	char * buffer = malloc(24 * sizeof(char));
	if(o->sign == -1){
		strcpy(buffer,"-");
		buffer++;
	}else{
		strcpy(buffer,"");
	}

	#ifdef ENV64BIT
	sprintf(buffer,"%lld", (long long)(o->value));
	#endif
	
	#ifdef ENV32BIT
	sprintf(buffer,"%ld", (long)(o->value));
	#endif

	if(o->sign == -1){
		buffer--;
	}
	return buffer;
}

BaseObject * IntegerObject_BinaryAdd(BaseObject * self_tmp,BaseObject * other_tmp){
	if(!OBJCHECKTYPE(self_tmp,"integer")){
		//exception handler
	}
	IntegerObject * self = (IntegerObject *)self_tmp; 
	if(OBJCHECKTYPE(other_tmp,"integer")){
		IntegerObject * other = (IntegerObject *)other_tmp; 
		IntegerObject * new = IntegerObject_Init(0);
		new->value = self->value + other->value;		
		return (BaseObject *)new;
	}else if(OBJCHECKTYPE(other_tmp,"float")){//float
		
	}else{
		//exception handler
	}
	return NULL;
}

HASH IntegerObject_Hash(BaseObject * self_tmp){
	if(!OBJCHECKTYPE(self_tmp,"integer")){
		//exception handler
	}
	IntegerObject * self = (IntegerObject *)self_tmp;
	HASH hash = self->value * self->sign;
	return hash;
}

BaseObject * IntegerObject_UnaryNegate(BaseObject * self_tmp){
	if(!OBJCHECKTYPE(self_tmp,"integer")){
		//exception handler
	}
	IntegerObject * self = (IntegerObject *)self_tmp; 
	IntegerObject * new = IntegerObject_Init(-(self->value));
	return (BaseObject *)new;
}



BaseObject * IntegerObject_Fromlong(long value){
	IntegerObject * o = IntegerObject_Init(0);
	
	if(value < 0){
		value = -value;
		o->sign = -1;
	}

	o->value = (IntegerObject_basedatatype)value;
	return (BaseObject *)o;
}

long IntegerObject_Tolong(BaseObject * o_tmp){
	IntegerObject * o = (IntegerObject *)o_tmp; 
	return o->value*o->sign;
}


void IntegerObject_DESTRUCT(BaseObject * self_tmp){
	IntegerObject * self = (IntegerObject *)self_tmp;
	printf("integer <%p> deleting itself\n",self_tmp);
	free(self);
}


NumberMethods IntegerObject_NumberMethods = {
	//normal
		//arithmetic
		IntegerObject_BinaryAdd,	// add
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
	IntegerObject_UnaryNegate,	// neg;
	0,	// inv;
};


TypeObject IntegerType = {
	VarBaseObject_HEAD_INIT(&BaseObjectType,0)
	"integer",										//typename
	sizeof (IntegerObject),							//startsize
	0,												//itemsize
	&IntegerObject_DESTRUCT,						//destructor!
	&IntegerObject_NumberMethods,					//numbermethods
	&IntegerObject_Hash,							//hash
};

IntegerObject * IntegerObject_Init(IntegerObject_basedatatype value){
	IntegerObject * a = malloc(sizeof(IntegerObject));
	
	if(value == 0){
		*a = (IntegerObject) {
			BaseObject_HEAD_INIT(&IntegerType)
			0,
			1
		};
		return a;
	}
	int sign = 1;
	if(value < 0){
		value = -value;
		sign = -1;
	}

	*a = (IntegerObject) {
		BaseObject_HEAD_INIT(&IntegerType)
		(IntegerObject_basedatatype)value,
		sign
	};

	return a;
}