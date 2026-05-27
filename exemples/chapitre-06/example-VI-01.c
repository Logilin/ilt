/****************************************************************************\
** Exemple de la formation "Temps-reel sous Linux"                          **
**                                                                          **
** Christophe Blaess 2010-2026                                              **
** http://christophe.blaess.fr                                              **
** Licence GPLv2                                                            **
\****************************************************************************/

#define _GNU_SOURCE

#include <sched.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/resource.h>


int _End_of_loop = 0;


void sigalrm_handler(int unused)
{
	(void) unused;

	_End_of_loop = 1;
}


int main(int argc, char *argv[])
{
	int priority;
	struct sched_param param;
	long long int counter;

	if ((argc != 2)
	 || (sscanf(argv[1], "%d", &priority) != 1)) {
		fprintf(stderr, "usage: %s priority\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	struct rlimit limit = { RLIM_INFINITY, RLIM_INFINITY };
	prlimit(0, RLIMIT_RTTIME, &limit, NULL);

	param.sched_priority = priority;
	if (sched_setscheduler(0, SCHED_RR, &param) != 0) {
		perror("setscheduler");
		exit(EXIT_FAILURE);
	}

	alarm(4);
	sleep(1);
	signal(SIGALRM, sigalrm_handler);

	counter = 0;
	while (! _End_of_loop) {
		counter ++;
	}
	fprintf(stdout, "[%d] Priority = %d, counter = %lld\n",
	                 getpid(), priority, counter);

	return EXIT_SUCCESS;
}
