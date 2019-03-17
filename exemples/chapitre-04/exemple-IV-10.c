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


#define LOOPS 500000000


int main(void)
{
	int cpu;
	cpu_set_t cpu_set;
	int i;

	for (;;) {
		for (cpu = 0; cpu < sysconf(_SC_NPROCESSORS_ONLN); cpu ++) {
			CPU_ZERO(&cpu_set);
			CPU_SET(cpu, &cpu_set);
			sched_setaffinity(0, sizeof(cpu_set), &cpu_set);
			fprintf(stderr, "[%d] CPU -> %d\n",
			                 getpid(), sched_getcpu());
			for (i = 0; i < LOOPS; i ++)
				;
		}
	}
	return EXIT_SUCCESS;
}
