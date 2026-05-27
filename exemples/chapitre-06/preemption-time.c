/****************************************************************************\
** Exemple de la formation "Temps-reel sous Linux"                          **
**                                                                          **
** Christophe Blaess 2010-2026                                              **
** http://christophe.blaess.fr                                              **
** Licence GPLv2                                                            **
\****************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>


int main(void)
{
	long int start;
	long long int duration;
	long long int max_duration = 0;
	struct timeval previous;
	struct timeval now;

	struct rlimit limit = { RLIM_INFINITY, RLIM_INFINITY };
	prlimit(0, RLIMIT_RTTIME, &limit, NULL);

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
