/* verify that calling pthread_*attr_destroy() avoids memory leak */

#include	"unpipc.h"

int
main(int argc, char **argv)
{
	pthread_mutexattr_t	mattr;
	pthread_condattr_t	cattr;

	for ( ; ; ) {
		Pthread_mutexattr_init(&mattr);
		Pthread_mutexattr_destroy(&mattr);
		Pthread_condattr_init(&cattr);
		Pthread_condattr_destroy(&cattr);
	}

	exit(0);
}
