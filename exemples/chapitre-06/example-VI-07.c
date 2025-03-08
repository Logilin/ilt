/****************************************************************************\
** Exemple de la formation "Temps-reel sous Linux"                          **
**                                                                          **
** Christophe Blaess 2010-2025                                              **
** http://christophe.blaess.fr                                              **
** Licence GPLv2                                                            **
\****************************************************************************/


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


unsigned long Loops = 0;


void *thread_function (void *num)
{
	unsigned long int i;
	time_t start, end;

	start = time(NULL);
	for (i = 0; i < Loops; i ++)
		;
	end = time(NULL);
	fprintf(stderr, "%ld -> %ld\n", start, end);
	return NULL;
}


#define NB 4

int main(int argc, char *argv[])
{
	pthread_t thr[NB];
	pthread_attr_t attr;
	struct sched_param param;
	int i;

	if ((argc != 2)
	 || (sscanf(argv[1], "%lu", &Loops) != 1)) {
		fprintf(stderr, "Usage: %s <loops>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	pthread_attr_init(& attr);
	pthread_attr_setschedpolicy(& attr, SCHED_RR);
	param.sched_priority = 10;
	pthread_attr_setschedparam(& attr, & param);
	pthread_attr_setinheritsched(& attr, PTHREAD_EXPLICIT_SCHED);

	for (i =  0; i < NB; i ++) {
		if (pthread_create(&(thr[i]), & attr, thread_function, NULL) != 0) {
			fprintf(stderr, "pthread_create error %d\n", i);
			exit(1);
		}
	}
	pthread_exit(0);
}
