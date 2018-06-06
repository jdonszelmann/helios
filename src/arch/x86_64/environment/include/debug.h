
#ifndef DEBUG_H
#define DEBUG_H

void * dbg_malloc(int size,int line,const char * file, const char * func);
void dbg_free(void * orig,int line,const char * file, const char * func);
void * dbg_realloc(void * orig,int size,int line,const char * file, const char * func);

#define malloc(x) dbg_malloc(x, __LINE__,__FILE__, __FUNCTION__)
#define free(x) dbg_free(x, __LINE__,__FILE__, __FUNCTION__)
#define realloc(x,y) dbg_realloc(x,y,__LINE__,__FILE__, __FUNCTION__)

void debug_print();

#endif
