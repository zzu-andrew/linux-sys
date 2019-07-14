#include	"mesg.h"

void
server(int readfd, int writefd)
{
	FILE	*fp;
	ssize_t	n;
	struct mymesg	mesg;

		/* 4read pathname from IPC channel */
	mesg.mesg_type = 1;
	if ( (n = Mesg_recv(readfd, &mesg)) == 0)
		err_quit("pathname missing");
	mesg.mesg_data[n] = '\0';	/* null terminate pathname */

	if ( (fp = fopen(mesg.mesg_data, "r")) == NULL) {
			/* 4error: must tell client */
		snprintf(mesg.mesg_data + n, sizeof(mesg.mesg_data) - n,
				 ": can't open, %s\n", strerror(errno));
		mesg.mesg_len = strlen(mesg.mesg_data);
		Mesg_send(writefd, &mesg);

	} else {
			/* 4fopen succeeded: copy file to IPC channel */
		while (Fgets(mesg.mesg_data, MAXMESGDATA, fp) != NULL) {
			mesg.mesg_len = strlen(mesg.mesg_data);
			Mesg_send(writefd, &mesg);
		}
		Fclose(fp);
	}

		/* 4send a 0-length message to signify the end */
	mesg.mesg_len = 0;
	Mesg_send(writefd, &mesg);
}
