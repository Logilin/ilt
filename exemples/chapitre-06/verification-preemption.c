/****************************************************************************\
** Exemple de la formation "Temps-reel Linux et Xenomai"                    **
**                                                                          **
** Christophe Blaess 2010-2018                                              **
** http://christophe.blaess.fr                                              **
** Licence GPLv2                                                            **
\****************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>


int main(void)
{
	long int start;
	long long int duration;
	long long int max_duration = 0;
	struct timeval previous;
	struct timeval now;

	gettimeofday (&now, NULL);
	start = now.tv_sec;

	do {
		previous = now;

		gettimeofday(&now, NULL);
		duration  = now.tv_sec - previous.tv_sec;
		duration *= 1000000;
		duration += now.tv_usec - previous.tv_usec;
		if (duration > max_duration)
			max_duration = duration;

	} while ((now.tv_sec - start) < 10);

	fprintf(stdout, "Max preemption = %lld us\n", max_duration);

	return 0;
}
