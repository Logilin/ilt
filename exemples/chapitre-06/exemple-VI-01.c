/****************************************************************************\
** Exemple de la formation "Temps-reel Linux et Xenomai"                    **
**                                                                          **
** Christophe Blaess 2010-2018                                              **
** http://christophe.blaess.fr                                              **
** Licence GPLv2                                                            **
\****************************************************************************/


#include <sched.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int _End_of_loop = 0;


void sigalrm_handler(int unused)
{
	(void) unused;

	_End_of_loop = 1;
}


int main(int argc, char * argv[])
{
	int priority;
	struct sched_param param;
	long long int counter;

	if ((argc != 2)
	 || (sscanf(argv[1], "%d", &priority) != 1)) {
		fprintf(stderr, "usage: %s priority\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	param.sched_priority = priority;
	if (sched_setscheduler(0, SCHED_RR, &param) != 0) {
		perror("setscheduler");
		exit(EXIT_FAILURE);
	}

	sleep(1);
	signal(SIGALRM, sigalrm_handler);
	alarm(4);

	counter = 0;
	while (! _End_of_loop) {
		counter ++;
	}
	fprintf(stdout, "[%d] Priority = %d, counter = %lld\n",
	                 getpid(), priority, counter);

	return EXIT_SUCCESS;
}
