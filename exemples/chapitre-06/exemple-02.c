#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>

#include <native/task.h>
#include <native/timer.h>
#include <rtdk.h>

void fonction_periodique (void * arg)
{
	RTIME precedent = 0; 
	RTIME heure = 0;
	RTIME periode;
	RTIME duree;
	RTIME min = -1;
	RTIME max = 0;
	RTIME sum = 0;
	RTIME max_max = 0;
	long nb_mesures;
	long mesure = 0;
	periode = * (RTIME *) arg;
	nb_mesures = 2000000 / periode; // deux secondes;
	
	periode = periode * 1000; // en ns
	rt_task_set_periodic(NULL, TM_NOW, periode);
	while(1) {
		rt_task_wait_period(NULL);
		heure = rt_timer_read();
		// ignorer le premier declenchement
		if (precedent != 0) { 
			duree = heure - precedent;
			sum = sum + duree;
			if ((min < 0) || (duree < min))
				min = duree;
			if (max < duree) {
				max = duree;
				if (max > max_max)
					max_max = max;
			}
			mesure ++;
			if (mesure == nb_mesures) {
				fprintf(stdout, "Min.=%lld, Moy.=%lld, Max.=%lld, Max.Max.=%lld\n",
					min/1000, sum/nb_mesures/1000, max/1000, max_max/1000);
				mesure = 0;
				min = -1;
				max = 0;
				sum = 0;
			}
		}
		precedent = heure;
	}
}



int main(int argc, char * argv[])
{	
	RT_TASK task;
	RTIME periode;
	int err;
	int fd;
	int zero = 0;
	fd = open("/dev/cpu_dma_latency", O_WRONLY);
	if (fd >= 0) {
		write(fd, & zero, sizeof(zero));
		// ne pas fermer le fichier avant la fin du processus
	} 
	if ((argc != 2) || (sscanf(argv[1], "%llu", & periode) != 1)) {
		fprintf(stderr, "usage: %s periode_en_us\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	
	mlockall(MCL_CURRENT|MCL_FUTURE);
	rt_print_auto_init(1);

	if ((err = rt_task_spawn(& task, NULL, 0, 99,
	        T_JOINABLE, fonction_periodique, & periode)) != 0) {
		fprintf(stderr, "rt_task_spaw: %s\n", strerror(-err));
		exit(EXIT_FAILURE);
	}

	rt_task_join(& task);
	return 0;
}


