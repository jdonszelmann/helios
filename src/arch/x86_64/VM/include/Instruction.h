
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

	//IO
	PRNT,

}InstructionID;

#define addcase(x) case x:return #x

#define SPUSH(x,y) x->stack[(x->stacksize)++]=y
#define SPOP(x) x->stack[--(x->stacksize)]
#define STOP(x) x->stack[x->stacksize-1]
#define STOPX(x,y) x->stack[x->stacksize-(1+y)]


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
		addcase(PRNT);
		addcase(LDC);
		addcase(STV);
		addcase(LDV);
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
	int callstacksize;
	int callstackfilled;
	BaseObject ** stack;
	int stacksize;
	int stackfilled;

	BaseObject ** constants;
}frame;

instruction * execute_one(instruction * i, frame * f);
instruction * execute_n(instruction * i, frame * f, int n);
frame * execute_frame(frame * f);
frame * execute_frames(frame * f);
instruction * execute(instruction * i, frame * f);


instruction * add_instruction_after_prev(InstructionID id,int arg);
instruction * add_instruction_after(InstructionID id,int arg,instruction * last);
instruction * instruction_init(InstructionID id);
void instruction_DESTRUCT(instruction * i);
void instruction_DESTRUCT_Recursive(instruction * i);

frame * frame_init();
void frame_DESTRUCT_Recursive(frame * i);
void frame_DESTRUCT(frame * i);

#endif