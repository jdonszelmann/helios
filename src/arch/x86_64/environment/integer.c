
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <math.h>
#include <assert.h>

#include <Foxlang.h>


BaseObject * IntegerObject_Fromstring(char * value){
	IntegerObject * a = IntegerObject_Init();

	#ifdef ENV64BIT
	a->value = strtoull(value, NULL, 10);
	#endif
	#ifdef ENV32BIT
	a->value = strtoul(value, NULL, 10);
	#endif

	if(errno == ERANGE){
		RAISE(ExceptionObject_FromCHARPNT("TypeError. integer out of range (use longs or wait till i implemented autoconversion............)"));
	}
	return (BaseObject *)a;
}

char * IntegerObject_Repr_CHARPNT(BaseObject * o_tmp){
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

BaseObject * IntegerObject_Repr(BaseObject * o_tmp){
	char * res = IntegerObject_Repr_CHARPNT(o_tmp);
	BaseObject * str = StringObject_Fromstring(res);
	free(res);
	return str;
}

BaseObject * IntegerObject_BinaryAdd(BaseObject * self_tmp,BaseObject * other_tmp){
	IntegerObject * self = (IntegerObject *)self_tmp; 
	if(OBJCHECKTYPE(other_tmp,"integer")){
		IntegerObject * other = (IntegerObject *)other_tmp; 
		IntegerObject * new = IntegerObject_Init();
		new->value = self->value + other->value;		
		return (BaseObject *)new;
	}else if(OBJCHECKTYPE(other_tmp,"float")){//float
		RAISE(ExceptionObject_FromCHARPNT("TypeError. int-float addition not supported (yet)"));
	}else{
		RAISE(ExceptionObject_FromCHARPNT("TypeError. invalid type for addition"));
	}
	return NULL;
}


BaseObject * IntegerObject_BinaryEQ(BaseObject * self_tmp,BaseObject * other_tmp){
	IntegerObject * self = (IntegerObject *)self_tmp; 
	if(OBJCHECKTYPE(other_tmp,"integer")){
		IntegerObject * other = (IntegerObject *)other_tmp; 
		if(self->value == other->value){
			return True;
		}else{
			return False;
		}
	}else if(OBJCHECKTYPE(other_tmp,"float")){//float
		RAISE(ExceptionObject_FromCHARPNT("TypeError. int-float comparison not supported (yet)"));	
	}else{
		return False;
	}
	return NULL;
}



HASH IntegerObject_Hash(BaseObject * self_tmp){
	if(!OBJCHECKTYPE(self_tmp,"integer")){
		RAISE(ExceptionObject_FromCHARPNT("TypeError. wrong function."));
	}
	IntegerObject * self = (IntegerObject *)self_tmp;
	HASH hash = self->value * self->sign;
	return hash;
}

BaseObject * IntegerObject_UnaryNegate(BaseObject * self_tmp){
	if(!OBJCHECKTYPE(self_tmp,"integer")){
		RAISE(ExceptionObject_FromCHARPNT("TypeError. wrong function."));
	}
	IntegerObject * self = (IntegerObject *)self_tmp; 
	IntegerObject * new = IntegerObject_Init();
	new->value = self->value;
	new->sign = -self->sign;
	return (BaseObject *)new;
}


BaseObject * IntegerObject_UnaryBool(BaseObject * self_tmp){
	if(!OBJCHECKTYPE(self_tmp,"integer")){
		RAISE(ExceptionObject_FromCHARPNT("TypeError. wrong function."));
	}
	IntegerObject * self = (IntegerObject *)self_tmp;
	if(self->value == 0){
		return False;
	}
	return True;
}


BaseObject * IntegerObject_Fromlong(long value){
	IntegerObject * o = IntegerObject_Init();
	
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
	if(self_tmp == NULL){
		return;
	}
	IntegerObject * self = (IntegerObject *)self_tmp;
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

CompareMethods IntegerObject_Compare = {
	IntegerObject_BinaryEQ,	// EQ
	0,	// NEQ
	0,	// LT
	0,	// GT
	0,	// LTE
	0,	// GTE
	IntegerObject_UnaryBool,	// ASBOOL
};


TypeObject IntegerType = {
	VarBaseObject_HEAD_INIT(&BaseObjectType,0)
	"integer",										//typename
	sizeof (IntegerObject),							//startsize
	0,												//itemsize
	&IntegerObject_DESTRUCT,						//destructor!
	&IntegerObject_Compare,							//comparemethods
	&IntegerObject_NumberMethods,					//numbermethods
	0,												//itermethods
	&IntegerObject_Hash,							//hash
	&IntegerObject_Repr,							//repr
};


IntegerObject * IntegerObject_Init(){
	IntegerObject * a = malloc(sizeof(IntegerObject));
	
	*a = (IntegerObject) {
		BaseObject_HEAD_INIT(&IntegerType)
		0,
		1
	};
	Fox_Initialize_Object((BaseObject *)a);
	return a;
}