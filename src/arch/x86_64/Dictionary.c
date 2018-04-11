#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <math.h>
#include <assert.h>
#include <stdbool.h>

#include <Foxlang.h>


void DictionaryObject_Insert(BaseObject * self_tmp, BaseObject * key, BaseObject * value){
	DictionaryObject * self = (DictionaryObject *)self_tmp;
	HASH hash;
	TypeObject * t = OBJTYPE(key);
	if(t->generate_hash == 0){
		//exception handler 
	}else{
		hash = t->generate_hash(key);

		if(!self->values[hash%OBJSIZE(self)].filled){
			self->values[hash%OBJSIZE(self)] = (DictionaryObjectPair){
				key,
				value,
				hash,
				true,
			};
			printf("succesfully isnserted at %i\n",hash%OBJSIZE(self));
		}else if(false){
			//OBJCMP_VAL(self->values[hash%OBJSIZE(self)].key,key)
		}else{
			printf("not null\n");
		}
	}
}

// void DictionaryObject_RESIZE(BaseObject * self_tmp,unsigned int size){
// 	DictionaryObject * self = (DictionaryObject *)self_tmp;

// }

void DictionaryObject_DESTRUCT(BaseObject * self_tmp){
	DictionaryObject * self = (DictionaryObject *)self_tmp;
	printf("dictionary <%p> deleting itself\n",self_tmp);
	free(self->values);
	free(self);
}


TypeObject DictionaryType = {
	VarBaseObject_HEAD_INIT(&BaseObjectType,0)
	"dictionary",									//typename
	sizeof (DictionaryObject),						//startsize
	0,												//itemsize
	&DictionaryObject_DESTRUCT,						//destructor!
	0,												//numbermethods
	0,												//hash
};

DictionaryObject * DictionaryObject_Init(){
	DictionaryObject * a = malloc(sizeof(DictionaryObject));

	*a = (DictionaryObject){
		VarBaseObject_HEAD_INIT(&DictionaryType,DICTIONARY_DEFAULT_STARTSIZE)
		calloc(DICTIONARY_DEFAULT_STARTSIZE,sizeof(DictionaryObjectPair)),
	};
	return a;
}


