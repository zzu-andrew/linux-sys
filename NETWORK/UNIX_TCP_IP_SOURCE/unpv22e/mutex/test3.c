/* verify that not calling pthread_attr_destroy() causes memory leak */

#include	"unpipc.h"

int
main(int argc, char **argv)
{
	pthread_attr_t	attr;

	for ( ; ; ) {
		Pthread_attr_init(&attr);
	}

	exit(0);
}
