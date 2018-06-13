#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <Foxlang.h>



instruction * execute_one(instruction * i, frame * f){
	#if DEBUGVM
	printf("%s %i\n",id_to_instruction(i->id),i->id);
	#endif

	int finit = false;
	if(f == NULL){
		f = frame_init();
		finit = true;
	}
	BaseObject * a;
	BaseObject * b;
	// BaseObject * c;

	switch(i->id){
		case NOP:
			return i->next;
			break;
		case STP:
			return NULL;
			break;
		case LDC:
			SPUSH(f,f->constants[i->arg]);
			return i->next;
			break;
		case ADD:	
			a = SPOP(f);
			b = SPOP(f);
			if(OBJTYPE(a)->number!=NULL && OBJTYPE(a)->number->add!=NULL){
				SPUSH(f,OBJTYPE(a)->number->add(a,b));
				DECREF(a);
				DECREF(b);
			}else{
				RAISE(ExceptionObject_FromCHARPNT_FMT("TyperError: cant add %s to %s",OBJTYPE(a)->typename,OBJTYPE(b)->typename));
			}
			return i->next;
			break;			
		case PRNT:
			BaseObject_PRINTFUNC(STOP(f));
			return i->next;
			break;
		default:
			return i->next;
			break;
	}

	if(finit){
		frame_DESTRUCT(f);
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
	execute(f->start,f);
	return f;
}

frame * execute_frames(frame * f){
	return NULL;
}

instruction * execute(instruction * i, frame * f){
	
	int finit = false;
	if(f == NULL){
		f = frame_init();
		finit = true;
	}

	instruction * next = i;
	while (1){
		if(next==NULL){
			return NULL;
		}
		printf("%p\n",next);
		next = execute_one(next,f);
	}

	if(finit){
		frame_DESTRUCT(f);
	}
	return next;
}

void instruction_DESTRUCT(instruction * i){
	free(i->file);
	free(i->function);
	free(i);
}

void instruction_DESTRUCT_Recursive(instruction * i){
	while(i->next != NULL){
		i=i->next;
		free(i);
	}
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

frame * frame_init(){
	frame * i = malloc(1*sizeof(frame));
	*i = (frame){
		NULL,
		malloc(100*sizeof(BaseObject *)),
		100,
		0,
		malloc(100*sizeof(BaseObject *)),
		100,
		0,

		NULL,
	};
	return i;
}

void frame_DESTRUCT(frame * i){
	free(i->callstack);
	free(i->stack);
	free(i);
}

void frame_DESTRUCT_Recursive(frame * i){
	instruction_DESTRUCT_Recursive(i->start);
	free(i->callstack);
	free(i->stack);
	free(i);
}

instruction * add_instruction_after(InstructionID id,int arg,instruction * last){
	instruction * i = instruction_init(id);
	if(last != NULL){
		last->next = i;
	}
	i->prev[0]=last;
	last = i;
	setarg(i,arg);
	return i;	
}

instruction * add_instruction_after_prev(InstructionID id,int arg){
	static instruction * last = NULL;

	instruction * i = instruction_init(id);
	if(last != NULL){
		last->next = i;
	}
	i->prev[0]=last;
	last = i;
	setarg(i,arg);
	return i;
}