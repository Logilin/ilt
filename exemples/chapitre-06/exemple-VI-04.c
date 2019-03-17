/****************************************************************************\
** Exemple de la formation "Temps-reel Linux et Xenomai"                    **
**                                                                          **
** Christophe Blaess 2010-2018                                              **
** http://christophe.blaess.fr                                              **
** Licence GPLv2                                                            **
\****************************************************************************/


#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


static int _Nb_measure_per_interval = 0;


void sigalrm_handler(int unused)
{
	static long long int min;
	static long long int max;
	static long long int sum;
	static long long int max_max = 0;
	static int measure = -1;
	static struct timespec previous;
	struct timespec now;
	long long int duration;

	(void) unused;

	if (measure < 0) {
		min = -1;
		max = 0;
		sum = 0;
		clock_gettime(CLOCK_REALTIME, &previous);
		measure ++;
		return;
	}

	clock_gettime(CLOCK_REALTIME, &now);
	duration  = now.tv_sec - previous.tv_sec;
	duration *= 1000000000;
	duration += now.tv_nsec - previous.tv_nsec;
	duration /= 1000;
	if ((min == -1) || (duration < min))
		min = duration;
	if (duration > max) {
		max = duration;
		if (max_max < max)
			max_max = duration;
	}
	sum += duration;
	previous = now;
	measure ++;
	if (measure == _Nb_measure_per_interval) {
		fprintf(stdout, "Min.= %lld, Moy.=%lld, Max.=%lld,  Max.Max.=%lld\n",
			min, sum / _Nb_measure_per_interval, max, max_max);
		measure = -1;
	}
}


int main (int argc, char * argv[])
{
	long int period;
	timer_t tmr;
	struct sigevent notify;
	struct itimerspec itimer;


	if ((argc != 2) || (sscanf(argv[1], "%ld", &period) != 1)) {
		fprintf(stderr, "usage: %s period_us\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	if ((period <= 0) || (period > 2000000)) {
		fprintf(stderr, "%s: the period must be in [1, 2000000]\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	_Nb_measure_per_interval = 2000000 / period; // Un affichage toutes les deux secondes environ

	signal(SIGALRM, sigalrm_handler);
	notify.sigev_notify = SIGEV_SIGNAL;
	notify.sigev_signo  = SIGALRM;
	if (timer_create(CLOCK_REALTIME, &notify, & tmr) != 0) {
		perror("timer_create");
		exit(EXIT_FAILURE);
	}

	itimer.it_value.tv_sec  = itimer.it_interval.tv_sec  = period / 1000000;  // seconds
	itimer.it_value.tv_nsec = itimer.it_interval.tv_nsec = (period % 1000000) * 1000; // nanoseconds
	if (timer_settime(tmr, 0, & itimer, NULL) != 0) {
		perror("timer_settime");
		exit(EXIT_FAILURE);
	}

	for(;;)
		pause();

	return EXIT_SUCCESS;
}
