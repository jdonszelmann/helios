#ifndef STRING_H
#define STRING_H


typedef struct{
	Object_immutable_HEAD;
	char * value;
}StringObject;

StringObject * StringObject_Init();
char * StringObject_Repr_CHARPNT(BaseObject * o_tmp);
BaseObject * StringObject_Fromstring(char * value);
void StringObject_DESTRUCT(BaseObject * self_tmp);


BaseObject * StringObject_BinaryEQ(BaseObject * self_tmp,BaseObject * other_tmp);
BaseObject * StringObject_UnaryBool(BaseObject * self_tmp);

TypeObject StringType;
NumberMethods StringObject_NumberMethods;


#endif