
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

#include <Foxlang.h>


TypeObject IntegerType = {
	VarBaseObject_HEAD_INIT(&BaseObjectType,0)
	"int",
	sizeof (IntegerObject),
	0,
	0
};

IntegerObject * IntegerObject_Init(int startsize){
	IntegerObject * a = malloc(sizeof(IntegerObject));
	*a = (IntegerObject) {
		BaseObject_HEAD_INIT(&IntegerType)
		malloc(sizeof(unsigned char)*startsize),
		startsize,
		-1
	};
	return a;
}

void IntegerObject_Resize(BaseObject * i_tmp, int length){
	IntegerObject * i = (IntegerObject *)i_tmp;
	i->length = length;
	i->value = realloc(i->value, length*sizeof(unsigned char));
}


BaseObject * IntegerObject_Fromstring(char * value){
	int size = strlen(value);
	printf("size %i\n", size);
	IntegerObject * a = IntegerObject_Init(size);

	for (int i = 0; i < size; ++i)
	{
		char substr[2];
		strncpy(substr, value+i, 1);
		unsigned char ret = (unsigned char)strtol(substr, NULL, 10);
		a->value[i] = ret;
	}
	return (BaseObject *)a;
}

char * IntegerObject_Repr(BaseObject * o_tmp){

	IntegerObject * o = (IntegerObject *)o_tmp;
	char * largebuffer = malloc((o->length)*sizeof(char));
	if(o->sign == -1){
		strcpy(largebuffer,"-");
	}else{
		strcpy(largebuffer,"");
	}
	for(int i = 0; i < o->length; i++){
		char buffer[2];
		sprintf(buffer,"%i", o->value[i]);
		strcat(largebuffer,buffer);
	}
	return largebuffer;
}

BaseObject * IntegerObject_Add(BaseObject * self_tmp,BaseObject * other_tmp){
	if(self_tmp->object_type->typename != "int"){
		//exception handler
	}
	if(other_tmp->object_type->typename != "int"){
		//exception handler
	}
	// IntegerObject * o = (IntegerObject *)o_tmp;
	return NULL;
}


BaseObject * IntegerObject_Fromlong(unsigned long value){
	char buffer[10];
	sprintf(buffer,"%li",value);
	return IntegerObject_Fromstring(buffer);
}

long IntegerObject_Tolong(BaseObject * o_tmp){

	char * repr = IntegerObject_Repr(o_tmp);
	unsigned long res = (unsigned long)strtoul(repr, NULL, 10);
	if(errno == ERANGE){
		return 0;
	}
	return res;
}