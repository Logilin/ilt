/****************************************************************************\
** Exemple de la formation "Temps-reel sous Linux"                          **
**                                                                          **
** Christophe Blaess 2010-2025                                              **
** http://christophe.blaess.fr                                              **
** Licence GPLv2                                                            **
\****************************************************************************/

#define _GNU_SOURCE  // sched_getcpu()

#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

unsigned long Loops = 0;

int main(int argc, char *argv[])
{
	int cpu;
	cpu_set_t cpu_set;
	unsigned long int i;

	if ((argc != 2)
	 || (sscanf(argv[1], "%lu", &Loops) != 1)) {
		fprintf(stderr, "Usage: %s <loops>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	for (;;) {
		for (cpu = 0; cpu < sysconf(_SC_NPROCESSORS_ONLN); cpu ++) {
			CPU_ZERO(&cpu_set);
			CPU_SET(cpu, &cpu_set);
			sched_setaffinity(0, sizeof(cpu_set), &cpu_set);
			fprintf(stderr, "[%d] CPU -> %d\n",
			                 getpid(), sched_getcpu());
			for (i = 0; i < Loops; i ++)
				;
		}
	}
	return EXIT_SUCCESS;
}
