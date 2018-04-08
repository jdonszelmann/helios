
#include <Foxlang.h>

TypeObject BaseObjectType = {
	VarBaseObject_HEAD_INIT(&BaseObjectType,0)
	"BaseObject",
	sizeof (BaseObject),
	0,
	0
};

TypeObject VarBaseObjectType = {
	VarBaseObject_HEAD_INIT(&VarBaseObjectType,0)
	"BaseObject",
	sizeof (VarBaseObject),
	0,
	0
};

