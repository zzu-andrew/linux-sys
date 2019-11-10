/***
 * Excerpted from "Test-Driven Development for Embedded C",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material, 
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose. 
 * Visit http://www.pragmaticprogrammer.com/titles/jgade for more book information.
***/
#include "ClassName.h"
#include <stdlib.h>
#include <memory.h>

typedef struct ClassNameStruct
{
    int placeHolderForHiddenStructElements;
} ClassNameStruct;

ClassName ClassName_Create(void)
{
     ClassName self = calloc(1, sizeof(ClassNameStruct));
     return self;
}

void ClassName_Destroy(ClassName self)
{
    free(self);
}


