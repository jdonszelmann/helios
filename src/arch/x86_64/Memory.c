
#include <stdio.h>
#include <stdlib.h>
#include <Foxlang.h>

void BaseObject_Dealloc(BaseObject * o){
	printf("deleting %p\n",o);
	TypeObject * t = OBJTYPE(o);
	if(t == 0){
		free(o);
	}else{
		t->destruct_object(o);
	}
}