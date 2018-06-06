
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <math.h>
#include <assert.h>
#include <ctype.h>

#include <Foxlang.h>

char * ExceptionObject_Repr_CHARPNT(BaseObject * o_tmp){
	ExceptionObject * o = (ExceptionObject *)o_tmp;
	return o->message;
}

BaseObject * ExceptionObject_Repr(BaseObject * o_tmp){
	return (BaseObject *) StringObject_Fromstring(ExceptionObject_Repr_CHARPNT(o_tmp));
}


// HASH ExceptionObject_Hash(BaseObject * self_tmp){
// 	return 0;
// }


BaseObject * ExceptionObject_FromCHARPNT(char * value){
	ExceptionObject * o = ExceptionObject_Init();
	o->message = value;
	return (BaseObject *)o;
}

BaseObject * ExceptionObject_FromString(BaseObject * o){
	return NULL;
}

char * ExceptionObject_ToCHARPNT(BaseObject * o){
	return "";
}

BaseObject * ExceptionObject_ToString(BaseObject * o){
	return NULL;
}



void ExceptionObject_DESTRUCT(BaseObject * self_tmp){
	ExceptionObject * self = (ExceptionObject *)self_tmp;
	printf("Exception <%p> deleting itself\n",self_tmp);
	free(self);
}


TypeObject ExceptionType = {
	VarBaseObject_HEAD_INIT(&BaseObjectType,0)
	"Exception",									//typename
	sizeof (ExceptionObject),						//startsize
	0,												//itemsize
	&ExceptionObject_DESTRUCT,						//destructor!
	0,												//comparemethods
	0,												//numbermethods
	0,// &ExceptionObject_Hash,						//hash
	&ExceptionObject_Repr,							//repr
};

ExceptionObject * ExceptionObject_Init(){
	ExceptionObject * a = malloc(sizeof(ExceptionObject));
	
	*a = (ExceptionObject) {
		BaseObject_HEAD_INIT(&ExceptionType)
		NULL
	};
	return a;
}
