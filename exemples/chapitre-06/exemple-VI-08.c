/****************************************************************************\
** Exemple de la formation "Temps-reel Linux et Xenomai"                    **
**                                                                          **
** Christophe Blaess 2010-2018                                              **
** http://christophe.blaess.fr                                              **
** Licence GPLv2                                                            **
\****************************************************************************/


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


pthread_barrier_t _Barrier;


void * thread_function (void * unused)
{
	int i, j;
	time_t debut, fin;

	pthread_barrier_wait(&_Barrier);
	debut = time(NULL);
	for (i = 0; i < 100000; i ++)
		for (j = 0; j < 10000; j ++)
			;
	fin = time(NULL);
	fprintf(stderr, "%ld -> %ld\n", debut, fin);
	return NULL;
}


#define NB 4

int main(void)
{
	pthread_t thr[NB];
	pthread_attr_t attr;
	struct sched_param param;
	int i;

	pthread_barrier_init(&_Barrier, NULL, NB);
	pthread_attr_init(& attr);
	pthread_attr_setschedpolicy(& attr, SCHED_RR);
	param.sched_priority = 10;
	pthread_attr_setschedparam(& attr, & param);
	pthread_attr_setinheritsched(& attr, PTHREAD_EXPLICIT_SCHED);

	for (i =  0; i < NB; i ++) {
		if (pthread_create(&(thr[i]), & attr, thread_function, NULL) != 0) {
			fprintf(stderr, "pthread_create error %d\n", i);
			exit(1);
		}
	}
	pthread_exit(0);
}
