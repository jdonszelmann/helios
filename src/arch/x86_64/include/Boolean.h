#ifndef BOOLEAN_H
#define BOOLEAN_H


typedef struct{
	Object_mutable_HEAD;
}BooleanObject;


BaseObject * BooleanObject_FromBool(int value);
int BooleanObject_ToBool(BaseObject * o);

TypeObject BooleanType;


BaseObject * True;
BaseObject * False;

#define BOOLEAN_IS_TRUE(o) ((BaseObject *)o == True)
#define BOOLEAN_NOT_TRUE(o) !BOOLEAN_IS_TRUE(o)
#define BOOLEAN_IS_FALSE(o) ((BaseObject *)o == False)
#define BOOLEAN_not_FALSE(o) !BOOLEAN_IS_FALSE(o)
#define IS_BOOLEAN(o) (o == True || o == False)

inline int BASEOBJECT_IS_TRUE(BaseObject * o){
	if(BOOLEAN_IS_TRUE(o)){
		return 1;
	}else if(BOOLEAN_IS_FALSE(o)){
		return 0;
	// }else if (IS_NONE(o)){
	// 	return 0;
	}else if(OBJTYPE(o)->number != NULL && OBJTYPE(o)->number->ASBOOL != NULL){
		int counter = 0;
		BaseObject * current = o;
		while(1){
			BaseObject * a = OBJTYPE(current)->number->ASBOOL(current);
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