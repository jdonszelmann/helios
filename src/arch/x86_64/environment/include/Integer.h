#ifndef INTEGER_H
#define INTEGER_H

#include <Foxlang.h>


typedef struct{
	Object_immutable_HEAD;
	IntegerObject_basedatatype value;
	int sign;
}IntegerObject;

IntegerObject * IntegerObject_Init();
char * IntegerObject_Repr_CHARPNT(BaseObject * o_tmp);
BaseObject * IntegerObject_Fromstring(char * value);
void IntegerObject_DESTRUCT(BaseObject * self_tmp);
HASH IntegerObject_Hash(BaseObject * self_tmp);

BaseObject * IntegerObject_BinaryAdd(BaseObject * self,BaseObject * other);
BaseObject * IntegerObject_BinaryEQ(BaseObject * self_tmp,BaseObject * other_tmp);
BaseObject * IntegerObject_UnaryNegate(BaseObject * self);
BaseObject * IntegerObject_UnaryBool(BaseObject * self_tmp);

TypeObject IntegerType;
NumberMethods IntegerObject_NumberMethods;

BaseObject * IntegerObject_Fromlong(long value);
long IntegerObject_Tolong(BaseObject * o);

#endif