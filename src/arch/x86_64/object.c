
#include <Foxlang.h>

TypeObject BaseObjectType = {
	VarBaseObject_HEAD_INIT(&BaseObjectType,0)
	"BaseObject",
	sizeof (BaseObject),
	0,
	0,
	0
};

TypeObject VarBaseObjectType = {
	VarBaseObject_HEAD_INIT(&VarBaseObjectType,0)
	"BaseObject",
	sizeof (VarBaseObject),
	0,
	0,
	0
};

int OBJCHECKTYPE(BaseObject * o, char * type){
	return strcmp(o->object_type->typename,type) == 0;
}

