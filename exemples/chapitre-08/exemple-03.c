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

#define MAX_SWITCHES  1000
static int _Switches = 0;

static unsigned long long int _Before_switch;
static unsigned long long int _After_switch;;
static unsigned long long int _Switch_durations[MAX_SWITCHES];


void thread_function_1 (void * unused)
{
	(void) unused;

	do {
	    rt_mutex_acquire(&_Mutex, TM_INFINITE);
	    rt_task_sleep(10000000UL); // 10 ms
	    _Before_switch = rt_timer_read();
	    rt_mutex_release(&_Mutex);
	    rt_task_yield(); 
	}
	while (_Switches < MAX_SWITCHES);
}


void thread_function_2 (void * unused)
{
	(void) unused;

	rt_task_sleep(5000000UL); // 5 ms

	while (_Switches < MAX_SWITCHES) {
		rt_mutex_acquire(&_Mutex, TM_INFINITE);
		_After_switch = rt_timer_read();
		_Switch_durations[_Switches] = _After_switch - _Before_switch;
		_Switches ++;
		rt_mutex_release(&_Mutex);
		rt_task_yield();
	}
}



int main(void)
{
	int i;
	int err;
	RT_TASK task[2];

	mlockall(MCL_CURRENT|MCL_FUTURE);

	err = rt_mutex_create(&_Mutex, "Switch_MTX");
	if (err != 0) {
		fprintf(stderr, "rt_mutex_create:%s\n",
		         strerror(-err));
		exit(EXIT_FAILURE);
	}

	err = rt_task_spawn(&task[0], NULL, 0, 99,
	                  T_JOINABLE, thread_function_1, NULL);
	if (err != 0) {
		fprintf(stderr, "rt_task_spawn:%s\n",
		        strerror(-err));
		exit(EXIT_FAILURE);
	}

	err = rt_task_spawn(&task[1], NULL, 0, 99,
	                  T_JOINABLE, thread_function_2, NULL);
	if (err != 0) {
		fprintf(stderr, "rt_task_spawn:%s\n",
		        strerror(-err));
		exit(EXIT_FAILURE);
	}
	rt_task_join(&task[0]);
	rt_task_join(&task[1]);
	rt_mutex_delete(&_Mutex);

	for (i = 0; i < MAX_SWITCHES; i ++)
		printf("%6lld us\n", _Switch_durations[i] / 1000);

	return EXIT_SUCCESS;
}
