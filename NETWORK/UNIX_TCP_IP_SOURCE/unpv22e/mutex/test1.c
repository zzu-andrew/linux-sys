/* verify that not calling pthread_*attr_destroy() causes memory leak */

#include	"unpipc.h"

int
main(int argc, char **argv)
{
	pthread_mutexattr_t	mattr;
	pthread_condattr_t	cattr;

	for ( ; ; ) {
		Pthread_mutexattr_init(&mattr);
		Pthread_condattr_init(&cattr);
	}

	exit(0);
}
