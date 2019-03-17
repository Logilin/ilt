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


void hello_world_function (void * unused)
{
	for (;;) {
		rt_printf("Hello from Xenomai Realtime Space\n");
		rt_task_sleep(1000000000LL); // 1 second.
	}
}


int main(void)
{
	int err;
	RT_TASK task;

	mlockall(MCL_CURRENT|MCL_FUTURE);

	if ((err = rt_task_spawn(& task, "Hello_01",
	                         0, 99, T_JOINABLE,
	                         hello_world_function, NULL)) != 0) {
		fprintf(stderr, "rt_task_spawn: %s\n", strerror(-err));
		exit(EXIT_FAILURE);
	}

	rt_task_join(& task);

	return 0;
}
