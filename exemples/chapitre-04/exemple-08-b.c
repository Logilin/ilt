	#include <fcntl.h>
	#include <pthread.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <unistd.h>
	#include <sys/mman.h>

	typedef struct {

		int value;
		pthread_mutex_t mutex;

	} counter_t;


int main(int argc, char *argv[])
{
	int creation;
	int fd; 
	counter_t *counter;


	if (argc != 2) {
		fprintf(stderr, "usage: %s <shm-name>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	creation = 0;
	fd = shm_open(argv[1], O_RDWR, 0666);
	if (fd < 0) {
		fd = shm_open(argv[1], O_CREAT | O_RDWR, 0666);
		if (fd < 0) {
			perror(argv[1]);
			exit(EXIT_FAILURE);
		}
		creation = 1;
	}

	if (creation)
		ftruncate(fd, sizeof(counter_t));

	counter = mmap(NULL, sizeof(counter_t), PROT_READ|PROT_WRITE,
	               MAP_SHARED, fd, 0);
	if (counter == MAP_FAILED) {
		perror("mmap");
		exit(EXIT_FAILURE);
	}

	if (creation) {
		pthread_mutexattr_t mutexattr;

		pthread_mutexattr_init(&mutexattr);
		pthread_mutexattr_setpshared(&mutexattr, PTHREAD_PROCESS_SHARED);
		pthread_mutex_init(&(counter->mutex), &mutexattr);
	}

	while(1) {
		pthread_mutex_lock(&(counter->mutex));
		counter->value ++;
		fprintf(stdout, "%d\n", counter->value);
		pthread_mutex_unlock(&(counter->mutex));
		sleep(1);
	}

	return 0;
}
