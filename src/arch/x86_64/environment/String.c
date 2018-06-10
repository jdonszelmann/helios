
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <math.h>
#include <assert.h>
#include <stdarg.h>
#include <stdbool.h>

#include <Foxlang.h>


void StringObject_Setvalue(StringObject * self, char * value){
	if(self->value!=NULL){
		free(self->value);
	}
	int length = strlen(value);
	char * p = malloc((length+1)*sizeof(char));
	if(p==NULL){
		printf("NULL");
	}
	self->value = p;
	strcpy(self->value,value);
}

BaseObject * StringObject_Fromstring(char * value){
	StringObject * a = StringObject_Init();
	StringObject_Setvalue(a,value);
	return (BaseObject *)a;
}

BaseObject * StringObject_Fromformat(char * format,...){
    va_list args,copy;
    va_start(args, format);

	va_copy(copy, args);
    int bufsz = vsnprintf(NULL, 0, format,copy);
    va_end(copy);

    char * res = malloc(bufsz+1);
    vsnprintf(res,bufsz+1,format,args);
    va_end(args);

    BaseObject * str = StringObject_Fromstring(res);
    free(res);
    return str;
}

char * StringObject_Repr_CHARPNT(BaseObject * self_tmp){
	StringObject * self = (StringObject *)self_tmp;
	if(self->value == NULL){
		char * ret = malloc(3*sizeof(char));
		*ret = '"';
		*(ret+1) = '"';
		*(ret+2) = '\0';
		return ret;
	}
	int copysize = OBJTYPE(self)->item_size + 10;
	char * copy = malloc(copysize * sizeof(char));
	*copy = '\'';
	int copycounter = 1;
	int originalcounter = 0;	

	while(1){
		if(self->value[originalcounter] == '\0'){
			copy[copycounter] = '\'';
			copycounter++;
			copy[copycounter] = '\0';
			copycounter++;
			break;
		}
		if(self->value[originalcounter] == '\n'){
			copy[copycounter] = '\\';
			copycounter++;
			copy[copycounter] = 'n';
			copycounter++;
		}else{
			copy[copycounter] = self->value[originalcounter];
			copycounter++;
		}
		if(copycounter > copysize-2){
			copysize += 20;
			copy = realloc(copy,copysize);
		}
		originalcounter++;
	}
	return copy;
}

BaseObject * StringObject_Repr(BaseObject * self_tmp){
	StringObject * res = StringObject_Init();
	char * str = StringObject_Repr_CHARPNT(self_tmp);
	StringObject_Setvalue(res,str);
	free(str);
	return (BaseObject *)res;
}

char * StringObject_Str_CHARPNT(BaseObject * self_tmp){
	StringObject * self = (StringObject *)self_tmp;
	char * res = malloc(sizeof(char)*OBJTYPE(self)->item_size+1);
	strcpy(res,self->value);
	return res;
}

BaseObject * StringObject_Str(BaseObject * self_tmp){
	StringObject * res = StringObject_Init();
	char * str = StringObject_Str_CHARPNT(self_tmp);
	StringObject_Setvalue(res,str);
	free(str);
	return (BaseObject *)res;
}

BaseObject * StringObject_BinaryEQ(BaseObject * self_tmp,BaseObject * other_tmp){
	StringObject * self = (StringObject *)self_tmp; 
	if(OBJCHECKTYPE(other_tmp,"string")){
		StringObject * other = (StringObject *)other_tmp; 
		if(strcmp(self->value,other->value) == 0){
			return True;
		}else{
			return False;
		}
	}else{
		return False;
	}
}



HASH StringObject_Hash(BaseObject * self_tmp){
	if(!OBJCHECKTYPE(self_tmp,"string")){
		RAISE(ExceptionObject_FromCHARPNT("TypeError. wrong function."));
	}
	StringObject * self = (StringObject *)self_tmp;
	if(self->statichash != -1){
		return self->statichash;
	}
	
	HASH hash = *self->value << 7;
	for(int i = 0; i < OBJTYPE(self)->item_size; ++i){
		hash = (hash * 1000003) ^ self->value[i];
	}
	self->statichash = hash;
	return hash;
}

BaseObject * StringObject_UnaryBool(BaseObject * self_tmp){
	if(!OBJCHECKTYPE(self_tmp,"string")){
		RAISE(ExceptionObject_FromCHARPNT("TypeError. wrong function."));
	}
	StringObject * self = (StringObject *)self_tmp;
	if(strlen(self->value) == 0){
		return False;
	}
	return True;
}


void StringObject_DESTRUCT(BaseObject * self_tmp){
	if(self_tmp == NULL){
		return;
	}
	StringObject * self = (StringObject *)self_tmp;
	// printf("string <%p> deleting itself\n",self_tmp);
	if(self->value != NULL){
		free(self->value);
	}
	free(self);
}


CompareMethods StringObject_Compare = {
	StringObject_BinaryEQ,	// EQ
	0,	// NEQ
	0,	// LT
	0,	// GT
	0,	// LTE
	0,	// GTE
	StringObject_UnaryBool,	// ASBOOL
};


TypeObject StringType = {
	VarBaseObject_HEAD_INIT(&BaseObjectType,0)
	"string",										//typename
	sizeof (StringObject),							//startsize
	0,												//itemsize
	&StringObject_DESTRUCT,							//destructor!
	&StringObject_Compare,							//comparemethods
	0,												//numbermethods
	0,												//itermethods
	&StringObject_Hash,								//hash
	&StringObject_Repr,								//repr
};

StringObject * StringObject_Init(){
	StringObject * a = malloc(sizeof(StringObject));
	
	*a = (StringObject) {
		BaseObject_HEAD_INIT(&StringType)
		NULL,
		-1
	};
	Fox_Initialize_Object((BaseObject *)a);
	return a;
}