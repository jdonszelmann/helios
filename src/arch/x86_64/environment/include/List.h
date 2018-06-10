#ifndef LIST_H
#define LIST_H

#include <Foxlang.h>

typedef struct{
	Object_mutable_HEAD;
	BaseObject ** value;
	int size;
	int filled;
}ListObject;

ListObject * ListObject_Init();
BaseObject * ListObject_Repr(BaseObject * o_tmp);
char * ListObject_Repr_CHARPNT(BaseObject * o_tmp);
BaseObject * ListObject_Str(BaseObject * o_tmp);

void ListObject_Append(BaseObject * o_tmp, BaseObject * i);
void ListObject_Remove(BaseObject * o_tmp, BaseObject * i);
void ListObject_Removei(BaseObject * o_tmp, BaseObject * i);
void ListObject_Removei_int(BaseObject * o_tmp, int i);

BaseObject * ListObject_FromVARG(int size,...);

void ListObject_DESTRUCT(BaseObject * self_tmp);


BaseObject * ListObject_BinaryEQ(BaseObject * self_tmp,BaseObject * other_tmp);
BaseObject * ListObject_UnaryBool(BaseObject * self_tmp);

BaseObject * ListObject_GetItemAtint(BaseObject * self_tmp,int index);
BaseObject * ListObject_GetItemAt(BaseObject * self_tmp,BaseObject * index);


TypeObject ListType;


#endif