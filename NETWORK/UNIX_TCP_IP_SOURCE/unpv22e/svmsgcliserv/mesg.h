#include	"unpipc.h"

/* Our own "messages" to use with pipes, FIFOs, and message queues. */

	/* 4want sizeof(struct mymesg) <= PIPE_BUF */
#define	MAXMESGDATA	(PIPE_BUF - 2*sizeof(long))

	/* 4length of mesg_len and mesg_type */
#define	MESGHDRSIZE	(sizeof(struct mymesg) - MAXMESGDATA)

struct mymesg {
  long	mesg_len;	/* #bytes in mesg_data, can be 0 */
  long	mesg_type;	/* message type, must be > 0 */
  char	mesg_data[MAXMESGDATA];
};

ssize_t	 mesg_send(int, struct mymesg *);
void	 Mesg_send(int, struct mymesg *);
ssize_t	 mesg_recv(int, struct mymesg *);
ssize_t	 Mesg_recv(int, struct mymesg *);
