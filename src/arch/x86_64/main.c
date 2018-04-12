
#include <stdio.h>
#include <stdlib.h>

#include <Foxlang.h>






int main(int argc, char *argv[]){
	BaseObject * a = IntegerObject_Fromstring("81");
	BaseObject * b = IntegerObject_Fromstring("82");
	// BaseObject * c = IntegerObject_Fromstring("83");
	// BaseObject * d = IntegerObject_Fromstring("84");
	// BaseObject * e = IntegerObject_Fromstring("85");
	// BaseObject * f = IntegerObject_Fromstring("86");
	// BaseObject * g = IntegerObject_Fromstring("87");
	// BaseObject * h = IntegerObject_Fromstring("88");
	// BaseObject * i = IntegerObject_Fromstring("89");
	// BaseObject * j = IntegerObject_Fromstring("90");
	// BaseObject * k = IntegerObject_Fromstring("91");
	// BaseObject * l = IntegerObject_Fromstring("92");
	// BaseObject * m = IntegerObject_Fromstring("93");
	// BaseObject * n = IntegerObject_Fromstring("94");
	// BaseObject * o = IntegerObject_Fromstring("95");
	// BaseObject * p = IntegerObject_Fromstring("96");
	// BaseObject * q = IntegerObject_Fromstring("97");
	// BaseObject * r = IntegerObject_Fromstring("98");
	// BaseObject * s = IntegerObject_Fromstring("99");
	// BaseObject * dict = (BaseObject *)DictionaryObject_Init();
	// DictionaryObject_Insert(dict,a,False);
	// DictionaryObject_Insert(dict,b,False);
	// DictionaryObject_Insert(dict,c,False);
	// DictionaryObject_Insert(dict,d,False);
	// DictionaryObject_Insert(dict,e,False);
	// DictionaryObject_Insert(dict,f,False);
	// DictionaryObject_Insert(dict,g,False);
	// DictionaryObject_Insert(dict,h,False);
	// DictionaryObject_Insert(dict,i,False);
	// DictionaryObject_Insert(dict,j,False);
	// DictionaryObject_Insert(dict,k,False);
	// DictionaryObject_Insert(dict,l,False);
	// DictionaryObject_Insert(dict,m,False);
	// DictionaryObject_Insert(dict,n,False);
	// DictionaryObject_Insert(dict,o,False);
	// DictionaryObject_Insert(dict,p,False);
	// DictionaryObject_Insert(dict,q,False);
	// DictionaryObject_Insert(dict,r,False);
	// DictionaryObject_Insert(dict,s,False);
	
	// printf(">%i\n",BOOLEAN_IS_TRUE(BaseObject_Compare(a,b,EQ)));
	// printf("%ld\n", IntegerObject_Tolong(a));
	// printf("%ld\n", IntegerObject_Tolong(b));

	printf("%s\n",IntegerObject_Repr_CHARPNT(IntegerObject_BinaryAdd(a,b)));
	DECREF(a);
	DECREF(b);
	return 0;
}


