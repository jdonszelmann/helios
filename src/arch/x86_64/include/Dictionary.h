
#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <Foxlang.h>

#define DICTIONARY_DEFAULT_STARTSIZE 16

typedef struct{
	BaseObject * key;
	BaseObject * value;
	HASH keyhash;
}DictionaryObjectPair;

typedef struct{
	Object_mutable_HEAD;
	DictionaryObjectPair * values;
}DictionaryObject;

DictionaryObject * DictionaryObject_Init();
void DictionaryObject_DESTRUCT(BaseObject * self_tmp);
void DictionaryObject_RESIZE(BaseObject * self_tmp,unsigned int size);

TypeObject DictionaryType;


#endif









