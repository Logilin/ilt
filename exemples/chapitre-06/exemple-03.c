#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>

#include <native/task.h>
#include <native/mutex.h>
#include <native/timer.h>
#include <rtdk.h>

static RT_MUTEX  mutex;

#define NB_COMMUTATIONS_MAX  1000
static int nb_commutations = 0;
static unsigned long long int avant_commutation;
static unsigned long long int apres_commutation;
static unsigned long long int durees_commutations[NB_COMMUTATIONS_MAX];


void thread_2 (void * unused)
{
	rt_task_sleep(5000000UL); // 5 ms

	while (nb_commutations < NB_COMMUTATIONS_MAX) {
		rt_mutex_acquire(& mutex, TM_INFINITE);
		apres_commutation = rt_timer_read();
		durees_commutations[nb_commutations] = apres_commutation - avant_commutation;
		nb_commutations ++;
		rt_mutex_release(& mutex);
		rt_task_yield();
	}
}


void thread_1 (void * unused)
{
	rt_mutex_acquire(& mutex, TM_INFINITE);

	while (nb_commutations < NB_COMMUTATIONS_MAX) {
		rt_task_sleep(10000000UL); // 10 ms
		avant_commutation = rt_timer_read();
		rt_mutex_release(& mutex);
		rt_task_yield();
		rt_mutex_acquire(& mutex, TM_INFINITE);
	}
	rt_mutex_release(& mutex);
}

int main(void)
{	
	int i;
	int err;
	RT_TASK task[2];
	
	mlockall(MCL_CURRENT|MCL_FUTURE);
	rt_print_auto_init(1);

	if ((err = rt_mutex_create(& mutex, "Exemple-01")) != 0) {
		fprintf(stderr, "rt_mutex_create:%s\n",
		         strerror(-err));
		exit(EXIT_FAILURE);
	}

	if ((err = rt_task_spawn(& task[0], NULL, 0, 99,
	                  T_JOINABLE, thread_1, NULL) != 0)) {
		fprintf(stderr, "rt_task_spawn:%s\n",
		        strerror(-err));
		exit(EXIT_FAILURE);
	}

	if (rt_task_spawn(& task[1], NULL, 0, 99,
	                  T_JOINABLE, thread_2, NULL) != 0) {
		fprintf(stderr, "rt_task_spawn:%s\n",
		        strerror(-err));
		exit(EXIT_FAILURE);
	}
	rt_task_join(& task[0]);
	rt_task_join(& task[1]);
	rt_mutex_delete(& mutex);

	for (i = 0; i < NB_COMMUTATIONS_MAX; i ++)
		printf("%lld\n", durees_commutations[i]/1000);

	return EXIT_SUCCESS;
}

