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


#define THREADS 2
#define LOOPS   1000000


static int _Counter = 0;
// pthread_mutex_t _Counter_mtx = PTHREAD_MUTEX_INITIALIZER;


void * thread_function(void * arg)
{
	int i;

	for (i = 0; i < LOOPS; i ++) {
//		pthread_mutex_lock (& _Counter_mtx);
		_Counter ++;
//		pthread_mutex_unlock (& _Counter_mtx);
	}
	return NULL;
}


int main(void)
{
	int i;
	pthread_t thr[THREADS];

	// Creer tous les threads
	for (i = 0; i < THREADS; i ++) {
		if (pthread_create(& thr[i], NULL, thread_function, NULL) != 0)
			exit(1);
	}

	// Attendre qu'ils soient tous termines
	for (i = 0; i < THREADS; i ++)
		pthread_join(thr[i], NULL);

	// Afficher l'etat du compteur
	fprintf(stdout, "Result:%d\n", _Counter);
	return 0;
}
