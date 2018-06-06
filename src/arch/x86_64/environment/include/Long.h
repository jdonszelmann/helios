#ifndef Long_H
#define Long_H

#include <Foxlang.h>


typedef struct{
	Object_immutable_HEAD;
	unsigned char * value;
	size_t size;
	int sign;
}LongObject;

LongObject * LongObject_Init();
char * LongObject_Repr_CHARPNT(BaseObject * o_tmp);
BaseObject * LongObject_Fromstring(char * value);
void LongObject_DESTRUCT(BaseObject * self_tmp);
HASH LongObject_Hash(BaseObject * self_tmp);

BaseObject * LongObject_BinaryAdd(BaseObject * self,BaseObject * other);
BaseObject * LongObject_BinaryEQ(BaseObject * self_tmp,BaseObject * other_tmp);
BaseObject * LongObject_UnaryNegate(BaseObject * self);
BaseObject * LongObject_UnaryBool(BaseObject * self_tmp);

TypeObject LongType;
NumberMethods LongObject_NumberMethods;

BaseObject * LongObject_Fromlong(long value);
long LongObject_Tolong(BaseObject * o);

#endif