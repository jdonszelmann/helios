
#include <stdio.h>
#include <stdlib.h>

#include <Foxlang.h>






int main(int argc, char *argv[]){
	BaseObject * a = IntegerObject_Fromstring("99");
	BaseObject * b = IntegerObject_Fromstring("99");
	
	printf("%ld\n", IntegerObject_Tolong(a));
	printf("%ld\n", IntegerObject_Tolong(b));

	printf("%s\n",IntegerObject_Repr(IntegerObject_BinaryAdd(a,b)));
	DECREF(a);
	DECREF(b);

	return 0;
}


