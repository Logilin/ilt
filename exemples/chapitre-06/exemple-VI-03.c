/****************************************************************************\
** Exemple de la formation "Temps-reel Linux et Xenomai"                    **
**                                                                          **
** Christophe Blaess 2010-2018                                              **
** http://christophe.blaess.fr                                              **
** Licence GPLv2                                                            **
\****************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


#define LOOPS 50


int main (void)
{
	int i;
	struct timespec ts[LOOPS];

	for (i = 0; i < LOOPS; i++)
		clock_gettime(CLOCK_REALTIME, & (ts[i]));

	for (i = 0; i < LOOPS; i++)
		fprintf(stdout, "%ld.%09ld\n", ts[i].tv_sec, ts[i].tv_nsec);

	return EXIT_SUCCESS;
}
