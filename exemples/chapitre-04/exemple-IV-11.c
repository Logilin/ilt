/****************************************************************************\
** Exemple de la formation "Temps-reel Linux et Xenomai"                    **
**                                                                          **
** Christophe Blaess 2010-2018                                              **
** http://christophe.blaess.fr                                              **
** Licence GPLv2                                                            **
\****************************************************************************/


#define _GNU_SOURCE


#include <errno.h>
#include <pthread.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


#define LOOPS 500000000


void * thread_function(void *);

int main(void)
{
	long            i;
	pthread_t *     threads;
	pthread_attr_t  attr;
	cpu_set_t       cpu_set;
	int             nb_cpus;

	nb_cpus = sysconf(_SC_NPROCESSORS_ONLN);
	threads = calloc(nb_cpus, sizeof(pthread_t));
	if (threads == NULL) {
		perror("calloc");
		exit(EXIT_FAILURE);
	}

	for (i = 0; i < nb_cpus; i ++) {
		CPU_ZERO(&cpu_set);
		CPU_SET(i, &cpu_set);
		pthread_attr_init(&attr);
		pthread_attr_setaffinity_np(&attr, sizeof(cpu_set_t), &cpu_set);
		if ((errno = pthread_create(&(threads[i]), &attr, thread_function, (void *) i)) != 0) {
			perror("pthread_create");
			exit(EXIT_FAILURE);
		}
	}
	for (i = 0; i < nb_cpus; i ++) {
		pthread_join(threads[i], NULL);
	}
	return EXIT_SUCCESS;
}


void * thread_function(void * arg)
{
	int i;
	long num = (long) arg;

	for (;;) {
		for (i = 0 ; i < LOOPS; i ++)
			;
		fprintf(stderr, "[%ld] CPU -> %d\n", num, sched_getcpu());
		sleep(1);
	}
	return NULL;
}
