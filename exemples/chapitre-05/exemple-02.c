
#define _GNU_SOURCE  // sched_getcpu() est une extension GNU
#include <pthread.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/time.h>


void * fonction_thread(void * arg)
{
	long int cpu = (long int) arg;
	cpu_set_t cpu_set;
	struct sched_param param;
	int i, j;

	CPU_ZERO(& cpu_set);
	CPU_SET(cpu, & cpu_set);
	if (pthread_setaffinity_np(pthread_self(), sizeof(cpu_set), & cpu_set) != 0) {
		perror("pthread_setaffinity_np");
		exit(EXIT_FAILURE);
	}

	param.sched_priority = 99;
	if (pthread_setschedparam(pthread_self(), SCHED_FIFO, & param) != 0) {
		perror("pthread_setschedparam");
		exit(EXIT_FAILURE);
	}

	fprintf(stderr, "Thread sur CPU %ld va demarrer...\n", cpu);
	sleep(1);

	for (j = 0; j < 10; j ++)
		for (i = 0; i < 400000000; i ++)
			;
	return NULL;
}


int main(void)
{
	long int cpu;
	pthread_t thr;

	for (cpu = 0; cpu < sysconf(_SC_NPROCESSORS_ONLN); cpu ++)
		pthread_create (& thr, NULL, fonction_thread, (void *) cpu);
        pthread_exit(NULL);
}

