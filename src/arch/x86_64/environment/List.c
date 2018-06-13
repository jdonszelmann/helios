
#include <stdio.h>
#include <stdlib.h>
#include <List.h>
#include <limits.h>
#include <errno.h>
#include <math.h>
#include <assert.h>
#include <stdarg.h>
#include <stdbool.h>

#include <Foxlang.h>



BaseObject * ListObject_FromVARG(int size,...){
	ListObject * a = ListObject_Init();
	va_list args;
	va_start(args, size);
	BaseObject * val;
	for (int i=0;i<size;i++){
		val=va_arg(args,BaseObject *);
		ListObject_Append((BaseObject *)a,val);
	}
	va_end(args);

	return (BaseObject *)a;
}

void ListObject_Append(BaseObject * self_tmp, BaseObject * i){
	ListObject * self = (ListObject *)self_tmp;
	INCREF(i);
	if(self->filled>self->size){
		self->size*=2;
		self->value=realloc(self->value,self->size*sizeof(BaseObject *));
	}
	self->value[self->filled]=i;
	self->filled++;
}

void ListObject_Remove(BaseObject * self_tmp, BaseObject * o){
	ListObject * self = (ListObject *)self_tmp;
	for (int i = 0; i < self->filled; ++i){
		if(BOOLEAN_IS_TRUE(BaseObject_Compare_EQ(self->value[i],o))){
			ListObject_Removei_int(self_tmp,i);
			return;
		}
	}
}

void ListObject_Removei(BaseObject * self_tmp, BaseObject * o){
	ListObject_Removei_int(self_tmp,IntegerObject_Tolong(BaseObject_AsInteger(o)));
}

void ListObject_Removei_int(BaseObject * self_tmp, int index){
	ListObject * self = (ListObject *)self_tmp;
	BaseObject * old = self->value[index];
	DECREF(old);
	int i;
	self->filled--;
	for (i = index; i < self->filled; ++i){
		self->value[i]=self->value[i+1];
	}
}


char * ListObject_Repr_CHARPNT(BaseObject * self_tmp){
	ListObject * self = (ListObject *)self_tmp;
	if(self->value == NULL){
		char * ret = malloc(3*sizeof(char));
		*ret = '[';
		*(ret+1) = ']';
		*(ret+2) = '\0';
		return ret;
	}
	char * finalstring = malloc(100);
	*finalstring = '[';
	*(finalstring+1) = '\0';
	int size = 100;
	int filled = 2;

	char * res;
	for (int i = 0; i < self->filled; ++i){
		res = BaseObject_Repr_CHARPNT(self->value[i]);
		if((strlen(res)+filled+3)>size){
			size*=2;
			finalstring = realloc(finalstring,size);
		}
		filled += strlen(res)+2;
		strcat(finalstring,res);
		if(i != self->filled-1){
			strcat(finalstring,", ");
		}
		free(res);
	}
	if((2+filled)>size){
		size*=2;
		finalstring = realloc(finalstring,size);
	}
	strcat(finalstring,"]");
	return finalstring;
}

BaseObject * ListObject_Repr(BaseObject * self_tmp){
	char * res = ListObject_Repr_CHARPNT(self_tmp);
	BaseObject * str = StringObject_Fromstring(res);
	free(res);
	return (BaseObject *)str;
}

char * ListObject_Str_CHARPNT(BaseObject * self_tmp){
	return ListObject_Repr_CHARPNT(self_tmp);
}

BaseObject * ListObject_Str(BaseObject * self_tmp){
	char * res = ListObject_Str_CHARPNT(self_tmp);
	BaseObject * str = StringObject_Fromstring(res);
	free(res);
	return (BaseObject *)str;
}

BaseObject * ListObject_BinaryEQ(BaseObject * self_tmp,BaseObject * other_tmp){
	if(!OBJCHECKTYPE(self_tmp,"List")){
		RAISE(ExceptionObject_FromCHARPNT("TypeError. wrong function."));
	}
	ListObject * self = (ListObject *)self_tmp; 
	if(OBJCHECKTYPE(other_tmp,"List")){
		ListObject * other = (ListObject *)other_tmp; 
		if(self->filled != other->filled){
			return False;
		}
		for (int i = 0; i < self->filled; ++i){
			if(BOOLEAN_IS_FALSE(BaseObject_Compare_EQ(self->value[i],other->value[i]))){
				return False;
			}
		}
		return True;
	}else{
		return False;
	}
}

HASH ListObject_Hash(BaseObject * self_tmp){
	if(!OBJCHECKTYPE(self_tmp,"List")){
		RAISE(ExceptionObject_FromCHARPNT("TypeError. wrong function."));
	}
	ListObject * self = (ListObject *)self_tmp;
	
	HASH hash = BaseObject_Hash_HASH(*self->value) << 7;
	for(int i = 0; i < self->filled; ++i){
		hash = (hash * 1000003) ^ BaseObject_Hash_HASH(self->value[i]);
	}
	return hash;
}

BaseObject * ListObject_UnaryBool(BaseObject * self_tmp){
	if(!OBJCHECKTYPE(self_tmp,"List")){
		RAISE(ExceptionObject_FromCHARPNT("TypeError. wrong function."));
	}
	ListObject * self = (ListObject *)self_tmp;
	if(self->filled == 0){
		return False;
	}
	return True;
}


void ListObject_DESTRUCT(BaseObject * self_tmp){
	if(self_tmp == NULL){
		return;
	}
	ListObject * self = (ListObject *)self_tmp;
	// printf("List <%p> deleting itself\n",self_tmp);
	for (int i = 0; i < self->filled; ++i){
		DECREF(self->value[i]);
		
	}
	if(self->value != NULL){
		free(self->value);
	}
	free(self);
}

BaseObject * ListObject_len(BaseObject * self_tmp){
	ListObject * self = (ListObject *)self_tmp;
	return IntegerObject_Fromlong(self->filled);
}


BaseObject * ListObject_iter(BaseObject * self_tmp){
	return IteratorObject_Create(self_tmp);
}


BaseObject * ListObject_iternext(BaseObject * iterator){
	IteratorObject * it = (IteratorObject *) iterator;
	return ListObject_GetItemAtint(it->iterating,it->index); 
}

BaseObject * ListObject_iterprev(BaseObject * self_tmp){
	return NULL;
}

BaseObject * ListObject_GetItemAtint(BaseObject * self_tmp,int index){
	ListObject * self = (ListObject *)self_tmp;
	return self->value[index];
}

BaseObject * ListObject_GetItemAt(BaseObject * self_tmp,BaseObject * index){
	// ListObject * self = (ListObject *)self_tmp;
	return NULL;
}



CompareMethods ListObject_Compare = {
	ListObject_BinaryEQ,	// EQ
	0,	// NEQ
	0,	// LT
	0,	// GT
	0,	// LTE
	0,	// GTE
	ListObject_UnaryBool,	// ASBOOL
};

IterMethods ListObject_Iter = {
	&ListObject_len,				//length
	
	0,
	0,

	0,
	0,
	0,

	0,
	0,

	0,

	&ListObject_iter,				//iter
	&ListObject_iternext,			//iternext
	&ListObject_iterprev,			//iterprev
};

TypeObject ListType = {
	VarBaseObject_HEAD_INIT(&BaseObjectType,0)
	"List",										//typename
	sizeof (ListObject),						//startsize
	0,											//itemsize
	&ListObject_DESTRUCT,						//destructor!
	&ListObject_Compare,						//comparemethods
	0,											//numbermethods
	&ListObject_Iter,							//itermethods
	&ListObject_Hash,							//hash
	&ListObject_Repr,							//repr
};

ListObject * ListObject_Init(){
	ListObject * a = malloc(sizeof(ListObject));
	
	*a = (ListObject) {
		VarBaseObject_HEAD_INIT(&ListType,0)
		malloc(100*sizeof(BaseObject *)),
		100,
		0
	};
	Fox_Initialize_Object((BaseObject *)a);
	return a;
}