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
#include <unistd.h>


static int _Counter = 0;


void *thread_function (void *arg)
{
	long number = (long) arg;

	while (1) {
		fprintf(stderr, "Thread %ld, counter = %d\n",
		        number, _Counter);
		sleep(1);
	}
	return NULL;
}


#define THREADS 5


int main(void)
{
	long i;
	pthread_t thr[THREADS];

	for (i = 0; i < THREADS; i ++)
		pthread_create(&(thr[i]), NULL, thread_function, (void *)i);

	while (1) {
		fprintf(stderr, "Main : counter = %d\n", _Counter ++);
		sleep(1);
	}
	return 0;
}
