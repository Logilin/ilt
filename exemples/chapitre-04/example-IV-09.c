/****************************************************************************\
** Exemple de la formation "Temps-reel sous Linux"                          **
**                                                                          **
** Christophe Blaess 2010-2023                                              **
** http://christophe.blaess.fr                                              **
** Licence GPLv2                                                            **
\****************************************************************************/

#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>

struct mutexed_counter {
	int              counter;
	pthread_mutex_t  mutex;
};



int main(int argc, char * argv[])
{
	int fd;
	struct mutexed_counter *cnt;
	pthread_mutexattr_t attr;

	if (argc != 2) {
		fprintf(stderr, "usage: %s shm_name\n", argv[0]);
		exit(1);
	}

	if ((fd = shm_open(argv[1], O_RDWR, 0666)) < 0) {
		if ((fd = shm_open(argv[1], O_CREAT | O_RDWR, 0666)) < 0) {
			perror(argv[1]);
			exit(EXIT_FAILURE);
		}
		ftruncate(fd, sizeof(struct mutexed_counter));
		cnt = mmap(NULL, sizeof(struct mutexed_counter), PROT_READ|PROT_WRITE,
		                MAP_SHARED, fd, 0);
		cnt->counter = 0;
		pthread_mutexattr_init(&attr);
		pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);
		pthread_mutex_init(&(cnt->mutex), &attr);
	} else {
		cnt = mmap(NULL, sizeof(struct mutexed_counter), PROT_READ|PROT_WRITE,
		                MAP_SHARED, fd, 0);
	}

	for (;;) {
		pthread_mutex_lock(&(cnt->mutex));
		fprintf(stderr, "counter = %d\n", ++(cnt->counter));
		pthread_mutex_unlock(&(cnt->mutex));
		sleep(1);
	}
	return 0;
}
