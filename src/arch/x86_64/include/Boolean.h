#ifndef BOOLEAN_H
#define BOOLEAN_H


typedef struct{
	Object_mutable_HEAD;
}BooleanObject;


BaseObject * BooleanObject_FromBool(int value);
int BooleanObject_ToBool(BaseObject * o);

BaseObject * BooleanObject_Repr(BaseObject * o_tmp);
char * BooleanObject_CHARPNT(BaseObject * o_tmp);

TypeObject BooleanType;


BaseObject * True;
BaseObject * False;

#define BOOLEAN_IS_TRUE(o) ((BaseObject *)o == True)
#define BOOLEAN_NOT_TRUE(o) !BOOLEAN_IS_TRUE(o)
#define BOOLEAN_IS_FALSE(o) ((BaseObject *)o == False)
#define BOOLEAN_NOT_FALSE(o) !BOOLEAN_IS_FALSE(o)
#define BOOLEAN_NOT(o) (o == True)?False:True
#define IS_BOOLEAN(o) (o == True || o == False)

inline int BASEOBJECT_IS_TRUE(BaseObject * o){
	if(BOOLEAN_IS_TRUE(o)){
		return 1;
	}else if(BOOLEAN_IS_FALSE(o)){
		return 0;
	// }else if (IS_NONE(o)){
	// 	return 0;
	}else if(OBJTYPE(o)->compare != NULL && OBJTYPE(o)->compare->ASBOOL != NULL){
		int counter = 0;
		BaseObject * current = o;
		while(1){
			BaseObject * a = OBJTYPE(current)->compare->ASBOOL(current);
			if(IS_BOOLEAN(a)){
				return BOOLEAN_IS_TRUE(a);
			}else if(counter > 1000){
				//exception handler
			}else{
				current = a;
			}
			counter++;
		}
	}else{
		return 1;
	}
}

#define BASEOBJECT_IS_FALSE(o) !BASEOBJECT_IS_TRUE(o)



#endif