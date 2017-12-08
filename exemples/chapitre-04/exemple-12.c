/****************************************************************************\
** Exemple de la formation "Temps-reel Linux et Xenomai                     **
**                                                                          **
** Christophe Blaess 2012                                                   **
** http://christophe.blaess.fr                                              **
\****************************************************************************/

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int fin_traitement = 0;

void handler_alarm(int unused)
{
	fin_traitement = 1;
}

int main(int argc, char * argv[])
{
	long long int compteur = 0;
	int valeur_nice;

	if ((argc != 2) || (sscanf(argv[1], "%d", & valeur_nice) != 1)) {
		fprintf(stderr, "usage: %s valeur_nice\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	nice(valeur_nice);

	signal(SIGALRM, handler_alarm);
	alarm(5);
	while (! fin_traitement) {
		compteur ++;
	}
	fprintf(stdout, "[%d] (nice = %d) compteur = %lld\n", getpid(), valeur_nice, compteur);
	return 0;
}

