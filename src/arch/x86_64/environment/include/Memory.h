#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>
#include <Foxlang.h>
// #define FOX_MEMORY_BLOCK_SIZE 4096

// typedef struct{
// 	void * objects;
// 	int size;
// 	int filled;
// }Fox_Memory_Block;


void BaseObject_Dealloc(BaseObject * o);

void Fox_Initialize_Object(BaseObject * a);

void Fox_Clean_Init();
void Fox_Clean();
// void alloc_block_next();
// void alloc_block(int);

// void memory_init();
// void memory_exit();
// void memory_freeall();


#endif