#ifndef FOXLANG_H
#define FOXLANG_H

#define DEBUGMEM 0
#define DEBUGVM 1

#if DEBUGMEM
#define DEBUGDEALLOC 1
#else
#define DEBUGDEALLOC 0
#endif

#include <Typedefs.h>

#include <numbers.h>

#include <Object.h>
#include <Integer.h>
#include <Long.h>
#include <Dictionary.h>
#include <Boolean.h>
#include <String.h>
#include <Exception.h>
#include <List.h>
#include <Iterator.h>

#include <Memory.h>

#include <Default.h>

#include <env.h>

#if DEBUGMEM
#include <debug.h>
#endif

#include <tokenizer.h>
#include <VM.h>

#endif