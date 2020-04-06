/* verify that calling pthread_attr_destroy() avoids memory leak */

#include	"unpipc.h"

int
main(int argc, char **argv)
{
	pthread_attr_t	attr;

	for ( ; ; ) {
		Pthread_attr_init(&attr);
		Pthread_attr_destroy(&attr);
	}

	exit(0);
}
