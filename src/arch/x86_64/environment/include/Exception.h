#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <Foxlang.h>

typedef struct{
	Object_immutable_HEAD;
	char * message;
}ExceptionObject;

#define RAISE(X) OBJCHECKTYPE(X,"Exception")?(printf("%s\n",((ExceptionObject *)(X))->message),exit(0)):(printf("TypeError: exceptions must be of type Exception"),exit(0))


ExceptionObject * ExceptionObject_Init();
char * ExceptionObject_Repr_CHARPNT(BaseObject * o_tmp);
BaseObject * ExceptionObject_Fromstring(char * value);
void ExceptionObject_DESTRUCT(BaseObject * self_tmp);
// HASH ExceptionObject_Hash(BaseObject * self_tmp);

TypeObject ExceptionType;

BaseObject * ExceptionObject_FromCHARPNT(char * value);
BaseObject * ExceptionObject_FromCHARPNT_FMT(char * value,...);
BaseObject * ExceptionObject_FromString(BaseObject * o);
char * ExceptionObject_ToCHARPNT(BaseObject * o);
BaseObject * ExceptionObject_ToString(BaseObject * o);



#endif