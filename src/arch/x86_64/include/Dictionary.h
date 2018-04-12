
#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <Foxlang.h>

#define DICTIONARY_DEFAULT_STARTSIZE 16

typedef struct{
	BaseObject * key;
	BaseObject * value;
	HASH keyhash;
	char filled;
}DictionaryObjectPair;

typedef struct{
	Object_mutable_HEAD;
	DictionaryObjectPair * values;
}DictionaryObject;

DictionaryObject * DictionaryObject_Init();
void DictionaryObject_DESTRUCT(BaseObject * self_tmp);
void DictionaryObject_RESIZE(BaseObject * self_tmp,unsigned int size);
char * IntegerObject_Repr_CHARPNT(BaseObject * self_tmp);

void DictionaryObject_Insert(BaseObject * self_tmp, BaseObject * key, BaseObject * value);

TypeObject DictionaryType;


#endif









