#include	"unpipc.h"
#include	"mqueue.h"

#define	BUFFLEN		100
char	msg[BUFFLEN];				/* receive buffer */

char	msg0[] = "";
char	msg1[] = "1";
char	msg2[] = "22";
char	msg3[] = "333";
char	msg4[] = "4444";
char	msg5[] = "55555";
char	msg6[] = "666666";
char	msg7[] = "7777777";
char	msg8[] = "88888888";

static void	sig_alrm(int);
static void	sig_usr1(int);
int		blocked, sigusr1;

int
main(int argc, char **argv)
{
	int		rc;
	pid_t	childpid;
	mymqd_t	mqd;
	unsigned int	prio;
	struct sigevent	sigev;
	struct mymq_attr	attr, info;

	if (argc != 2)
		err_quit("usage: testmymq <pathname>");

		/***************************************************************/
		/* test mq_unlink() error return */
	mymq_unlink(argv[1]);
	if ( ( rc = mymq_unlink(argv[1])) == 0 || errno != ENOENT)
		err_sys("mq_unlink returned %d", rc);

		/***************************************************************/
		/* create a queue with default attributes */
	mqd = Mymq_open(argv[1], O_CREAT | O_EXCL | O_RDWR, FILE_MODE, NULL);
	Mymq_getattr(mqd, &info);
	if (info.mq_maxmsg != 128 || info.mq_msgsize != 1024 ||
		info.mq_flags != 0 || info.mq_curmsgs != 0)
		err_msg("message queue defaults:\n"
				"maxmsg = %ld, msgsize = %ld, flags = %ld, curmsgs = %ld",
		   		info.mq_maxmsg, info.mq_msgsize,
				info.mq_flags, info.mq_curmsgs);
	Mymq_close(mqd);

		/***************************************************************/
		/* check O_EXCL */
	mqd = mymq_open(argv[1], O_CREAT | O_EXCL | O_RDWR, FILE_MODE, NULL);
	if (mqd != (mqd_t) -1 || errno != EEXIST)
		err_sys("mq_open returned %d", rc);
	Mymq_unlink(argv[1]);

		/***************************************************************/
		/* create with attributes */
	attr.mq_maxmsg = 4;
	attr.mq_msgsize = 7;
	mqd = Mymq_open(argv[1], O_CREAT | O_EXCL | O_RDWR, FILE_MODE, &attr);
	Mymq_getattr(mqd, &info);
	if (info.mq_maxmsg != 4 || info.mq_msgsize != 7 ||
		info.mq_flags != 0 || info.mq_curmsgs != 0)
		err_quit("1: maxmsg = %ld, msgsize = %ld, flags = %ld, curmsgs = %ld\n",
		   		 info.mq_maxmsg, info.mq_msgsize,
				 info.mq_flags, info.mq_curmsgs);

		/***************************************************************/
		/* send/receive 1 message */
	Mymq_send(mqd, msg1, 1, 1);
	if ( (rc = Mymq_receive(mqd, msg, BUFFLEN, &prio)) != 1)
		err_quit("mq_receive returned %d, expected 1", rc);
	if (prio != 1)
		err_quit("mq_receive returned prio %d, expected 1", prio);

		/* send/receive 1 0-byte message */
	Mymq_send(mqd, msg0, 0, 0);
	if ( (rc = Mymq_receive(mqd, msg, BUFFLEN, &prio)) != 0)
		err_quit("mq_receive returned %d, expected 0", rc);
	if (prio != 0)
		err_quit("mq_receive returned prio %d, expected 0", prio);


		/* send 2 messages/receive in reverse order */
	Mymq_send(mqd, msg1, 1, 1);
	Mymq_send(mqd, msg2, 2, 2);
	if ( (rc = Mymq_receive(mqd, msg, BUFFLEN, &prio)) != 2)
		err_quit("mq_receive returned %d, expected 2", rc);
	if (prio != 2)
		err_quit("mq_receive returned prio %d, expected 2", prio);
	if ( (rc = Mymq_receive(mqd, msg, BUFFLEN, &prio)) != 1)
		err_quit("mq_receive returned %d, expected 1", rc);
	if (prio != 1)
		err_quit("mq_receive returned prio %d, expected 1", prio);

		/* send 3 messages/receive in reverse order */
	Mymq_send(mqd, msg1, 1, 1);
	Mymq_send(mqd, msg2, 2, 2);
	Mymq_send(mqd, msg3, 3, 3);
	if ( (rc = Mymq_receive(mqd, msg, BUFFLEN, &prio)) != 3)
		err_quit("mq_receive returned %d, expected 3", rc);
	if (prio != 3)
		err_quit("mq_receive returned prio %d, expected 3", prio);
	if ( (rc = Mymq_receive(mqd, msg, BUFFLEN, &prio)) != 2)
		err_quit("mq_receive returned %d, expected 2", rc);
	if (prio != 2)
		err_quit("mq_receive returned prio %d, expected 2", prio);
	if ( (rc = Mymq_receive(mqd, msg, BUFFLEN, &prio)) != 1)
		err_quit("mq_receive returned %d, expected 1", rc);
	if (prio != 1)
		err_quit("mq_receive returned prio %d, expected 1", prio);

		/* send 4 messages/receive in reverse order */
	Mymq_send(mqd, msg1, 1, 1);
	Mymq_send(mqd, msg2, 2, 2);
	Mymq_send(mqd, msg3, 3, 3);
	Mymq_send(mqd, msg4, 4, 4);
	if ( (rc = Mymq_receive(mqd, msg, BUFFLEN, &prio)) != 4)
		err_quit("mq_receive returned %d, expected 4", rc);
	if (prio != 4)
		err_quit("mq_receive returned prio %d, expected 4", prio);
	if ( (rc = Mymq_receive(mqd, msg, BUFFLEN, &prio)) != 3)
		err_quit("mq_receive returned %d, expected 3", rc);
	if (prio != 3)
		err_quit("mq_receive returned prio %d, expected 3", prio);
	if ( (rc = Mymq_receive(mqd, msg, BUFFLEN, &prio)) != 2)
		err_quit("mq_receive returned %d, expected 2", rc);
	if (prio != 2)
		err_quit("mq_receive returned prio %d, expected 2", prio);
	if ( (rc = Mymq_receive(mqd, msg, BUFFLEN, &prio)) != 1)
		err_quit("mq_receive returned %d, expected 1", rc);
	if (prio != 1)
		err_quit("mq_receive returned prio %d, expected 1", prio);

		/***************************************************************/
		/* send/receive 1 message */
	Mymq_send(mqd, msg4, 4, 4);
	if ( (rc = Mymq_receive(mqd, msg, BUFFLEN, &prio)) != 4)
		err_quit("mq_receive returned %d, expected 4", rc);
	if (prio != 4)
		err_quit("mq_receive returned prio %d, expected 4", prio);

		/* send 2 messages/receive in order */
	Mymq_send(mqd, msg4, 4, 4);
	Mymq_send(mqd, msg3, 3, 3);
	if ( (rc = Mymq_receive(mqd, msg, BUFFLEN, &prio)) != 4)
		err_quit("mq_receive returned %d, expected 4", rc);
	if (prio != 4)
		err_quit("mq_receive returned prio %d, expected 4", prio);
	if ( (rc = Mymq_receive(mqd, msg, BUFFLEN, &prio)) != 3)
		err_quit("mq_receive returned %d, expected 3", rc);
	if (prio != 3)
		err_quit("mq_receive returned prio %d, expected 3", prio);

		/* send 3 messages/receive in order */
	Mymq_send(mqd, msg4, 4, 4);
	Mymq_send(mqd, msg3, 3, 3);
	Mymq_send(mqd, msg2, 2, 2);
	if ( (rc = Mymq_receive(mqd, msg, BUFFLEN, &prio)) != 4)
		err_quit("mq_receive returned %d, expected 4", rc);
	if (prio != 4)
		err_quit("mq_receive returned prio %d, expected 4", prio);
	if ( (rc = Mymq_receive(mqd, msg, BUFFLEN, &prio)) != 3)
		err_quit("mq_receive returned %d, expected 3", rc);
	if (prio != 3)
		err_quit("mq_receive returned prio %d, expected 3", prio);
	if ( (rc = Mymq_receive(mqd, msg, BUFFLEN, &prio)) != 2)
		err_quit("mq_receive returned %d, expected 2", rc);
	if (prio != 2)
		err_quit("mq_receive returned prio %d, expected 2", prio);

		/* send 4 messages/receive in order */
		/* first check EMSGSIZE */
	if ( (rc = mymq_send(mqd, msg4, 8, 4)) == 0 || errno != EMSGSIZE)
		err_sys("mq_send returned %d, expected EMSGSIZE", rc);
	Mymq_send(mqd, msg4, 4, 4);
	Mymq_send(mqd, msg3, 3, 3);
	Mymq_send(mqd, msg2, 2, 2);
	Mymq_send(mqd, msg1, 1, 1);
	if ( (rc = Mymq_receive(mqd, msg, BUFFLEN, &prio)) != 4)
		err_quit("mq_receive returned %d, expected 4", rc);
	if (prio != 4)
		err_quit("mq_receive returned prio %d, expected 4", prio);
	if ( (rc = Mymq_receive(mqd, msg, BUFFLEN, &prio)) != 3)
		err_quit("mq_receive returned %d, expected 3", rc);
	if (prio != 3)
		err_quit("mq_receive returned prio %d, expected 3", prio);
	if ( (rc = Mymq_receive(mqd, msg, BUFFLEN, &prio)) != 2)
		err_quit("mq_receive returned %d, expected 2", rc);
	if (prio != 2)
		err_quit("mq_receive returned prio %d, expected 2", prio);
		/* first check EMSGSIZE */
	if ( (rc = mymq_receive(mqd, msg, 6, &prio)) == 0 || errno != EMSGSIZE)
		err_sys("mq_receive returned %d, expected EMSGSIZE", rc);
	if ( (rc = Mymq_receive(mqd, msg, BUFFLEN, &prio)) != 1)
		err_quit("mq_receive returned %d, expected 1", rc);
	if (prio != 1)
		err_quit("mq_receive returned prio %d, expected 1", prio);

		/* fill queue then close it */
	Mymq_send(mqd, msg1, 1, 1);
	Mymq_send(mqd, msg2, 2, 2);
	Mymq_send(mqd, msg4, 4, 4);
	Mymq_send(mqd, msg3, 3, 3);
	Mymq_close(mqd);
		/* open existing queue nonblocking and read */
	mqd = Mymq_open(argv[1], O_RDWR | O_NONBLOCK);
	Mymq_getattr(mqd, &info);
	if (info.mq_maxmsg != 4 || info.mq_msgsize != 7 ||
		info.mq_flags != O_NONBLOCK || info.mq_curmsgs != 4)
		err_quit("2: maxmsg = %ld, msgsize = %ld, flags = %ld, curmsgs = %ld\n",
		   		 info.mq_maxmsg, info.mq_msgsize,
				 info.mq_flags, info.mq_curmsgs);
	if ( (rc = Mymq_receive(mqd, msg, info.mq_msgsize, &prio)) != 4)
		err_quit("mq_receive returned %d, expected 4", rc);
	if (prio != 4)
		err_quit("mq_receive returned prio %d, expected 4", prio);
	if ( (rc = Mymq_receive(mqd, msg, info.mq_msgsize, &prio)) != 3)
		err_quit("mq_receive returned %d, expected 3", rc);
	if (prio != 3)
		err_quit("mq_receive returned prio %d, expected 3", prio);
	if ( (rc = Mymq_receive(mqd, msg, info.mq_msgsize, &prio)) != 2)
		err_quit("mq_receive returned %d, expected 2", rc);
	if (prio != 2)
		err_quit("mq_receive returned prio %d, expected 2", prio);
	if ( (rc = Mymq_receive(mqd, msg, info.mq_msgsize, &prio)) != 1)
		err_quit("mq_receive returned %d, expected 1", rc);
	if (prio != 1)
		err_quit("mq_receive returned prio %d, expected 1", prio);
		/* check nonblockiing receive */
	if ( (rc = mymq_receive(mqd, msg, info.mq_msgsize, &prio)) == 0 ||
		errno != EAGAIN)
		err_sys("mq_receive returned %d, expected EAGAIN", rc);

		/* fill queue then close it */
	Mymq_send(mqd, msg1, 1, 1);
	Mymq_send(mqd, msg4, 4, 4);
	Mymq_send(mqd, msg2, 2, 2);
	Mymq_send(mqd, msg3, 3, 3);
		/* first check nonblocking send */
	if ( (rc = mymq_send(mqd, msg5, 5, 5)) == 0 || errno != EAGAIN)
		err_sys("mq_send returned %d, expected EAGAIN", rc);
	Mymq_close(mqd);

		/* open existing queue and read */
	mqd = Mymq_open(argv[1], O_RDWR);
	if ( (rc = Mymq_receive(mqd, msg, info.mq_msgsize, &prio)) != 4)
		err_quit("mq_receive returned %d, expected 4", rc);
	if (prio != 4)
		err_quit("mq_receive returned prio %d, expected 4", prio);
		/* now set nonblocking with mq_setattr */
	attr.mq_flags = O_NONBLOCK;
	Mymq_setattr(mqd, &attr, &info);
	if (info.mq_maxmsg != 4 || info.mq_msgsize != 7 ||
		info.mq_flags != 0 || info.mq_curmsgs != 3)
		err_quit("3: maxmsg = %ld, msgsize = %ld, flags = %ld, curmsgs = %ld\n",
		   		 info.mq_maxmsg, info.mq_msgsize,
				 info.mq_flags, info.mq_curmsgs);
	Mymq_getattr(mqd, &info);
	if (info.mq_maxmsg != 4 || info.mq_msgsize != 7 ||
		info.mq_flags != O_NONBLOCK || info.mq_curmsgs != 3)
		err_quit("4: maxmsg = %ld, msgsize = %ld, flags = %ld, curmsgs = %ld\n",
		   		 info.mq_maxmsg, info.mq_msgsize,
				 info.mq_flags, info.mq_curmsgs);
	if ( (rc = Mymq_receive(mqd, msg, info.mq_msgsize, &prio)) != 3)
		err_quit("mq_receive returned %d, expected 3", rc);
	if (prio != 3)
		err_quit("mq_receive returned prio %d, expected 3", prio);
	if ( (rc = Mymq_receive(mqd, msg, info.mq_msgsize, &prio)) != 2)
		err_quit("mq_receive returned %d, expected 2", rc);
	if (prio != 2)
		err_quit("mq_receive returned prio %d, expected 2", prio);
	if ( (rc = Mymq_receive(mqd, msg, info.mq_msgsize, &prio)) != 1)
		err_quit("mq_receive returned %d, expected 1", rc);
	if (prio != 1)
		err_quit("mq_receive returned prio %d, expected 1", prio);
		/* check nonblocking receive */
	if ( (rc = mymq_receive(mqd, msg, info.mq_msgsize, &prio)) == 0 ||
		errno != EAGAIN)
		err_sys("mq_receive returned %d, expected EAGAIN", rc);

		/* now clear nonblocking with mq_setattr */
	attr.mq_flags = 0;
	Mymq_setattr(mqd, &attr, &info);
	if (info.mq_maxmsg != 4 || info.mq_msgsize != 7 ||
		info.mq_flags != O_NONBLOCK || info.mq_curmsgs != 0)
		err_quit("5: maxmsg = %ld, msgsize = %ld, flags = %ld, curmsgs = %ld\n",
		   		 info.mq_maxmsg, info.mq_msgsize,
				 info.mq_flags, info.mq_curmsgs);
	Mymq_getattr(mqd, &info);
	if (info.mq_maxmsg != 4 || info.mq_msgsize != 7 ||
		info.mq_flags != 0 || info.mq_curmsgs != 0)
		err_quit("6: maxmsg = %ld, msgsize = %ld, flags = %ld, curmsgs = %ld\n",
		   		 info.mq_maxmsg, info.mq_msgsize,
				 info.mq_flags, info.mq_curmsgs);
#ifdef	notdef
		/* queue is empty; check that mymq_receive is interruptable */
	Signal(SIGALRM, sig_alrm);
	blocked = 1;
	alarm(4);
	if ( (rc = mymq_receive(mqd, msg, info.mq_msgsize, &prio)) == 0 ||
		errno != EINTR)
		err_sys("mq_receive returned %d, expected EINTR", rc);
	alarm(0);
	printf("mymq_receive interrupted, as expected\n");

		/* fill queue */
	Mymq_send(mqd, msg1, 1, 1);
	Mymq_send(mqd, msg2, 2, 2);
	Mymq_send(mqd, msg3, 3, 3);
	Mymq_send(mqd, msg4, 4, 4);
	Mymq_getattr(mqd, &info);
	if (info.mq_maxmsg != 4 || info.mq_msgsize != 7 ||
		info.mq_flags != 0 || info.mq_curmsgs != 4)
		err_quit("7: maxmsg = %ld, msgsize = %ld, flags = %ld, curmsgs = %ld\n",
		   		 info.mq_maxmsg, info.mq_msgsize,
				 info.mq_flags, info.mq_curmsgs);
		/* queue is full; check that mymq_send is interruptable */
	Signal(SIGALRM, sig_alrm);
	blocked = 1;
	alarm(4);
printf("about to call mymq_send\n");
	if ( (rc = mymq_send(mqd, msg5, 5, 5)) == 0 || errno != EINTR)
		err_sys("mq_send returned %d, expected EINTR", rc);
	alarm(0);
	printf("mymq_send interrupted, as expected\n");
#endif

		/* queue is empty, register for notification */
	sigev.sigev_notify = SIGEV_SIGNAL;
	sigev.sigev_signo = SIGUSR1;
	Signal(SIGUSR1, sig_usr1);
	Mymq_notify(mqd, &sigev);
		/* verify we cannot register twice */
	if ( (rc = mymq_notify(mqd, &sigev)) == 0 || errno != EBUSY)
		err_sys("mq_notify returned %d, expected EBUSY", rc);
		/* now unregister, then reregister */
	Mymq_notify(mqd, NULL);
	Mymq_notify(mqd, &sigev);
		/* verify we cannot register twice */
	if ( (rc = mymq_notify(mqd, &sigev)) == 0 || errno != EBUSY)
		err_sys("mq_notify returned %d, expected EBUSY", rc);

		/* make certain child cannot register if we are registered */
	if ( (childpid = Fork()) == 0) {
		if ( (rc = mymq_notify(mqd, &sigev)) == 0 || errno != EBUSY)
			err_sys("mq_notify returned %d, expected EBUSY", rc);
		exit(0);
	}
	Waitpid(childpid, NULL, 0);

		/* send a message and verify SIGUSR1 is delivered */
	sigusr1 = 0;
	Mymq_send(mqd, msg5, 5, 5);
	sleep(1);
	if (sigusr1 != 1)
		err_quit("sigusr1 = %d, expected 1", sigusr1);
	if ( (rc = Mymq_receive(mqd, msg, info.mq_msgsize, &prio)) != 5)
		err_quit("mq_receive returned %d, expected 5", rc);
	if (prio != 5)
		err_quit("mq_receive returned prio %d, expected 5", prio);

		/* send another and make certain another signal is not sent */
	Mymq_send(mqd, msg2, 2, 2);
	sleep(1);
	if (sigusr1 != 1)
		err_quit("sigusr1 = %d, expected 1", sigusr1);
	if ( (rc = Mymq_receive(mqd, msg, info.mq_msgsize, &prio)) != 2)
		err_quit("mq_receive returned %d, expected 2", rc);
	if (prio != 2)
		err_quit("mq_receive returned prio %d, expected 2", prio);

		/* reregister */
	Mymq_notify(mqd, &sigev);
	if ( (childpid = Fork()) == 0) {
			/* child calls mq_receive, which prevents notification */
		if ( (rc = Mymq_receive(mqd, msg, info.mq_msgsize, &prio)) != 6)
			err_quit("mq_receive returned %d, expected 6", rc);
		if (prio != 6)
			err_quit("mq_receive returned prio %d, expected 6", prio);
		exit(0);
	}
	sleep(2);		/* let child block in mq_receive() */
	Mymq_send(mqd, msg6, 6, 6);
	Waitpid(childpid, NULL, 0);
	if (sigusr1 != 1)
		err_quit("sigusr1 = %d, expected 1", sigusr1);

		/* make certain parent can send messages to child, and vice versa */
	if ( (childpid = Fork()) == 0) {
		sleep(2);		/* let parent send two messages */
		if ( (rc = Mymq_receive(mqd, msg, info.mq_msgsize, &prio)) != 3)
			err_quit("mq_receive returned %d, expected 3", rc);
		if (prio != 3)
			err_quit("mq_receive returned prio %d, expected 3", prio);
		if ( (rc = Mymq_receive(mqd, msg, info.mq_msgsize, &prio)) != 1)
			err_quit("mq_receive returned %d, expected 1", rc);
		if (prio != 1)
			err_quit("mq_receive returned prio %d, expected 1", prio);
		exit(0);
	}
	Mymq_send(mqd, msg1, 1, 1);
	Mymq_send(mqd, msg3, 3, 3);
	Waitpid(childpid, NULL, 0);
	Mymq_getattr(mqd, &info);
	if (info.mq_maxmsg != 4 || info.mq_msgsize != 7 ||
		info.mq_flags != 0 || info.mq_curmsgs != 0)
		err_quit("8: maxmsg = %ld, msgsize = %ld, flags = %ld, curmsgs = %ld\n",
		   		 info.mq_maxmsg, info.mq_msgsize,
				 info.mq_flags, info.mq_curmsgs);

	if ( (childpid = Fork()) == 0) {
		Mymq_send(mqd, msg3, 3, 3);
		Mymq_send(mqd, msg5, 5, 5);
		Mymq_send(mqd, msg1, 1, 1);
		exit(0);
	}
	sleep(2);		/* let child send 3 messages */
	if ( (rc = Mymq_receive(mqd, msg, info.mq_msgsize, &prio)) != 5)
		err_quit("mq_receive returned %d, expected 5", rc);
	if (prio != 5)
		err_quit("mq_receive returned prio %d, expected 5", prio);
	if ( (rc = Mymq_receive(mqd, msg, info.mq_msgsize, &prio)) != 3)
		err_quit("mq_receive returned %d, expected 3", rc);
	if (prio != 3)
		err_quit("mq_receive returned prio %d, expected 3", prio);
	if ( (rc = Mymq_receive(mqd, msg, info.mq_msgsize, &prio)) != 1)
		err_quit("mq_receive returned %d, expected 1", rc);
	if (prio != 1)
		err_quit("mq_receive returned prio %d, expected 1", prio);
	Waitpid(childpid, NULL, 0);
	Mymq_getattr(mqd, &info);
	if (info.mq_maxmsg != 4 || info.mq_msgsize != 7 ||
		info.mq_flags != 0 || info.mq_curmsgs != 0)
		err_quit("9: maxmsg = %ld, msgsize = %ld, flags = %ld, curmsgs = %ld\n",
		   		 info.mq_maxmsg, info.mq_msgsize,
				 info.mq_flags, info.mq_curmsgs);

	printf("done\n");
	exit(0);
}

static void
sig_usr1(int signo)
{
	sigusr1++;
	return;
}

static void
sig_alrm(int signo)
{
	printf("SIGALRM caught\n");
	return;
}
