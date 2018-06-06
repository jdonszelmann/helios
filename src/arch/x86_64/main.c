
#include <stdio.h>
#include <stdlib.h>

#include <Foxlang.h>

#define ERROR(o) printf("error %s at line %d (%s)",(char *)o,__LINE__,__FILE__);

int main(int argc, char *argv[]){

	instruction * start = add_instruction_after_prev(NOP);
	add_instruction_after_prev(NOP);
	add_instruction_after_prev(STP);
	
	execute(start,NULL);

	instruction_DESTRUCT_Recursive(start);

	// Fox_Clean_Init();

	// BaseObject * a = IntegerObject_Fromstring("390");
	// BaseObject * b = IntegerObject_Fromstring("320");

	// // printf(">%i\n",BOOLEAN_IS_TRUE(BaseObject_Compare(a,b,EQ)));
	// // printf("%ld\n", IntegerObject_Tolong(a));
	// // printf("%ld\n", IntegerObject_Tolong(b));
	// // printf(">>%s\n",DictionaryObject_Repr_CHARPNT(dict));
	// BaseObject_PRINTFUNC(a);
	// BaseObject_PRINTFUNC(b);

	// BaseObject * c = IntegerObject_BinaryAdd(a,b);
	// BaseObject_PRINTFUNC(c);
	// // DECREF(a);
	// // DECREF(b);
	// // DECREF(c);

	// Fox_Clean();

	return 0;

}

