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


#define LOOPS  1000000000

struct mtx_counter {
	int              counter;
	pthread_mutex_t  mutex;
};


int main(int argc, char * argv[])
{
	int fd;
	struct mtx_counter *cnt;
	pthread_mutexattr_t attr;
	char buffer[16];

	if (argc != 2) {
		fprintf(stderr, "usage: %s shm_name\n", argv[0]);
		exit(1);
	}

	if ((fd = shm_open(argv[1], O_RDWR, 0666)) >=  0) {

		cnt = mmap(NULL, sizeof(struct mtx_counter), PROT_READ|PROT_WRITE,
		                MAP_SHARED, fd, 0);
	} else {

		if ((fd = shm_open(argv[1], O_CREAT | O_RDWR, 0666)) < 0) {
			perror(argv[1]);
			exit(EXIT_FAILURE);
		}
		ftruncate(fd, sizeof(struct mtx_counter));
		cnt = mmap(NULL, sizeof(struct mtx_counter), PROT_READ|PROT_WRITE,
		                MAP_SHARED, fd, 0);
		cnt->counter = 0;
		pthread_mutexattr_init(&attr);
		pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);
		pthread_mutex_init(&(cnt->mutex), &attr);
	}

	fprintf(stderr, "Press `Enter` to start counting... ");
	fgets(buffer, 15, stdin);

        for (unsigned i = 0; i < LOOPS; i++){
                pthread_mutex_lock(&(cnt->mutex));
                cnt->counter ++;
                pthread_mutex_unlock(&(cnt->mutex));
        }

	fprintf(stderr, "Press `Enter` to display result... ");
	fgets(buffer, 15, stdin);

	fprintf(stdout, "counter = %d\n", cnt->counter);

	return 0;
}
