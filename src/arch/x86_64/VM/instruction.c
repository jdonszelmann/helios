#include <stdio.h>
#include <stdlib.h>

#include <Foxlang.h>



instruction * execute_one(instruction * i, frame * f){
	#if DEBUGVM
	printf("%s\n",id_to_instruction(i->id));
	#endif

	switch(i->id){
		case NOP:
			return i->next;
			break;
		case STP:
			return NULL;
			break;
		default:
			return i->next;
			break;
	}
}

instruction * execute_n(instruction * i, frame * f, int n){
	instruction * next = i;
	for (int i = 0; i < n; ++i){
		if(next==NULL){
			return NULL;
		}
		next = execute_one(next,f);
	}
	return next;
}

frame * execute_frame(frame * f){
	return NULL;
}

frame * execute_frames(frame * f){
	return NULL;
}

instruction * execute(instruction * i, frame * f){
	instruction * next = i;
	while (1){
		if(next==NULL){
			return NULL;
		}
		printf("%p\n",next);
		next = execute_one(next,f);
	}
	return next;
}

void instruction_DESTRUCT(instruction * i){
	free(i->prev);
	free(i->file);
	free(i->function);
	free(i);
}

void instruction_DESTRUCT_Recursive(instruction * i){
	if(i->next != NULL){
		instruction_DESTRUCT_Recursive(i->next);
	}
	free(i->prev);
	free(i->file);
	free(i->function);
	free(i);
}

instruction * instruction_init(InstructionID id){
	instruction * i = malloc(1*sizeof(instruction));
	*i = (instruction){
		id,

		NULL,
		calloc(1,sizeof(instruction *)),
		1,

		-1,
		NULL,
		NULL,
		0,
	};
	return i;
}

instruction * add_instruction_after(InstructionID id,instruction * last){
	instruction * i = instruction_init(id);
	if(last != NULL){
		last->next = i;
	}
	i->prev[0]=last;
	last = i;
	return i;	
}

instruction * add_instruction_after_prev(InstructionID id){
	static instruction * last = NULL;

	instruction * i = instruction_init(id);
	if(last != NULL){
		last->next = i;
	}
	i->prev[0]=last;
	last = i;
	return i;
}