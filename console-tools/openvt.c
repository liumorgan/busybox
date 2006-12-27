/* vi: set sw=4 ts=4: */
/*
 *  openvt.c - open a vt to run a command.
 *
 *  busyboxed by Quy Tonthat <quy@signal3.com>
 *  hacked by Tito <farmatito@tiscali.it>
 *
 * Licensed under GPLv2 or later, see file LICENSE in this tarball for details.
 */

/* getopt not needed */

#include "busybox.h"

int openvt_main(int argc, char **argv)
{
	int fd;
	char vtname[sizeof(VC_FORMAT) + 2];


	if (argc < 3) {
		bb_show_usage();
	}
	/* check for illegal vt number: < 1 or > 63 */
	sprintf(vtname, VC_FORMAT, (int)xatoul_range(argv[1], 1, 63));

	if (fork() == 0) {
		/* leave current vt */
		if (setsid() < 0) {
			bb_perror_msg_and_die("setsid");
		}
		close(0);			/* so that new vt becomes stdin */

		/* and grab new one */
		fd = xopen(vtname, O_RDWR);

		/* Reassign stdout and sterr */
		dup2(fd, STDOUT_FILENO);
		dup2(fd, STDERR_FILENO);

		execvp(argv[2], &argv[2]);
		_exit(1);
	}
	return EXIT_SUCCESS;
}
