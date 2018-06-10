#ifndef EXCEPTION_H
#define EXCEPTION_H


#define C_SYNTAXERROR(o) ExceptionObject_Raise(ExceptionObject_SyntaxError(StringObject_Fromformat("error %s at line %d (%s)",(char *)o,__LINE__,__FILE__)));
#define C_KEYERROR(o) ExceptionObject_Raise(ExceptionObject_KeyError(StringObject_Fromformat("error %s at line %d (%s)",(char *)o,__LINE__,__FILE__)));
#define C_VALUEERROR(o) ExceptionObject_Raise(ExceptionObject_ValueError(StringObject_Fromformat("error %s at line %d (%s)",(char *)o,__LINE__,__FILE__)));
#define C_KEYBOARDINTERRUPT(o) ExceptionObject_Raise(ExceptionObject_KeyboardInterrupt(StringObject_Fromformat("error %s at line %d (%s)",(char *)o,__LINE__,__FILE__)));
#define C_SYSTEMEXIT(o) ExceptionObject_Raise(ExceptionObject_SystemExit(StringObject_Fromformat("error %s at line %d (%s)",(char *)o,__LINE__,__FILE__)));


typedef struct{
	Object_immutable_HEAD;
	char * message;
}BaseException;

typedef struct{
	Object_immutable_HEAD;
	char * message;
}ExceptionObject_SystemExit;

typedef struct{
	Object_immutable_HEAD;
	char * message;
}ExceptionObject_SyntaxError;

typedef struct{
	Object_immutable_HEAD;
	char * message;
}ExceptionObject_KeyboardInterrupt;

typedef struct{
	Object_immutable_HEAD;
	char * message;
}ExceptionObject_KeyError;


#endif