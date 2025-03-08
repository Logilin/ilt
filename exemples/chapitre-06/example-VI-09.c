/****************************************************************************\
** Exemple de la formation "Temps-reel sous Linux"                          **
**                                                                          **
** Christophe Blaess 2010-2025                                              **
** http://christophe.blaess.fr                                              **
** Licence GPLv2                                                            **
\****************************************************************************/

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>


pthread_mutex_t _Mutex;
pthread_t _Thread_1, _Thread_2, _Thread_3;
pthread_attr_t _Attr_1, _Attr_2, _Attr_3;


unsigned long Loops = 0;


void *thread_function_3(void *unused)
{
	unsigned long int i;

	fprintf(stderr, "        T3 starts.\n");
	fprintf(stderr, "        T3 waits for the mutex.\n");
	pthread_mutex_lock(&_Mutex);
	fprintf(stderr, "        T3 holds the mutex.\n");
	fprintf(stderr, "        T3 works...\n");
	for (i = 0; i < Loops; i ++)
		;
	fprintf(stderr, "        T3 releases the mutex.\n");
	pthread_mutex_unlock(&_Mutex);
	fprintf(stderr, "        T3 terminates.\n");

	return NULL;
}


void *thread_function_2(void *unused)
{
	unsigned long int i;

	fprintf(stderr, "    T2 starts.\n");
	fprintf(stderr, "    T2 works...\n");
	for (i = 0; i < Loops; i ++)
		;
	fprintf(stderr, "    T2 terminates.\n");
	return NULL;
}



void *thread_function_1(void *unused)
{
	fprintf(stderr, "T1 starts.\n");

	fprintf(stderr, "T1 waits for the mutex.\n");
	pthread_mutex_lock(&_Mutex);
	fprintf(stderr, "T1 holds the mutex.\n");

	fprintf(stderr, "        T3 wakes up.\n");
	pthread_create(&_Thread_3, &_Attr_3, thread_function_3, NULL);

	fprintf(stderr, "    T2 wakes up.\n");
	pthread_create(&_Thread_2, &_Attr_2, thread_function_2, NULL);

	fprintf(stderr, "T1 releases the mutex.\n");
	pthread_mutex_unlock(&_Mutex);
	fprintf(stderr, "T1 terminates.\n");
	return NULL;
}



int main(int argc, char *argv[])
{
	struct sched_param param;

	if ((argc != 2)
	 || (sscanf(argv[1], "%lu", &Loops) != 1)) {
		fprintf(stderr, "Usage: %s <loops>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	pthread_mutex_init(&_Mutex, NULL);
	pthread_attr_init(&_Attr_1);
	pthread_attr_init(&_Attr_2);
	pthread_attr_init(&_Attr_3);
	pthread_attr_setschedpolicy(&_Attr_1, SCHED_FIFO);
	pthread_attr_setschedpolicy(&_Attr_2, SCHED_FIFO);
	pthread_attr_setschedpolicy(&_Attr_3, SCHED_FIFO);
	param.sched_priority = 10;
	pthread_attr_setschedparam(&_Attr_1, & param);
	param.sched_priority = 20;
	pthread_attr_setschedparam(&_Attr_2, & param);
	param.sched_priority = 30;
	pthread_attr_setschedparam(&_Attr_3, & param);
	pthread_attr_setinheritsched(&_Attr_1, PTHREAD_EXPLICIT_SCHED);
	pthread_attr_setinheritsched(&_Attr_2, PTHREAD_EXPLICIT_SCHED);
	pthread_attr_setinheritsched(&_Attr_3, PTHREAD_EXPLICIT_SCHED);

	if ((errno = pthread_create(&_Thread_1, &_Attr_1, thread_function_1, NULL)) != 0) {
		perror("pthread_create");
		exit(EXIT_FAILURE);
	}
	pthread_join(_Thread_1, NULL);

	return 0;
}
