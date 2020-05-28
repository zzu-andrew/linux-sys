#include "Xt.h"

void main (int argc, char * argv [])
{	void * shell = new(XtApplicationShell(), & argc, argv);
	void * lineOut = new(XLineOut(), shell, 0, "hello, world");

	puto(lineOut, stdout);
	mainLoop(shell);
}
