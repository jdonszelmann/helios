#ifndef FOXLANG_H
#define FOXLANG_H

#define DEBUGMEM 0
#define DEBUGVM 1


#include <Typedefs.h>

#include <numbers.h>

#include <Object.h>
#include <Integer.h>
#include <Long.h>
#include <Dictionary.h>
#include <Boolean.h>
#include <String.h>
#include <Exception.h>

#include <Memory.h>

#include <env.h>

#if DEBUGMEM
#include <debug.h>
#endif

#include <VM.h>

#endif