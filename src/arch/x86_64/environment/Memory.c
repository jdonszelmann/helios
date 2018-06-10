
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <Foxlang.h>

// Fox_Memory_Block * fox_memory;
// int fox_memory_size = 1;
// int fox_memory_currsize = 0;


// int memory_initialized; 


// void memory_init(){
// 	fox_memory = malloc(fox_memory_size*sizeof(Fox_Memory_Block));
// 	alloc_block_next();
// 	memory_initialized = true;
// }


// void memory_exit(){
// 	memory_freeall();
// 	memory_initialized = false;
// }

// void memory_freeall(){

// }

// void alloc_block_next(){
// 	return alloc_block(fox_memory_currsize);
// }

// void alloc_block(int where){
// 	fox_memory_currsize++;
// 	if(fox_memory_currsize > fox_memory_size){
// 		fox_memory_size*=2;
// 		fox_memory = realloc(fox_memory,fox_memory_size);
// 	}
// 	fox_memory[where] = (Fox_Memory_Block){
// 		malloc(FOX_MEMORY_BLOCK_SIZE),
// 		FOX_MEMORY_BLOCK_SIZE,
// 		0
// 	};
// }


static int objlistsize = 100;
static int objlistlength = 0;
static BaseObject ** objectlist = NULL;

static int clean_initialized = 0;


void BaseObject_Dealloc(BaseObject * o){
	if(clean_initialized){
		return;
	}
	TypeObject * t = OBJTYPE(o);
	#if DEBUGDEALLOC
	printf("deallocating %s at %p\n",OBJTYPE(o)->typename,o);
	#endif
	if(t == NULL){
		free(o);
	}else{
		t->destruct_object(o);
	}
}

void Fox_Initialize_Object(BaseObject * a){
	if(objectlist == NULL){
		objectlist = malloc(objlistsize*sizeof(BaseObject *));
	}
	if(objlistlength >= objlistsize){
		objlistsize*=2;
		objectlist = realloc(objectlist,objlistsize*sizeof(BaseObject *));
	}

	objectlist[objlistlength] = a;
	objlistlength++;
}

void Fox_Clean_Init(){
	clean_initialized = 1;
}

void Fox_Clean(){
	clean_initialized = 0;
	if (objectlist != NULL){
		for (int i = 0; i < objlistlength; ++i){
			BaseObject_Dealloc(objectlist[i]);
		}
		free(objectlist);
		objectlist = NULL;
		objlistlength = 0;
		objlistsize = 100;
	}
}

// void BaseObject_Alloc(int size){
// 	if(!memory_initialized){
// 		printf("fox memory found uninitialized. initializing....");
// 		memory_init();
// 	}

// }