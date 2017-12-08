/****************************************************************************\
** Exemple de la formation "Temps-reel Linux et Xenomai                     **
**                                                                          **
** Christophe Blaess 2012                                                   **
** http://christophe.blaess.fr                                              **
\****************************************************************************/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int compteur = 0;

void * fonction (void * arg)
{
	long numero = (long) arg;
	while (1) {
		fprintf(stderr, "Thread %ld, compteur = %d\n",
		        numero, compteur);
		sleep(1);
	}
	return NULL;
}

#define NB_THREADS 5

int main(void)
{
	long i;
	pthread_t thr[NB_THREADS];

	for (i = 0; i < NB_THREADS; i ++)
		pthread_create(&(thr[i]), NULL, fonction, (void *)i);

	while (1) {
		fprintf(stderr, "Main : compteur = %d\n",
		                compteur ++);
		sleep(1);
	}
	return 0;
}

