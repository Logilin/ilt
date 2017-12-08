#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>



int main(void)
{
	long int debut_sec;
	long long int delai_usec;
	long long int delai_max_usec =  0;
	struct timeval precedent, actuel;

	gettimeofday (& actuel, NULL);
	debut_sec = actuel.tv_sec;

	do {
		precedent = actuel;

		gettimeofday(& actuel, NULL);
		delai_usec  = actuel.tv_sec - precedent.tv_sec;
		delai_usec *= 1000000;
		delai_usec += actuel.tv_usec - precedent.tv_usec;
		if (delai_usec > delai_max_usec)
			delai_max_usec = delai_usec;


	} while (actuel.tv_sec - debut_sec < 10);

	fprintf(stdout, "Preemption max. = %lld us\n", delai_max_usec);
	return 0;
}

