

#include <stdio.h>
#include <stdlib.h>
#include <debug.h>

int allocs = 0;
int frees = 0;
int reallocs = 0;

int total = 0;

void debug_print(){
	total = 0;
	printf("alloc:%i\nfree:%i\nrealloc:%i\n",allocs,frees,reallocs);
	allocs = 0;
	frees = 0;
	reallocs = 0;
}

void * dbg_malloc(int size,int line,const char * file, const char * func){
	allocs++;
	total++;
	void *p = (malloc)(size);
	printf ("%i: Allocated = %s, %d, %s, %p\n",total, file, line, func, p);
	return p;
}


void dbg_free(void * orig,int line,const char * file, const char * func){
	if(orig == NULL){
		return;
	}
	frees++;
	total--;
	printf ("%i: Freed = %s, %d, %s, %p\n",total, file, line, func, orig);
	(free)(orig);
}

void * dbg_realloc(void * orig,int size,int line,const char * file, const char * func){
	reallocs++;
	void *p = (realloc)(orig,size);
	printf ("Reallocated = %s, %d, %s, %p->%p\n", file, line, func,orig,p);
	return p;
}

