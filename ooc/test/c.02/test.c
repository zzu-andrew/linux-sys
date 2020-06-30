#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>

void test(void);

struct String {
	const void * class;	/* must be first */
	char * text;
};

struct Class {
	size_t size;
	void  (* test) (void);
};
void test(void)
{
    printf("test for point.\n");
}



static const struct Class _String = {
	sizeof(struct String),
	test
};

const void * String = & _String;

/**
 *  
 */
int main(int argc, char const *argv[])
{
    size_t stringSize = sizeof(struct String);
    


    const struct Class * class = String;
	void * p = calloc(1, class -> size);

	assert(p);
     
	* (const struct Class **) p = class;

    struct String {
        const void * class;	/* must be first */
        char * text;
    };
    struct String * p = (struct String *)calloc(1, sizeof(struct String));
    

    return 0;
}
