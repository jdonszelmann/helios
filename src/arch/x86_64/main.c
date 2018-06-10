
#include <stdio.h>
#include <stdlib.h>

#include <Foxlang.h>

#define ERROR(o) printf("error %s at line %d (%s)",(char *)o,__LINE__,__FILE__);

int main(int argc, char *argv[]){

	tokenize("a = \"hello world\"");


	// BaseObject * list = ListObject_FromVARG(2,IntegerObject_Fromstring("390"),IntegerObject_Fromstring("320"));
	// BaseObject_PRINTFUNC(list);
	// BaseObject * iterator = BaseObject_Iter(list);


	
	// BaseObject * next = BaseObject_IterNext(iterator);
	// BaseObject_PRINTFUNC(next);
	// DECREF(next);

	// BaseObject * next1 = BaseObject_IterNext(iterator);
	// BaseObject_PRINTFUNC(next1);
	
	// DECREF(next1);

	// DECREF(iterator);
	// DECREF(list);

	// frame * f = frame_init();


	// instruction * start = add_instruction_after_prev(NOP,0);
	// add_instruction_after_prev(LDC,0);
	// add_instruction_after_prev(PRNT,0);
	// add_instruction_after_prev(LDC,1);
	// add_instruction_after_prev(PRNT,0);
	// add_instruction_after_prev(ADD,0);
	// add_instruction_after_prev(PRNT,0);

	// add_instruction_after_prev(PRNT,0);

	// add_instruction_after_prev(STP,0);
	

	// f->constants = (BaseObject *[]){
	// 	STATIC(IntegerObject_Fromstring("390")),
	// 	STATIC(IntegerObject_Fromstring("320")),
	// };

	// f->start = start;
	// execute_frame(f);

	// frame_DESTRUCT_Recursive(f);

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

