#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void * fonction(void * arg)
{	
	pthread_mutex_lock(& mutex);
	fprintf(stderr, "[%ld] J'ai le mutex\n", (long int) arg);
	pthread_mutex_unlock(& mutex);
	return NULL;
}

int main(int argc, char * argv [])
{
	long int prio;
	pthread_t  thr;
	pthread_attr_t  attr;
	struct sched_param  param;

	pthread_mutex_lock(& mutex);

	pthread_attr_init(& attr);
	pthread_attr_setinheritsched(& attr, PTHREAD_EXPLICIT_SCHED);
	pthread_attr_setschedpolicy(& attr, SCHED_FIFO);
	for (prio = 11; prio < 15; prio ++) {
		param.sched_priority = prio;
		pthread_attr_setschedparam(& attr, & param);
		if ((errno = pthread_create(& thr, & attr, fonction, (void *) prio)) != 0) {
			perror("pthread_create");
			exit(EXIT_FAILURE);
		}
	}
	pthread_mutex_unlock(& mutex);
	pthread_exit(NULL);
}
