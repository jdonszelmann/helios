
#ifndef INSTRUCTION_H
#define INSTRUCTION_H

typedef enum {
	//flow
	NOP,
	STP,
	CALL,
	RET,
	//math
	ADD,
	SUB,
	MUL,
	DIV,
	//stack
	POPTOP,
	ROT1,
	ROT2,
	ROT3,
	ROT4,
	DUP,
	//variables
	LDC, //load constant
	LDV, //load variable
	STV, //store variable

}InstructionID;

#define addcase(x) case x:return #x

inline char * id_to_instruction(InstructionID id){
	switch(id){
		addcase(NOP);
		addcase(STP);
		addcase(CALL);
		addcase(RET);
		addcase(ADD);
		addcase(SUB);
		addcase(MUL);
		addcase(DIV);
		addcase(POPTOP);
		addcase(ROT1);
		addcase(ROT2);
		addcase(ROT3);
		addcase(ROT4);
		addcase(DUP);
		default:return "NOP";
	}
}

#define setarg(x,y) x->arg=y  

typedef struct instruction{
	InstructionID id;
	struct instruction * next;

	struct instruction ** prev;
	int numprevs;

	int line;
	char * file;
	char * function;

	int arg;
}instruction;

typedef struct frame{
	instruction * start;
	BaseObject ** callstack;
	BaseObject ** stack;
}frame;

instruction * execute_one(instruction * i, frame * f);
instruction * execute_n(instruction * i, frame * f, int n);
frame * execute_frame(frame * f);
frame * execute_frames(frame * f);
instruction * execute(instruction * i, frame * f);


instruction * add_instruction_after_prev(InstructionID id);
instruction * add_instruction_after(InstructionID id,instruction * last);
instruction * instruction_init(InstructionID id);
void instruction_DESTRUCT(instruction * i);
void instruction_DESTRUCT_Recursive(instruction * i);

#endif