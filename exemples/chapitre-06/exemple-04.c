#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>

#include <native/task.h>
#include <native/mutex.h>
#include <native/timer.h>
#include <rtdk.h>

static RT_MUTEX  mutex;


void thread_1(void *unused);
void thread_2(void * unused);
void thread_3(void * unused);


void thread_1(void *unused)
{
	int err;
	RT_TASK task_2, task_3;

	rt_fprintf(stderr, "T1 demarre\n");

	rt_fprintf(stderr, "T1 demande le mutex\n");
	rt_mutex_acquire(& mutex, TM_INFINITE);
	rt_fprintf(stderr, "T1 tient le mutex\n");

	rt_fprintf(stderr, "T1 demarre T3\n");
	if ((err = rt_task_spawn(& task_3, NULL, 0, 30,
	                  T_JOINABLE, thread_3, NULL) != 0)) {
		fprintf(stderr, "rt_task_spawn:%s\n",
		        strerror(-err));
		exit(EXIT_FAILURE);
	}

	rt_fprintf(stderr, "T1 demarre T2\n");
	if ((err = rt_task_spawn(& task_2, NULL, 0, 20,
	                  T_JOINABLE, thread_2, NULL) != 0)) {
		fprintf(stderr, "rt_task_spawn:%s\n",
		        strerror(-err));
		exit(EXIT_FAILURE);
	}
	
	rt_fprintf(stderr, "T1 lache le mutex\n");
	rt_mutex_release(& mutex);

	rt_fprintf(stderr, "T1 attend T2 et T3\n");
	rt_task_join(& task_2);
	rt_task_join(& task_3);

	rt_fprintf(stderr, "T1 se termine\n");
}


void thread_2(void * unused)
{	
	rt_fprintf(stderr, "    T2 demarre\n");
	rt_fprintf(stderr, "    T2 travaille\n");
	rt_timer_spin(3000000000LLU);
	rt_fprintf(stderr, "    T2 se termine\n");
}


void thread_3(void * unused)
{
	rt_fprintf(stderr, "        T3 demarre\n");

	rt_fprintf(stderr, "        T3 demande le mutex\n");
	rt_mutex_acquire(& mutex, TM_INFINITE);
	rt_fprintf(stderr, "        T3 tient le mutex\n");

	rt_fprintf(stderr, "        T3 travaille\n");
	rt_timer_spin(3000000000LLU);

	rt_fprintf(stderr, "        T3 lache le mutex\n");
	rt_mutex_release(& mutex);
	rt_fprintf(stderr, "        T3 se termine\n");
}



int main(int argc, char * argv [])
{
	int err;
	RT_TASK task;

	mlockall(MCL_CURRENT|MCL_FUTURE);
	rt_print_auto_init(1);

	if ((err = rt_mutex_create(& mutex, "Exemple-02")) != 0) {
		fprintf(stderr, "rt_mutex_create:%s\n",
		         strerror(-err));
		exit(EXIT_FAILURE);
	}

	if ((err = rt_task_spawn(& task, NULL, 0, 10,
	                  T_JOINABLE, thread_1, NULL) != 0)) {
		fprintf(stderr, "rt_task_spawn:%s\n",
		        strerror(-err));
		exit(EXIT_FAILURE);
	}
	
	rt_task_join(& task);
	rt_mutex_delete(& mutex);
	return 0;
}
