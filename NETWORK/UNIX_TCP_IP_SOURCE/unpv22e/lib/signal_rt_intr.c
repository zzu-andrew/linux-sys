/* include signal_rt_intr */
#include	"unpipc.h"

Sigfunc_rt *
signal_rt_intr(int signo, Sigfunc_rt *func)
{
	struct sigaction	act, oact;

	act.sa_sigaction = func;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;		/* must specify this for realtime */
#ifdef	SA_INTERRUPT
	act.sa_flags |= SA_INTERRUPT;	/* SunOS 4.x */
#endif
	if (sigaction(signo, &act, &oact) < 0)
		return((Sigfunc_rt *) SIG_ERR);
	return(oact.sa_sigaction);
}
/* end signal_rt_intr */

Sigfunc_rt *
Signal_rt_intr(int signo, Sigfunc_rt *func)
{
	Sigfunc_rt	*sigfunc;

	if ( (sigfunc = signal_rt_intr(signo, func)) == (Sigfunc_rt *) SIG_ERR)
		err_sys("signal_rt_intr error");
	return(sigfunc);
}
