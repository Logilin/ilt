/****************************************************************************\
** Exemple de la formation "Temps-reel sous Linux"                          **
**                                                                          **
** Christophe Blaess 2010-2025                                              **
** http://christophe.blaess.fr                                              **
** Licence GPLv2                                                            **
\****************************************************************************/

#define _GNU_SOURCE

#include <pthread.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


unsigned long Loops = 0;


void *thread_function(void *arg)
{
	long int cpu = (long int) arg;
	cpu_set_t cpu_set;
	struct sched_param param;
	unsigned long int i;

	CPU_ZERO(& cpu_set);
	CPU_SET(cpu, & cpu_set);
	if (pthread_setaffinity_np(pthread_self(), sizeof(cpu_set), &cpu_set) != 0) {
		perror("pthread_setaffinity_np");
		exit(EXIT_FAILURE);
	}

	param.sched_priority = 99;
	if (pthread_setschedparam(pthread_self(), SCHED_FIFO, &param) != 0) {
		perror("pthread_setschedparam");
		exit(EXIT_FAILURE);
	}

	fprintf(stderr, "Thread sur CPU %ld va demarrer...\n", cpu);
	sleep(1);
	for (i = 0; i < Loops; i++)
		;
	return NULL;
}


int main(int argc, char *argv[])
{
	long int cpu;
	pthread_t thr;

	if ((argc != 2)
	 || (sscanf(argv[1], "%lu", &Loops) != 1)) {
		fprintf(stderr, "Usage: %s <loops>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	for (cpu = 0; cpu < sysconf(_SC_NPROCESSORS_ONLN); cpu ++)
		pthread_create(&thr, NULL, thread_function, (void *) cpu);

        pthread_exit(NULL);
}
