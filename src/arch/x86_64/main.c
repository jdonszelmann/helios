
#include <stdio.h>
#include <stdlib.h>

#include <Foxlang.h>

#define ERROR(o) printf("error %s at line %d (%s)",(char *)o,__LINE__,__FILE__);

int main(int argc, char *argv[]){
	BaseObject * a = IntegerObject_Fromstring("0");
	BaseObject * b = IntegerObject_Fromstring("1");
	BaseObject * string = StringObject_Fromstring("a");
	BaseObject * c = IntegerObject_Fromstring("2");
	BaseObject * d = IntegerObject_Fromstring("3");
	BaseObject * e = IntegerObject_Fromstring("4");
	BaseObject * f = IntegerObject_Fromstring("5");
	BaseObject * g = IntegerObject_Fromstring("6");
	BaseObject * h = IntegerObject_Fromstring("7");
	BaseObject * i = IntegerObject_Fromstring("8");
	BaseObject * j = IntegerObject_Fromstring("9");
	BaseObject * k = IntegerObject_Fromstring("10");
	BaseObject * l = IntegerObject_Fromstring("11");
	BaseObject * m = IntegerObject_Fromstring("12");
	BaseObject * n = IntegerObject_Fromstring("13");
	BaseObject * o = IntegerObject_Fromstring("14");
	BaseObject * p = IntegerObject_Fromstring("15");
	BaseObject * q = IntegerObject_Fromstring("16");
	BaseObject * r = IntegerObject_Fromstring("17");
	BaseObject * s = IntegerObject_Fromstring("18");
	BaseObject * dict = (BaseObject *)DictionaryObject_Init();
	DictionaryObject_Insert(dict,a,False);
	DictionaryObject_Insert(dict,b,False);
	DictionaryObject_Insert(dict,string,False);
	DictionaryObject_Insert(dict,c,False);
	DictionaryObject_Insert(dict,d,False);
	DictionaryObject_Insert(dict,e,False);
	DictionaryObject_Insert(dict,f,False);
	DictionaryObject_Insert(dict,g,True);
	DictionaryObject_Insert(dict,h,False);
	DictionaryObject_Insert(dict,i,False);
	DictionaryObject_Insert(dict,j,False);
	DictionaryObject_Insert(dict,k,False);
	DictionaryObject_Insert(dict,l,False);
	DictionaryObject_Insert(dict,m,False);
	DictionaryObject_Insert(dict,n,False);
	DictionaryObject_Insert(dict,o,False);
	DictionaryObject_Insert(dict,p,False);
	DictionaryObject_Insert(dict,q,False);
	DictionaryObject_Insert(dict,r,False);
	DictionaryObject_Insert(dict,s,False);
	
	printf("%s\n",BaseObject_Repr_CHARPNT(DictionaryObject_Retrieve(dict,IntegerObject_Fromstring("0"))));

	printf(">%s\n",DictionaryObject_Repr_CHARPNT(dict));
	// printf(">%i\n",BOOLEAN_IS_TRUE(BaseObject_Compare(a,b,EQ)));
	// printf("%ld\n", IntegerObject_Tolong(a));
	// printf("%ld\n", IntegerObject_Tolong(b));
	// printf(">>%s\n",DictionaryObject_Repr_CHARPNT(dict));

	printf("%s\n",BaseObject_Repr_CHARPNT(IntegerObject_BinaryAdd(a,b)));
	DECREF(a);
	DECREF(b);
	return 0;
}


