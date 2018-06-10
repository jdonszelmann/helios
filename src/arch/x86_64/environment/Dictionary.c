#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <math.h>
#include <assert.h>
#include <stdbool.h>
#include <unistd.h>

#include <Foxlang.h>


char * DictionaryObject_Repr_CHARPNT(BaseObject * self_tmp){
	DictionaryObject * self = (DictionaryObject *)self_tmp;
	int totalsize = 10;
	char * total = malloc(totalsize);
	char * currentpos = total;
	*currentpos = '{';
	currentpos++;
	for (int i = 0; i < OBJSIZE(self); ++i)
	{
		if(self->values[i].filled){
			char * key = BaseObject_Repr_CHARPNT(self->values[i].key);
			char * value = BaseObject_Repr_CHARPNT(self->values[i].value);

			int bufsz = snprintf(NULL, 0, "%s:%s", key, value);

			char res[bufsz+1];
			sprintf(res,"%s: %s, ", key, value);

			int length = strlen(res);
			if(currentpos-total+length > totalsize){
				totalsize *= 2;
				int diff = currentpos-total;
				printf("~%i\n",totalsize);
				total = realloc(total,totalsize);
				currentpos = total + diff;
			}
			strcpy(currentpos,res);
			currentpos+=length;
		}
	}
	*(currentpos-2) = '}';
	*(currentpos-1) = '\0';

	char * res = malloc(strlen(total)+1);
	strcpy(res,total);
	free(total);

	return res;
}

void DictionaryObject_Insert_Withhash(BaseObject * self_tmp, BaseObject * key, BaseObject * value, HASH hash){
	DictionaryObject * self = (DictionaryObject *)self_tmp;

	//if item already in: replace [O(1)]
	if(self->values[hash%OBJSIZE(self)].filled){
		if(BOOLEAN_IS_TRUE(BaseObject_Compare(self->values[hash%OBJSIZE(self)].key,key,EQ))){
			self->values[hash%OBJSIZE(self)].value = value;
			printf("object at %i replaced\n",hash%OBJSIZE(self));
			return;
		}else{
			//colision
			int counter = 0, j = hash%OBJSIZE(self);
			while(true){
				if(!self->values[(hash+j)%OBJSIZE(self)].filled){
					self->values[(hash+j)%OBJSIZE(self)] = (DictionaryObjectPair){
						key,
						value,
						hash,
						true,
					};
					printf("succesfully inserted at %i (added %i to index, took %i cycles)\n",(hash+j)%OBJSIZE(self),j, counter+1);
					ITEMSIZE(self)++;
					return;
				}
				if(counter > OBJSIZE(self)){
					printf("DICTIONARY FULL\n");
					//error handler
					return;
				}
				j = ((5*j) + 1) % OBJSIZE(self);
				counter++;
			}
		}
	}else{
		self->values[hash%OBJSIZE(self)] = (DictionaryObjectPair){
			key,
			value,
			hash,
			true,
		};
		ITEMSIZE(self)++;
		printf("succesfully inserted at %i\n",hash%OBJSIZE(self));
		return;
	}
}

void DictionaryObject_RESIZE(DictionaryObject * self,unsigned int size){
	if(size < ITEMSIZE(self)){
		//exception handler
		return;
	}
	int oldsize = OBJSIZE(self);
	DictionaryObjectPair * oldvalues = self->values;
	self->values = calloc(size,sizeof(DictionaryObjectPair));
	OBJSIZE(self) = size;
	ITEMSIZE(self) = 0;
	for (int i = 0; i < oldsize; ++i)
	{
		if(oldvalues[i].filled){
			DictionaryObject_Insert_Withhash((BaseObject *)self, oldvalues[i].key, oldvalues[i].value, oldvalues[i].keyhash);
		}
	}
	free(oldvalues);
}


BaseObject * DictionaryObject_Retrieve(BaseObject * self_tmp, BaseObject * key){
	DictionaryObject * self = (DictionaryObject *)self_tmp;
	HASH hash = BaseObject_Hash_HASH(key);
	if(hash == -1){
		return False; //must later become None
	}else{
		if(BOOLEAN_IS_TRUE(BaseObject_Compare(self->values[hash%OBJSIZE(self)].key,key,EQ))){
			return self->values[hash%OBJSIZE(self)].value;
		}else{
			printf("hash colision");
			return NULL;
		}
	}	
}


void DictionaryObject_Insert(BaseObject * self_tmp, BaseObject * key, BaseObject * value){
	HASH hash = BaseObject_Hash_HASH(key);
	if(hash == -1){
		printf("type not hashable");
		return;
		//exception handler 
	}else{
		if(ITEMSIZE(self_tmp) + 1 > (((float)OBJSIZE(self_tmp))*DICTIONARY_MAXFILLED)){
			printf("resizing\n");
			DictionaryObject_RESIZE((DictionaryObject *)self_tmp,OBJSIZE(self_tmp)*2);
		}

		DictionaryObject_Insert_Withhash(self_tmp, key, value, hash);
	}
}

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
	0,												//itermethods
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


