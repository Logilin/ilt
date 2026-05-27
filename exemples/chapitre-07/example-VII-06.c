/****************************************************************************\
** Exemple de la formation "Temps-reel sous Linux"                          **
**                                                                          **
** Christophe Blaess 2010-2026                                              **
** http://christophe.blaess.fr                                              **
** Licence GPLv2                                                            **
\****************************************************************************/

#define _GNU_SOURCE

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/resource.h>


pthread_mutex_t _Mutex = PTHREAD_MUTEX_INITIALIZER;


void *thread_function(void *arg)
{
	for (;;) {
		pthread_mutex_lock(&_Mutex);
		fprintf(stderr, "[%ld] holds the mutex\n", (long int) arg);
		sleep(1);
		pthread_mutex_unlock(&_Mutex);
	}
	return NULL;
}

int main(int argc, char *argv[])
{
	pthread_t  thr[2];
	pthread_attr_t  attr;
	struct sched_param  param;

	struct rlimit limit = { RLIM_INFINITY, RLIM_INFINITY };
	prlimit(0, RLIMIT_RTTIME, &limit, NULL);

	pthread_mutex_lock(&_Mutex);

	pthread_attr_init(&attr);
	pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
	pthread_attr_setschedpolicy(&attr, SCHED_RR);
	param.sched_priority = 20;
	pthread_attr_setschedparam(& attr, &param);

	if (((errno = pthread_create(&(thr[0]), &attr, thread_function, (void *) 0)) != 0)
	 || ((errno = pthread_create(&(thr[1]), &attr, thread_function, (void *) 1)) != 0)) {
		perror("pthread_create");
		exit(EXIT_FAILURE);
	}

	pthread_mutex_unlock(&_Mutex);
	pthread_exit(NULL);
}
