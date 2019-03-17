/****************************************************************************\
** Exemple de la formation "Temps-reel Linux et Xenomai"                    **
**                                                                          **
** Christophe Blaess 2010-2018                                              **
** http://christophe.blaess.fr                                              **
** Licence GPLv2                                                            **
\****************************************************************************/


#define _GNU_SOURCE  // sched_getcpu()


#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


int main(void)
{
	int cpu;
	int previous = -1;
	time_t now;
	struct tm * now_tm;

	for (;;) {
		cpu = sched_getcpu();
		if (cpu == -1) {
			perror("sched_getcpu");
			exit(EXIT_FAILURE);
		}
		if (previous == -1)
			previous = cpu;
		if (cpu != previous) {
			now = time(NULL);
			now_tm = localtime(&now);
			fprintf(stdout, "%02d:%02d:%02d migration %d -> %d\n",
			         now_tm->tm_hour, now_tm->tm_min, now_tm->tm_sec,
			         previous, cpu);
			previous = cpu;
		}
	}
	return EXIT_SUCCESS;
}
