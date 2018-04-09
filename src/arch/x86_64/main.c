
#include <stdio.h>
#include <stdlib.h>

#include <Foxlang.h>






int main(int argc, char *argv[]){
	BaseObject * a = IntegerObject_Fromstring("99");
	BaseObject * b = IntegerObject_Fromstring("99");
	printf("%li\n", IntegerObject_Tolong(a));
	printf("%li\n", IntegerObject_Tolong(b));

	printf("%s\n",IntegerObject_Repr(IntegerObject_Add(a,b)));
	DECREF(a);


	return 0;
}


