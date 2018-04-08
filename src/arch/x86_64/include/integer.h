#ifndef INTEGER_H
#define INTEGER_H

#include <Foxlang.h>


typedef struct{
	Object_immutable_HEAD;
	char * value;
	int length;
	int sign;
}IntegerObject;

IntegerObject * IntegerObject_Init();
char * IntegerObject_Repr(BaseObject * o_tmp);
BaseObject * IntegerObject_Fromstring(char * value);

TypeObject IntegerType;

BaseObject * IntegerObject_Fromlong(unsigned long value);
unsigned long intIntegerObject_Tolong(BaseObject * o);

#endif