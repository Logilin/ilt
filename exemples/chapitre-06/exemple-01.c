#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>

#include <rtdk.h>
#include <native/task.h>


void fonction_hello_world (void * unused)
{
	while (1) {
		rt_printf("Hello from Xenomai Realtime Space\n");
		rt_task_sleep(1000000000LL); // 1 milliard ns = 1 s.
	}
}


int main(void)
{
	int err;
	RT_TASK task;
	
	mlockall(MCL_CURRENT|MCL_FUTURE);
	rt_print_auto_init(1);
	
	if ((err = rt_task_spawn(& task, "Hello_01",
	                         0, 99, T_JOINABLE,
	                         fonction_hello_world, NULL)) != 0) {
		fprintf(stderr, "rt_task_spawn: %s\n", strerror(-err));
		exit(EXIT_FAILURE);
	}
	rt_task_join(& task);
	return 0;
}

