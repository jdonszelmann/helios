#ifndef STRING_H
#define STRING_H


typedef struct{
	Object_immutable_HEAD;
	char * value;
	HASH statichash;
}StringObject;

StringObject * StringObject_Init();
BaseObject * StringObject_Repr(BaseObject * o_tmp);
char * StringObject_Repr_CHARPNT(BaseObject * o_tmp);
BaseObject * StringObject_Str(BaseObject * o_tmp);
char * StringObject_Str_CHARPNT(BaseObject * o_tmp);
BaseObject * StringObject_Fromstring(char * value);
BaseObject * StringObject_Fromformat(char * format,...);
void StringObject_DESTRUCT(BaseObject * self_tmp);


BaseObject * StringObject_BinaryEQ(BaseObject * self_tmp,BaseObject * other_tmp);
BaseObject * StringObject_UnaryBool(BaseObject * self_tmp);

TypeObject StringType;
NumberMethods StringObject_NumberMethods;


#endif