#define _XOPEN_SOURCE 500
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

pthread_mutex_t mutex;
pthread_t thr1, thr2, thr3;
pthread_attr_t attr1, attr2, attr3;

void * fonction_2(void * unused)
{	
	int i, j;
	fprintf(stderr, "    T2 demarre\n");
	fprintf(stderr, "    T2 travaille...\n");
	for (i = 0; i < 100000; i ++)
		for (j = 0; j < 10000; j ++)
			;
	fprintf(stderr, "    T2 se termine\n");
	return NULL;
}

void * fonction_3(void * unused)
{
	int i, j;
	fprintf(stderr, "        T3 demarre\n");
	fprintf(stderr, "        T3 demande le mutex\n");
	pthread_mutex_lock(& mutex);
	fprintf(stderr, "        T3 tient le mutex\n");
	fprintf(stderr, "        T3 travaille...\n");
	for (i = 0; i < 100000; i ++)
		for (j = 0; j < 10000; j ++)
			;
	fprintf(stderr, "        T3 lache le mutex\n");
	pthread_mutex_unlock(& mutex);
	fprintf(stderr, "        T3 se termine\n");
	return NULL;
}

void * fonction_1(void *unused)
{
	fprintf(stderr, "T1 demarre\n");

	fprintf(stderr, "T1 demande le mutex\n");
	pthread_mutex_lock(& mutex);
	fprintf(stderr, "T1 tient le mutex\n");

	fprintf(stderr, "reveil de  T3\n");
	pthread_create(& thr3, &attr3, fonction_3, NULL);

	fprintf(stderr, "reveil de T2\n");
	pthread_create(& thr2, &attr2, fonction_2, NULL);
	
	fprintf(stderr, "T1 lache le mutex\n");
	pthread_mutex_unlock(& mutex);
	fprintf(stderr, "T1 se termine\n");
	return NULL;
}


int main(int argc, char * argv [])
{
	struct sched_param param;
	pthread_mutexattr_t attr;

	pthread_mutexattr_init(& attr);
	pthread_mutexattr_setprotocol (& attr, PTHREAD_PRIO_INHERIT);
	pthread_mutex_init(& mutex, &attr);

	pthread_attr_init(& attr1);
	pthread_attr_init(& attr2);
	pthread_attr_init(& attr3);
	pthread_attr_setschedpolicy(& attr1, SCHED_FIFO);
	pthread_attr_setschedpolicy(& attr2, SCHED_FIFO);
	pthread_attr_setschedpolicy(& attr3, SCHED_FIFO);
	param.sched_priority = 10;
	pthread_attr_setschedparam(& attr1, & param);
	param.sched_priority = 20;
	pthread_attr_setschedparam(& attr2, & param);
	param.sched_priority = 30;
	pthread_attr_setschedparam(& attr3, & param);
	pthread_attr_setinheritsched(& attr1, PTHREAD_EXPLICIT_SCHED);
	pthread_attr_setinheritsched(& attr2, PTHREAD_EXPLICIT_SCHED);
	pthread_attr_setinheritsched(& attr3, PTHREAD_EXPLICIT_SCHED);
	
	if ((errno = pthread_create(& thr1, & attr1, fonction_1, NULL)) != 0) {
		perror("pthread_create");
		exit(EXIT_FAILURE);
	}
	pthread_join(thr1, NULL);
	return 0;
}
