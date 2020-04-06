#include	"mesg.h"

void
server(int readid, int writeid)
{
	FILE	*fp;
	char	*ptr;
	ssize_t	n;
	struct mymesg	mesg;
	void	sig_chld(int);

	Signal(SIGCHLD, sig_chld);

	for ( ; ; ) {
			/* 4read pathname from our well-known queue */
		mesg.mesg_type = 1;
		if ( (n = Mesg_recv(readid, &mesg)) == 0) {
			err_msg("pathname missing");
			continue;
		}
		mesg.mesg_data[n] = '\0';	/* null terminate pathname */

		if ( (ptr = strchr(mesg.mesg_data, ' ')) == NULL) {
			err_msg("bogus request: %s", mesg.mesg_data);
			continue;
		}
		*ptr++ = 0;			/* null terminate msgid, ptr = pathname */
		writeid = atoi(mesg.mesg_data);

		if (Fork() == 0) {		/* child */
			if ( (fp = fopen(ptr, "r")) == NULL) {
					/* 4error: must tell client */
				snprintf(mesg.mesg_data + n, sizeof(mesg.mesg_data) - n,
						 ": can't open, %s\n", strerror(errno));
				mesg.mesg_len = strlen(ptr);
				memmove(mesg.mesg_data, ptr, mesg.mesg_len);
				Mesg_send(writeid, &mesg);
		
			} else {
					/* 4fopen succeeded: copy file to client's queue */
				while (Fgets(mesg.mesg_data, MAXMESGDATA, fp) != NULL) {
					mesg.mesg_len = strlen(mesg.mesg_data);
					Mesg_send(writeid, &mesg);
				}
				Fclose(fp);
			}
		
				/* 4send a 0-length message to signify the end */
			mesg.mesg_len = 0;
			Mesg_send(writeid, &mesg);
			exit(0);		/* child terminates */
		}
		/* parent just loops around */
	}
}
