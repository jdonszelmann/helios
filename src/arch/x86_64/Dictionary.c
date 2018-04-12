#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <math.h>
#include <assert.h>
#include <stdbool.h>

#include <Foxlang.h>

char * DictionaryObject_Repr_CHARPNT(BaseObject * self_tmp){
	DictionaryObject * self = (DictionaryObject *)self_tmp;
	for (int i = 0; i < OBJSIZE(self); ++i)
	{
		
	}
	return "";
}


void DictionaryObject_Insert(BaseObject * self_tmp, BaseObject * key, BaseObject * value){
	DictionaryObject * self = (DictionaryObject *)self_tmp;
	HASH hash;
	TypeObject * t = OBJTYPE(key);
	if(t->generate_hash == 0){
		return;
		//exception handler 
	}else{
		hash = t->generate_hash(key);
		for(int i=0;i<OBJSIZE(self);i++){
			if(self->values[i].keyhash == hash){
				if(BOOLEAN_IS_TRUE(BaseObject_Compare(self->values[i].value,value,EQ))){
					self->values[i].value = value;
					printf("object at %i replaced\n",i);
					return;
				}
			}
		}
		if(!self->values[hash%OBJSIZE(self)].filled){
			self->values[hash%OBJSIZE(self)] = (DictionaryObjectPair){
				key,
				value,
				hash,
				true,
			};
			printf("succesfully inserted at %i\n",hash%OBJSIZE(self));
		}else if(BOOLEAN_IS_TRUE(BaseObject_Compare(self->values[hash%OBJSIZE(self)].value,value,EQ))){
			self->values[hash%OBJSIZE(self)].value = value;
		}else{
			int counter = 0;
			while(++counter){
				if(!self->values[(hash+counter)%OBJSIZE(self)].filled){
					self->values[(hash+counter)%OBJSIZE(self)] = (DictionaryObjectPair){
						key,
						value,
						hash,
						true,
					};
					printf("succesfully inserted at %i (added %i to index)\n",(hash+counter)%OBJSIZE(self),counter);
					break;
				}
				printf("%i,%i\n",counter,OBJSIZE(self));
				if(counter > OBJSIZE(self)){
					printf("DICTIONARY FULL");
					//error handler
					return;
				}
			}
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
	0,												//comparemethods
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


