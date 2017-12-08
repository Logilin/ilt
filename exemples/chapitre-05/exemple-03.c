
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define NB_ECHANTILLONS 50

int main (void)
{
	int i;
	struct timespec ts[NB_ECHANTILLONS];
	for (i = 0; i < NB_ECHANTILLONS; i++)
		clock_gettime(CLOCK_REALTIME, & (ts[i]));
	for (i = 0; i < NB_ECHANTILLONS; i++)
		fprintf(stdout, "%ld.%09ld\n", ts[i].tv_sec, ts[i].tv_nsec);
	return EXIT_SUCCESS;
}
