
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <math.h>
#include <assert.h>
#include <stdbool.h>

#include <Foxlang.h>


TypeObject BooleanType = {
	VarBaseObject_HEAD_INIT(&BaseObjectType,0)
	"boolean",										//typename
	sizeof (BooleanObject),							//startsize
	0,												//itemsize
	&IntegerObject_DESTRUCT,						//destructor!	!CURRENTLY IMPLEMENTED AS INTEGER!
	0,												//comparemethods
	&IntegerObject_NumberMethods,					//numbermethods !CURRENTLY IMPLEMENTED AS INTEGER!
	0,												//hash
};


BaseObject * True = (BaseObject *)(&(BooleanObject){BaseObject_HEAD_INIT(&BooleanType)});
BaseObject * False = (BaseObject *)(&(BooleanObject){BaseObject_HEAD_INIT(&BooleanType)});

BaseObject * BooleanObject_FromBool(int value){
	if(!value){
		return False;
	}
	return True;
}

int BooleanObject_ToBool(BaseObject * o_tmp){
	BooleanObject * o = (BooleanObject *)o;
	return BOOLEAN_IS_TRUE(o);
}
