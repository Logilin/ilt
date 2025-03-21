/****************************************************************************\
** Exemple de la formation "Temps-reel sous Linux"                          **
**                                                                          **
** Christophe Blaess 2010-2025                                              **
** http://christophe.blaess.fr                                              **
** Licence GPLv2                                                            **
\****************************************************************************/


#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


static int _End_of_loop = 0;


void sigalrm_handler(int unused)
{
	_End_of_loop = 1;
}


int main(int argc, char * argv[])
{
	long long int counter = 0;
	int nice_value;

	if ((argc != 2)
	 || (sscanf(argv[1], "%d", &nice_value) != 1)) {
		fprintf(stderr, "usage: %s nice_value\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	if ((nice_value < 0) && (geteuid() != 0)) {
		fprintf(stderr, "%s: must be root for negative nice value.\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	nice(nice_value);

	signal(SIGALRM, sigalrm_handler);
	alarm(5);

	while (! _End_of_loop) {
		counter ++;
	}

	fprintf(stdout, "[%d] (nice =%+3d) counter = %10lld\n", getpid(), nice_value, counter);
	sleep(1);
	return 0;
}

