#include	"unpipc.h"
#include	"example.h"

int
main(int argc, char **argv)
{
	int		size;
	example	foo;

	size = RNDUP(sizeof(foo.a)) + RNDUP(sizeof(foo.b)) +
		   RNDUP(sizeof(foo.c[0])) * MAXC;
	printf("size = %d\n", size);
	exit(0);
}
