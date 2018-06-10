
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <math.h>
#include <assert.h>
#include <ctype.h>

#include <Foxlang.h>

static char *trim(char *str)
{
	size_t len = 0;
	char *frontp = str;
	char *endp = NULL;

	if( str == NULL ) { return NULL; }
	if( str[0] == '\0' ) { return str; }

	len = strlen(str);
	endp = str + len;

	/* Move the front and back pointers to address the first non-whitespace
	 * characters from each end.
	 */
	while( isspace((unsigned char) *frontp) ) { ++frontp; }
	if( endp != frontp )
	{
		while( isspace((unsigned char) *(--endp)) && endp != frontp ) {}
	}

	if( str + len - 1 != endp )
			*(endp + 1) = '\0';
	else if( frontp != str &&  endp == frontp )
			*str = '\0';

	/* Shift the string so that it starts at str so that if it's dynamically
	 * allocated, we can still free it on the returned pointer.  Note the reuse
	 * of endp to mean the front of the string buffer now.
	 */
	endp = str;
	if( frontp != str )
	{
		while( *frontp ) { *endp++ = *frontp++; }
		*endp = '\0';
	}


	return str;
}

BaseObject * LongObject_Fromstring(char * value){
	LongObject * o = LongObject_Init();

	trim(value);
	char * cpy = value;

	if(cpy[0] == '-'){
		int length = strlen(cpy)-1;
		o->value = malloc(length);
		o->sign = -1;
		o->size=0;
		cpy++;
	}else{
		int length = strlen(cpy);
		o->size=0;
		o->value = malloc(length);
	}

	int i = 0;
	while(*cpy!='\0'){
		o->value[i]=(*cpy-'0');
		o->size++;

		cpy++;	
		i++;
	}
	return (BaseObject *)o;
}

char * LongObject_Repr_CHARPNT(BaseObject * o_tmp){
	LongObject * o = (LongObject *)o_tmp;
	char * dest = NULL;
	char * cpy = NULL;


	if (o->sign == -1){
		dest = calloc(o->size+2,sizeof(char));
		dest[0]='-';
		cpy=dest;
		cpy++;
	}else{
		dest = calloc(o->size+1,sizeof(char));
		cpy=dest;
	}

	for (int i=0; i<=o->size; i++){
		sprintf(cpy,"%c",'0'+o->value[i]);
		cpy++;
	}
	cpy--;
	*cpy='\0';	
	return dest; 
}

BaseObject * LongObject_Repr(BaseObject * o_tmp){
	char * res = LongObject_Repr_CHARPNT(o_tmp);
	BaseObject * str = (BaseObject *) StringObject_Fromstring(res);
	free(res);
	return str;
}

BaseObject * LongObject_BinaryAdd(BaseObject * self_tmp,BaseObject * other_tmp){

	if(OBJCHECKTYPE(other_tmp,"Long")){
		LongObject * self = (LongObject *)self_tmp;
		LongObject * other = (LongObject *)other_tmp;
		
		LongObject * new = LongObject_Init();		

		int end;
		if(self->size>other->size){
			end=self->size;
		}else{
			end=other->size;
		}


		int * temp = malloc(end*sizeof(int));

		unsigned char carry=0;
		for (int i = 0;i<end;i++){
			int a;
			int b;
			// printf("%i %i\n",self->size,other->size);
			if(i>=self->size){
				a=0;
			}else{
				a=self->value[(self->size-1)-i];
			}
			if(i>=other->size){
				b=0;
			}else{
				b=other->value[(other->size-1)-i];
			}
			int res = a+b+carry;
			if(res>9){
				carry=1;
				res-=10;
			}else{
				carry=0;
			}
			// printf("%i %i,%i\n",res,a,b);
			temp[i]=res;
		}
		if(carry){
			new->size = end+1;
			new->value = malloc(new->size);
			new->value[0]=1;
			for (int i = 0; i < end; ++i){
				new->value[i+1]=temp[(end-1)-i];
			}
		}else{
			new->size = end;
			new->value = malloc(new->size);
			for (int i = 0; i < end; ++i){
				new->value[i]=temp[(end-1)-i];
			}			
		}
		free(temp);

		return (BaseObject *)new;
	}else if(OBJCHECKTYPE(other_tmp,"Float")){//float
		RAISE(ExceptionObject_FromCHARPNT("NotImplementedError. long-float addition not supported (yet)"));
	}else{
		RAISE(ExceptionObject_FromCHARPNT("TypeError. invalid type for addition."));
	}
	return NULL;

	
}


BaseObject * LongObject_BinaryEQ(BaseObject * self_tmp,BaseObject * other_tmp){
	return NULL;
	// if(!OBJCHECKTYPE(self_tmp,"Long")){
	// 	//exception handler
	// }
	// LongObject * self = (LongObject *)self_tmp; 
	// if(OBJCHECKTYPE(other_tmp,"Long")){
	// 	LongObject * other = (LongObject *)other_tmp; 
	// 	if(self->value == other->value){
	// 		return True;
	// 	}else{
	// 		return False;
	// 	}
	// }else if(OBJCHECKTYPE(other_tmp,"float")){//float
		
	// }else{
	// 	//exception handler
	// }
	// return NULL;
}



HASH LongObject_Hash(BaseObject * self_tmp){
	return 0;
}

BaseObject * LongObject_UnaryNegate(BaseObject * self_tmp){
	if(!OBJCHECKTYPE(self_tmp,"Long")){
		RAISE(ExceptionObject_FromCHARPNT("TypeError. wrong function."));
	}
	LongObject * self = (LongObject *)self_tmp; 
	LongObject * new = LongObject_Init();
	new->size = self->size;
	new->value = malloc(new->size);
	for (int i = 0; i < new->size; ++i){
		new->value[i]=self->value[i];
	}
	new->sign = -self->sign;
	return (BaseObject *)new;
}


BaseObject * LongObject_UnaryBool(BaseObject * self_tmp){
	return NULL;
	// if(!OBJCHECKTYPE(self_tmp,"Long")){
	// 	//exception handler
	// }
	// LongObject * self = (LongObject *)self_tmp;
	// if(self->value == 0){
	// 	return False;
	// }
	// return True;
}


BaseObject * LongObject_Fromlong(long value){
	return NULL;
	// LongObject * o = LongObject_Init();
	
	// if(value < 0){
	// 	value = -value;
	// 	o->sign = -1;
	// }

	// o->value = (LongObject_basedatatype)value;
	// return (BaseObject *)o;
}

long LongObject_Tolong(BaseObject * o_tmp){
	return 0;
	// LongObject * o = (LongObject *)o_tmp; 
	// return o->value*o->sign;
}


void LongObject_DESTRUCT(BaseObject * self_tmp){
	LongObject * self = (LongObject *)self_tmp;
	printf("Long <%p> deleting itself\n",self_tmp);
	if(self->value != NULL){
		free(self->value);
	}
	free(self);
}


NumberMethods LongObject_NumberMethods = {
	//normal
		//arithmetic
		LongObject_BinaryAdd,	// add
		0,	// sub
		0,	// div
		0,	// truediv
		0,	// mod
		0,	// mul
		0,	// pow

		//logic
		0,	// and
		0,	// or
		0,	// xor
		0,	// not
		0,	// rshift
		0,	// lshift

		//other

	//inplace
		//arithmetic
		0,	// iadd
		0,	// isub
		0,	// idiv
		0,	// itruediv
		0,	// imod
		0,	// imul
		0,	// ipow

		//logic
		0,	// iand
		0,	// ior
		0,	// ixor
		0,	// inot
		0,	// irshift
		0,	// ilshift

		//other

	//unary
	0,	// pos;
	LongObject_UnaryNegate,	// neg;
	0,	// inv;
};

CompareMethods LongObject_Compare = {
	LongObject_BinaryEQ,	// EQ
	0,	// NEQ
	0,	// LT
	0,	// GT
	0,	// LTE
	0,	// GTE
	LongObject_UnaryBool,	// ASBOOL
};


TypeObject LongType = {
	VarBaseObject_HEAD_INIT(&BaseObjectType,0)
	"Long",										//typename
	sizeof (LongObject),						//startsize
	0,											//itemsize
	&LongObject_DESTRUCT,						//destructor!
	&LongObject_Compare,						//comparemethods
	&LongObject_NumberMethods,					//numbermethods
	0,											//itermethods
	&LongObject_Hash,							//hash
	&LongObject_Repr,							//repr
};

LongObject * LongObject_Init(){
	LongObject * a = malloc(sizeof(LongObject));
	
	*a = (LongObject) {
		BaseObject_HEAD_INIT(&LongType)
		NULL,
		0,
		1
	};

	Fox_Initialize_Object((BaseObject *)a);
	return a;
}