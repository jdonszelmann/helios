#ifndef NUMBERS_H
#define NUMBERS_H
#include <Foxlang.h>

typedef int (*inquiry)(struct baseobj *, struct baseobj *, struct baseobj *);
typedef struct baseobj * (*TernaryOperator)(struct baseobj *, struct baseobj *, struct baseobj *);
typedef struct baseobj * (*BinaryOperator)(struct baseobj *, struct baseobj *);
typedef struct baseobj * (*UnaryOperator)(struct baseobj *);
typedef struct baseobj * (*UnaryFunc)(struct baseobj *);
typedef struct baseobj * (*BinaryFunc)(struct baseobj *,struct baseobj *);
typedef struct baseobj * (*TernaryFunc)(struct baseobj *, struct baseobj *, struct baseobj *);

typedef struct comparemethods{
	BinaryOperator EQ;
	BinaryOperator NEQ;
	BinaryOperator LT;
	BinaryOperator GT;
	BinaryOperator LTE;
	BinaryOperator GTE;
	UnaryOperator ASBOOL;
}CompareMethods;


typedef struct numbermethods{
	//normal
		//arithmetic
		BinaryOperator add;
		BinaryOperator sub;
		BinaryOperator div;
		BinaryOperator truediv;
		BinaryOperator mod;
		BinaryOperator mul;
		BinaryOperator pow;

		//logic
		BinaryOperator and;
		BinaryOperator or;
		BinaryOperator xor;
		BinaryOperator not;
		BinaryOperator rshift;
		BinaryOperator lshift;

		//other

	//inplace
		//arithmetic
		BinaryOperator iadd;
		BinaryOperator isub;
		BinaryOperator idiv;
		BinaryOperator itruediv;
		BinaryOperator imod;
		BinaryOperator imul;
		BinaryOperator ipow;

		//logic
		BinaryOperator iand;
		BinaryOperator ior;
		BinaryOperator ixor;
		BinaryOperator inot;
		BinaryOperator irshift;
		BinaryOperator ilshift;

		//other
	//unary
	UnaryOperator pos;
	UnaryOperator neg;
	UnaryOperator inv;

	//conversion
	UnaryFunc asint;

}NumberMethods;

#endif