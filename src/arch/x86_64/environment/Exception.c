
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <math.h>
#include <assert.h>
#include <ctype.h>

#include <Foxlang.h>

// static BaseObject * CatchStack[1024];

char * ExceptionObject_Repr_CHARPNT(BaseObject * o_tmp){
	ExceptionObject * o = (ExceptionObject *)o_tmp;
	return o->message;
}

BaseObject * ExceptionObject_Repr(BaseObject * o_tmp){
	char * res = ExceptionObject_Repr_CHARPNT(o_tmp);
	BaseObject * str = StringObject_Fromstring(res);
	free(res);
	return (BaseObject *) str;
}

// void TryPush(){

// }



// void TryPop(){

// }

// HASH ExceptionObject_Hash(BaseObject * self_tmp){
// 	return 0;
// }


BaseObject * ExceptionObject_FromCHARPNT(char * value){
	return ExceptionObject_FromCHARPNT_FMT(value);
}

BaseObject * ExceptionObject_FromCHARPNT_FMT(char * value,...){
	va_list args,copy;
	va_start(args, value);

	va_copy(copy, args);
	int bufsz = vsnprintf(NULL, 0, value,copy);
	va_end(copy);

	char * res = malloc(bufsz+1);
	vsnprintf(res,bufsz+1,value,args);
	va_end(args);


	ExceptionObject * o = ExceptionObject_Init();
	o->message = res;
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
	free(self->message);
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
	0,												//itermethods
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
