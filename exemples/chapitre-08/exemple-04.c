/****************************************************************************\
** Exemple de la formation "Temps-reel Linux et Xenomai"                    **
**                                                                          **
** Christophe Blaess 2010-2018                                              **
** http://christophe.blaess.fr                                              **
** Licence GPLv2                                                            **
\****************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>

#include <alchemy/task.h>
#include <alchemy/mutex.h>
#include <alchemy/timer.h>


static RT_MUTEX  _Mutex;

void thread_function_1(void *unused);
void thread_function_2(void *unused);
void thread_function_3(void *unused);


void thread_function_1(void *unused)
{
	int err;
	RT_TASK task_2, task_3;


	(void) unused;

	rt_fprintf(stderr, "T1 starts.\n");

	rt_fprintf(stderr, "T1 waits for the mutex.\n");
	rt_mutex_acquire(&_Mutex, TM_INFINITE);
	rt_fprintf(stderr, "T1 holds the mutex.\n");

	rt_fprintf(stderr, "        T3 wakes up.\n");
	if ((err = rt_task_spawn(& task_3, NULL, 0, 30,
	                  T_JOINABLE, thread_function_3, NULL) != 0)) {
		fprintf(stderr, "rt_task_spawn:%s\n",
		        strerror(-err));
		exit(EXIT_FAILURE);
	}

	rt_fprintf(stderr, "    T2 wakes up.\n");
	if ((err = rt_task_spawn(& task_2, NULL, 0, 20,
	                  T_JOINABLE, thread_function_2, NULL) != 0)) {
		fprintf(stderr, "rt_task_spawn:%s\n",
		        strerror(-err));
		exit(EXIT_FAILURE);
	}

	rt_fprintf(stderr, "T1 releases the mutex.\n");
	rt_mutex_release(&_Mutex);

	rt_task_join(& task_2);
	rt_task_join(& task_3);

	rt_fprintf(stderr, "T1 terminates.\n");
}


void thread_function_2(void *unused)
{
	(void) unused;

	rt_fprintf(stderr, "    T2 starts.\n");
	rt_fprintf(stderr, "    T2 works.\n");
	rt_timer_spin(3000000000LLU);
	rt_fprintf(stderr, "    T2 terminates.\n");
}


void thread_function_3(void *unused)
{
	(void) unused;

	rt_fprintf(stderr, "        T3 starts\n");

	rt_fprintf(stderr, "        T3 waits for the mutex.\n");
	rt_mutex_acquire(&_Mutex, TM_INFINITE);
	rt_fprintf(stderr, "        T3 holds the mutex\n");

	rt_fprintf(stderr, "        T3 works.\n");
	rt_timer_spin(3000000000LLU);

	rt_fprintf(stderr, "        T3 releases the mutex.\n");
	rt_mutex_release(&_Mutex);
	rt_fprintf(stderr, "        T3 terminates.\n");
}



int main(int argc, char * argv [])
{
	int err;
	RT_TASK task;

	mlockall(MCL_CURRENT|MCL_FUTURE);

	err = rt_mutex_create(&_Mutex, "PIP_test");
	if (err != 0) {
		fprintf(stderr, "rt_mutex_create:%s\n",
		         strerror(-err));
		exit(EXIT_FAILURE);
	}

	err = rt_task_spawn(&task, NULL, 0, 10,
	                  T_JOINABLE, thread_function_1, NULL);
	if (err != 0) {
		fprintf(stderr, "rt_task_spawn:%s\n",
		        strerror(-err));
		exit(EXIT_FAILURE);
	}

	rt_task_join(&task);
	rt_mutex_delete(&_Mutex);

	return 0;
}
