/****************************************************************************\
** Exemple de la formation "Temps-reel Linux et Xenomai                     **
**                                                                          **
** Christophe Blaess 2012                                                   **
** http://christophe.blaess.fr                                              **
\****************************************************************************/

#define _GNU_SOURCE  // sched_getcpu() est une extension GNU
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(void)
{
	int i;
	int cpu;
	cpu_set_t cpu_set;

	while (1) {
		for (cpu = 0; cpu < sysconf(_SC_NPROCESSORS_ONLN); cpu ++) {
			CPU_ZERO(& cpu_set);
			CPU_SET(cpu, & cpu_set);
			sched_setaffinity(0, sizeof(cpu_set), & cpu_set);
			fprintf(stderr, "[%d] je suis sur le CPU %d\n",
			                 getpid(), sched_getcpu());
			for (i = 0; i < 100000000; i ++)
				;
		}
	}
	return EXIT_SUCCESS;
}

