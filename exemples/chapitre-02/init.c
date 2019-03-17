
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(void)
{
	FILE * fp;
	time_t tm;

	fp = fopen("/dev/ttyAMA0", "w");
	while (1) {
		time(& tm);
		fprintf(fp, "%s", ctime(& tm));
		fflush(fp);
		sleep(1);	
	}
	return EXIT_FAILURE;
}

