#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>



static int nb_mesures = 0;

void handler_alarm(int unused)
{
	static long long int min;
	static long long int max;
	static long long int sum;
	static long long int max_max = 0;
	static struct timespec precedent;
	static int mesure = -1;

	long long int duree;
	struct timespec ts;

	if (mesure == -1) {
		min = -1;
		max = 0;
		sum = 0;
		clock_gettime(CLOCK_REALTIME, & precedent);
		mesure ++;
		return;
	} 

	clock_gettime(CLOCK_REALTIME, & ts);
	duree  = ts.tv_sec - precedent.tv_sec;
	duree *= 1000000000; // en nanosecondes
	duree += ts.tv_nsec - precedent.tv_nsec;
	duree /= 1000; // en microsecondes
	if ((min == -1) || (duree < min))
		min = duree;
	if (duree > max) {
		max = duree;
		if (max_max < max)
			max_max = duree;
	}
	sum += duree;
	precedent = ts;
	mesure ++;
	if (mesure == nb_mesures) {
		fprintf(stdout, "Min.= %lld, Moy.=%lld, Max.=%lld,  Max.Max.=%lld\n",
			min, sum / nb_mesures, max, max_max);
		mesure = -1;
	}
	
}


int main (int argc, char * argv[])
{
	long int periode;
	timer_t tmr;
	struct sigevent notification;
	struct itimerspec itimer;


	if ((argc != 2) || (sscanf(argv[1], "%ld", & periode) != 1)) {
		fprintf(stderr, "usage: %s periode_us\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	if ((periode <= 0) || (periode > 2000000)) {
		fprintf(stderr, "%s: La periode doit etre dans [1, 2000000]\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	nb_mesures = 2000000 / periode; // Un affichage toutes les deux secondes environ

	signal(SIGALRM, handler_alarm);
	notification.sigev_notify = SIGEV_SIGNAL;
	notification.sigev_signo  = SIGALRM;
	if (timer_create(CLOCK_REALTIME, & notification, & tmr) != 0) {
		perror("timer_create");
		exit(EXIT_FAILURE);
	}

	itimer.it_value.tv_sec  = itimer.it_interval.tv_sec  = periode / 1000000;  // en secondes
	itimer.it_value.tv_nsec = itimer.it_interval.tv_nsec = (periode % 1000000) * 1000; // en nanosecondes
	if (timer_settime(tmr, 0, & itimer, NULL) != 0) {
		perror("timer_settime");
		exit(EXIT_FAILURE);
	}

	while(1)
		pause();

	return EXIT_SUCCESS;
}
