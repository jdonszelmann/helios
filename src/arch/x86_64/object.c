
#include <Foxlang.h>

COMPARISON_OPERATOR REVERSE_COMPARISON_OPERATOR[] = {NEQ,EQ,GT,LT,GTE,LTE};

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

BaseObject * BaseObject_Compare(BaseObject * a, BaseObject * b,COMPARISON_OPERATOR op){
	if(a == NULL || b == NULL){
		//exception handler
		return NULL
	}
	// if(op == EQ)


}


int BaseObject_Compare_BOOL(BaseObject * a, BaseObject * b,COMPARISON_OPERATOR op){
	int compared_result = -1;
	if(a == b){
		if(op == EQ){
			return 1;
		}else if(op == NEQ){
			return 0;
		}
	}else{
		BaseObject * res = BaseObject_Compare(a,b,op);
		if (res == NULL){
			compared_result = -1;
		}else if(IS_BOOLEAN(res)){
			compared_result = BOOLEAN_IS_TRUE(res);
		}else{
			compared_result = BASEOBJECT_IS_TRUE(res);
		}						
		DECREF(res);
	}
	return compared_result;
}