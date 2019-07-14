/* include signal_rt */
#include	"unpipc.h"

Sigfunc_rt *
signal_rt(int signo, Sigfunc_rt *func)
{
	struct sigaction	act, oact;

	act.sa_sigaction = func;		/* must store function addr here */
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;		/* must specify this for realtime */
	if (signo == SIGALRM) {
#ifdef	SA_INTERRUPT
		act.sa_flags |= SA_INTERRUPT;	/* SunOS 4.x */
#endif
	} else {
#ifdef	SA_RESTART
		act.sa_flags |= SA_RESTART;		/* SVR4, 44BSD */
#endif
	}
	if (sigaction(signo, &act, &oact) < 0)
		return((Sigfunc_rt *) SIG_ERR);
	return(oact.sa_sigaction);
}
/* end signal_rt */

Sigfunc_rt *
Signal_rt(int signo, Sigfunc_rt *func)
{
	Sigfunc_rt	*sigfunc;

	if ( (sigfunc = signal_rt(signo, func)) == (Sigfunc_rt *) SIG_ERR)
		err_sys("signal_rt error");
	return(sigfunc);
}
