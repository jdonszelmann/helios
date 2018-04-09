
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <math.h>
#include <assert.h>

#include <Foxlang.h>



TypeObject IntegerType = {
	VarBaseObject_HEAD_INIT(&BaseObjectType,0)
	"int",
	sizeof (IntegerObject),
	0,
	0
};

IntegerObject * IntegerObject_Init(int startsize){
	IntegerObject * a = malloc(sizeof(IntegerObject));
	*a = (IntegerObject) {
		BaseObject_HEAD_INIT(&IntegerType)
		malloc(sizeof(unsigned char)*startsize),
		startsize,
		1
	};
	return a;
}

void IntegerObject_Resize(BaseObject * i_tmp, int length){
	IntegerObject * i = (IntegerObject *)i_tmp;
	i->length = length;
	i->value = realloc(i->value, ceil((length*sizeof(unsigned char))/2));
}


BaseObject * IntegerObject_Fromstring(char * value){
	int size = strlen(value);
	printf("size %i\n", size);
	IntegerObject * a = IntegerObject_Init(size);

	int lower = -1;
	int i;

	// packing unsigned chars as
	// lower:higher (4:4)

	for (i = 0; i < size; ++i)
	{
		char substr[2];
		strncpy(substr, value+i, 1);
		unsigned char ret = (unsigned char)strtol(substr, NULL, 10);
		assert(ret < 16 && ret > 0);
		
		if(lower == -1){
			lower = ret;
		}else{
			a->value[(int)floor(i/2)] = (unsigned char)(lower + (ret<<4));
			lower = -1;
		}
	}
	
	if(lower != -1){
		a->value[i+1] = lower;
	}

	return (BaseObject *)a;
}

char * IntegerObject_Repr(BaseObject * o_tmp){

	IntegerObject * o = (IntegerObject *)o_tmp;
	char * largebuffer = malloc(ceil(((o->length)*sizeof(unsigned char)) / 2) + 5);
	if(o->sign == -1){
		strcpy(largebuffer,"-");
	}else{
		strcpy(largebuffer,"");
	}
	int lower = 0;
	for(int i = 0; i < o->length; i++){
		char buffer[2];
		if(lower == 0){		
			sprintf(buffer,"%u", o->value[(int)floor(i/2)] & 0x0F);
			lower = 1;
		}else{
			sprintf(buffer,"%u", (o->value[(int)floor(i/2)] & 0xF0) >> 4);
			lower = 0;
		}
		strcat(largebuffer,buffer);
	}
	return largebuffer;
}

BaseObject * IntegerObject_Add(BaseObject * self_tmp,BaseObject * other_tmp){
	if(self_tmp->object_type->typename != "int"){
		//exception handler
	}
	IntegerObject * self = (IntegerObject *)self_tmp; 
	if(other_tmp->object_type->typename == "int"){
		IntegerObject * other = (IntegerObject *)other_tmp; 
		
		int length = self->length;
		// int shortlength = other->length;

		if(other->length > self->length){
			length = other->length;
			// shortlength self->length;
		}

		IntegerObject * new = IntegerObject_Init(length);
		unsigned char selfdigit;
		unsigned char otherdigit;
		unsigned char carry = 0;
		unsigned char tempval1;
		unsigned char tempval2;
		int oddeven = 0;
		for (int i = 0; i < length; ++i)
		{
			selfdigit = 0;
			if (i < self->length){
				if (oddeven == 0){
					selfdigit = self->value[(int)floor(i/2)] & 0x0F;
				}else{
					selfdigit = (self->value[(int)floor(i/2)] & 0xF0) >> 4;	
				}
			}
			otherdigit = 0;
			if (i < self->length){
				if (oddeven == 0){
					otherdigit = other->value[(int)floor(i/2)] & 0x0F;
				}else{
					otherdigit = (other->value[(int)floor(i/2)] & 0xF0) >> 4;
				}
			}

			if(oddeven == 0){
				tempval1 = selfdigit + otherdigit + carry;
				carry = 0;
				if (tempval1 > 9){
					tempval1 = tempval1 - 10;
					carry = 1;
				}
				oddeven = 1;
			}else{
				tempval2 = selfdigit + otherdigit + carry;
				carry = 0;
				if (tempval2 > 9){
					tempval2 = tempval2 - 10;
					carry = 1;
				}

				new->value[(int)floor(i/2)] = (unsigned char)(tempval1 + (tempval2<<4));
				oddeven = 0;
			}				
		}
		if(carry == 1){
			IntegerObject_Resize((BaseObject *)new, new->length + 1);
			new->value[new->length-1] = 1;
		}
		return (BaseObject *) new;

	}else if(0){//float
		
	}else{
		//exception handler
	}
	// IntegerObject * o = (IntegerObject *)o_tmp;
	return NULL;
}


BaseObject * IntegerObject_Fromlong(unsigned long value){
	char buffer[10];
	sprintf(buffer,"%li",value);
	return IntegerObject_Fromstring(buffer);
}

long IntegerObject_Tolong(BaseObject * o_tmp){

	char * repr = IntegerObject_Repr(o_tmp);
	unsigned long res = (unsigned long)strtoul(repr, NULL, 10);

	if(errno == ERANGE){
		return 0;
	}
	return res;
}