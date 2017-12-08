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
// pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

#define NB_THREADS 2
#define ITERATIONS 1000000

void * fonction(void * arg)
{
	int j;
	for (j = 0; j < ITERATIONS; j ++) {
//		pthread_mutex_lock (& mtx);
		compteur ++;
// 		pthread_mutex_unlock (& mtx);
	}
	return NULL;
}


int main(void)
{
	int i;
	pthread_t thr[NB_THREADS];

	// Creer tous les threads
	for (i = 0; i < NB_THREADS; i ++) {
		if (pthread_create(& thr[i], NULL, fonction, NULL) != 0)
			exit(1);
	}

	// Attendre qu'ils soient tous termines
	for (i = 0; i < NB_THREADS; i ++)
		pthread_join(thr[i], NULL);

	// Afficher l'etat du compteur
	fprintf(stdout, "Resultats :%d\n", compteur);
	return 0;
}

