#include	"unpipc.h"

int
main(int argc, char **argv)
{
	printf("sizeof(pthread_mutex_t) = %d\n", sizeof(pthread_mutex_t));
	printf("sizeof(pthread_cond_t) = %d\n", sizeof(pthread_cond_t));
	printf("sizeof(struct sigevent) = %d\n", sizeof(struct sigevent));
	exit(0);
}
