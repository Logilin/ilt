/****************************************************************************\
** Exemple de la formation "Temps-reel Linux et Xenomai"                    **
**                                                                          **
** Christophe Blaess 2010-2018                                              **
** http://christophe.blaess.fr                                              **
** Licence GPLv2                                                            **
\****************************************************************************/


#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>


#define THREADS  4
#define BASE_PRIORITY 10

pthread_mutex_t _Mutex = PTHREAD_MUTEX_INITIALIZER;


void * thread_function(void *arg)
{
	pthread_mutex_lock(&_Mutex);
	fprintf(stderr, "[%ld] Holds the mutex\n", (long int) arg);
	pthread_mutex_unlock(&_Mutex);
	return NULL;
}


int main(int argc, char * argv [])
{
	long int i;
	pthread_t  thr[THREADS];
	pthread_attr_t  attr;
	struct sched_param  param;

	pthread_mutex_lock(&_Mutex);

	pthread_attr_init(& attr);
	pthread_attr_setinheritsched(& attr, PTHREAD_EXPLICIT_SCHED);
	pthread_attr_setschedpolicy(& attr, SCHED_FIFO);

	for (i = 0; i < THREADS; i++) {
		param.sched_priority = BASE_PRIORITY + i;
		pthread_attr_setschedparam(&attr, &param);
		if ((errno = pthread_create(&(thr[i]), &attr, thread_function, (void *)i)) != 0) {
			perror("pthread_create");
			exit(EXIT_FAILURE);
		}
	}
	pthread_mutex_unlock(&_Mutex);
	pthread_exit(NULL);
}
