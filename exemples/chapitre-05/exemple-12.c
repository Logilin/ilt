#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void * fonction(void * arg)
{	
	while (1) {
		pthread_mutex_lock(& mutex);
		fprintf(stderr, "[%ld] J'ai le mutex\n", (long int) arg);
		sleep(1);
		pthread_mutex_unlock(& mutex);
	}
	return NULL;
}

int main(int argc, char * argv [])
{
	pthread_t  thr[2];
	pthread_attr_t  attr;
	struct sched_param  param;

	pthread_mutex_lock(& mutex);
	pthread_attr_init(& attr);
	pthread_attr_setinheritsched(& attr, PTHREAD_EXPLICIT_SCHED);
	pthread_attr_setschedpolicy(& attr, SCHED_RR);
	param.sched_priority = 20;
	pthread_attr_setschedparam(& attr, & param);
	
	if (((errno = pthread_create(& (thr[0]), & attr, fonction, (void *) 0)) != 0)
	 || ((errno = pthread_create(& (thr[1]), & attr, fonction, (void *) 1)) != 0)) {
			perror("pthread_create");
			exit(EXIT_FAILURE);
	}
	pthread_mutex_unlock(& mutex);
	pthread_exit(NULL);
}
