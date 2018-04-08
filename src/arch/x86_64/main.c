
#include <stdio.h>
#include <stdlib.h>

#include <Foxlang.h>






int main(int argc, char *argv[]){
	BaseObject * a = IntegerObject_Fromstring("99");
	printf("%li\n", IntegerObject_Tolong(a));

	printf("%s\n",IntegerObject_Repr(a));
	DECREF(a);


	return 0;
}


