
#include <Foxlang.h>


void BaseObject_Dealloc(BaseObject * o){
	printf("deleting %p\n",o);
	free(o);
}