#include	"unpipc.h"

int
main(int argc, char **argv)
{
	size_t	n;
	char	buff[MAXLINE], command[MAXLINE];
	FILE	*fp;

		/* 4read pathname */
	Fgets(buff, MAXLINE, stdin);
	n = strlen(buff);		/* fgets() guarantees null byte at end */
	if (buff[n-1] == '\n')
		n--;				/* delete newline from fgets() */

	snprintf(command, sizeof(command), "cat %s", buff);
	fp = Popen(command, "r");

		/* 4copy from pipe to standard output */
	while (Fgets(buff, MAXLINE, fp) != NULL)
		Fputs(buff, stdout);

	Pclose(fp);
	exit(0);
}
