/****************************************************************************\
** Exemple de la formation "Temps-reel Linux et Xenomai"                    **
**                                                                          **
** Christophe Blaess 2010-2018                                              **
** http://christophe.blaess.fr                                              **
** Licence GPLv2                                                            **
\****************************************************************************/


#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>

#include <alchemy/task.h>
#include <alchemy/timer.h>


void periodic_task (void * arg)
{
	RTIME previous = 0;
	RTIME now = 0;
	RTIME period;
	RTIME duration;
	RTIME min = -1;
	RTIME max = 0;
	RTIME sum = 0;
	RTIME max_max = 0;

	long nb_measure_per_cycle;
	long measure = 0;

	period = * (RTIME *) arg;
	nb_measure_per_cycle = 2000000 / period; // 2 seconds.

	period = period * 1000; // us->ns
	rt_task_set_periodic(NULL, TM_NOW, period);

	for (;;) {
		rt_task_wait_period(NULL);
		now = rt_timer_read();

		if (previous != 0) {
			duration = now - previous;
			sum = sum + duration;
			if ((min < 0) || (duration < min))
				min = duration;
			if (max < duration) {
				max = duration;
				if (max > max_max)
					max_max = max;
			}
			measure ++;
			if (measure == nb_measure_per_cycle) {
				rt_printf("Min.=%lld, Moy.=%lld, Max.=%lld, Max.Max.=%lld\n",
					min/1000, sum/nb_measure_per_cycle/1000, max/1000, max_max/1000);
				measure = 0;
				min = -1;
				max = 0;
				sum = 0;
			}
		}
		previous = now;
	}
}




int main(int argc, char * argv[])
{
	RT_TASK task;
	RTIME period;
	int err;
	int fd;
	int zero = 0;

	fd = open("/dev/cpu_dma_latency", O_WRONLY);
	if (fd >= 0) {
		write(fd, &zero, sizeof(zero));
		// don't close the file before process termination.
	}

	if ((argc != 2)
	 || (sscanf(argv[1], "%llu", &period) != 1)) {
		fprintf(stderr, "usage: %s period_us\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	mlockall(MCL_CURRENT|MCL_FUTURE);

	err = rt_task_spawn(& task, NULL, 0, 99,
	        T_JOINABLE, periodic_task, & period);
	if (err != 0) {
		fprintf(stderr, "rt_task_spaw: %s\n", strerror(-err));
		exit(EXIT_FAILURE);
	}

	rt_task_join(& task);

	return 0;
}
