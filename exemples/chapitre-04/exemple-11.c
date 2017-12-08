/****************************************************************************\
** Exemple de la formation "Temps-reel Linux et Xenomai                     **
**                                                                          **
** Christophe Blaess 2012                                                   **
** http://christophe.blaess.fr                                              **
\****************************************************************************/

#define _GNU_SOURCE  // sched_getcpu() est une extension GNU
#include <errno.h>
#include <pthread.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void * fonction_thread(void *);

int main(void)
{
	long            i;
	pthread_t *     threads;
	pthread_attr_t  attr;
	int             nb_cpus = sysconf(_SC_NPROCESSORS_ONLN);
	cpu_set_t       cpu_set;


	threads = calloc(nb_cpus, sizeof(pthread_t));
	if (threads == NULL) {
		perror("calloc");
		exit(EXIT_FAILURE);
	}

	for (i = 0; i < nb_cpus; i ++) {
		CPU_ZERO(& cpu_set);
		CPU_SET(i, & cpu_set);
		pthread_attr_init(& attr);
		pthread_attr_setaffinity_np(& attr, sizeof(cpu_set_t), & cpu_set);
		if ((errno = pthread_create(& (threads[i]), & attr, fonction_thread, (void *) i)) != 0) {
			perror("pthread_create");
			exit(EXIT_FAILURE);
		}
	}
	for (i = 0; i < nb_cpus; i ++) {
		pthread_join(threads[i], NULL);
	}
	return EXIT_SUCCESS;
}

void * fonction_thread(void * arg)
{
	int i;
	long numero = (long) arg;

	while (1) {
		for (i = 0 ; i < 1000000000; i ++)
				;
		fprintf(stderr, "[%ld] sur CPU %d\n", numero, sched_getcpu());
		sleep(1);
	}
	return NULL;
}
