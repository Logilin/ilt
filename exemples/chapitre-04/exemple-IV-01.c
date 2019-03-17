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
#include <sys/wait.h>


int main(void)
{
	pid_t  p;

	fprintf(stderr, "[%d] Parent process.\n", getpid());

	p = fork();

	if (p == 0) {
		fprintf(stderr, "[%d] Child process. My parent is %d.\n",
		                 getpid(), getppid());
		sleep(10);
		fprintf(stderr, "[%d] I will terminate...\n",
		                 getpid());
		exit(0);
	} else {
		fprintf(stderr, "[%d] Waiting for the termination of my child %d.\n",
		                 getpid(), p);
		waitpid(p, NULL, 0);
		fprintf(stderr, "[%d] My child %d has exited.\n",
		                 getpid(), p);
		fprintf(stderr, "[%d] I will terminate...\n",
		                 getpid());
	}
	return 0;
}
