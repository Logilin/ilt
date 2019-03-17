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

#define BUFFER_SIZE  1024

void thread_function_2(void *unused);

void thread_function_1(void *unused)
{
	char *query = "Hello from thread 1";
	RT_TASK_MCB mcb_query;

	char reply[BUFFER_SIZE];
	RT_TASK_MCB mcb_reply;

	int err;
	RT_TASK task_2;

	(void) unused;

	rt_fprintf(stderr, "T1 starts.\n");

	err = rt_task_spawn(& task_2, NULL, 0, 20,
	                  T_JOINABLE, thread_function_2, NULL);
	if (err  != 0) {
		fprintf(stderr, "rt_task_spawn:%s\n",
		        strerror(-err));
		exit(EXIT_FAILURE);
	}

	rt_printf("T1 fills the query.\n");
	memset(&mcb_query, 0, sizeof(mcb_query));
	mcb_query.data = query;
	mcb_query.size = strlen(query) + 1;

	mcb_reply.data = reply;
	mcb_reply.size = BUFFER_SIZE;

	rt_printf("T1 sends the message.\n");
	rt_task_send(&task_2, &mcb_query, &mcb_reply, TM_INFINITE);

	rt_printf("T1 got a reply: %s\n", mcb_reply.data);

	rt_printf("T1 terminates.\n");
}



void thread_function_2(void *unused)
{
	RT_TASK_MCB mcb_query;
	RT_TASK_MCB mcb_reply;
	int id;
	char *reply = "Hello from thread 2";

	mcb_query.data = malloc(BUFFER_SIZE);
	mcb_query.size = BUFFER_SIZE;

	(void) unused;

	rt_printf("    T2 starts.\n");
	rt_printf("    T2 waits for a query.\n");

	id = rt_task_receive(&mcb_query, TM_INFINITE);
	if (id < 0) {
		rt_printf("rt_task_receive error: %s\n", strerror(-id));
		exit(EXIT_FAILURE);
	}
	rt_printf("    T2 got a query: %s\n", mcb_query.data);

	rt_printf("    T2 prepare a reply.\n");
	memset(&mcb_reply, 0, sizeof(mcb_reply));
	mcb_reply.data = reply;
	mcb_reply.size = strlen(reply) + 1;

	rt_printf("    T2 prepare answers.\n");
	rt_task_reply(id, &mcb_reply);

	rt_printf("    T2 terminates.\n");
}


int main(int argc, char * argv [])
{
	int err;
	RT_TASK task;

	mlockall(MCL_CURRENT|MCL_FUTURE);

	err = rt_task_spawn(&task, NULL, 0, 10,
	                  T_JOINABLE, thread_function_1, NULL);
	if (err != 0) {
		fprintf(stderr, "rt_task_spawn:%s\n",
		        strerror(-err));
		exit(EXIT_FAILURE);
	}

	rt_task_join(&task);

	return 0;
}
