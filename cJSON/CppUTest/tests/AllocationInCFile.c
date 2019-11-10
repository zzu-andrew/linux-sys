/***
 * Excerpted from "Test-Driven Development for Embedded C",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material, 
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose. 
 * Visit http://www.pragmaticprogrammer.com/titles/jgade for more book information.
***/
#include <stdlib.h>
#include "AllocationInCFile.h"
#include "CppUTest/MemoryLeakDetectorMallocMacros.h"

/* This file is for simulating overloads of malloc */

char* mallocAllocation()
{
	return malloc(10UL);
}

void freeAllocation(void* memory)
{
	free(memory);
}

#undef free

void freeAllocationWithoutMacro(void* memory)
{
	free(memory);
}

