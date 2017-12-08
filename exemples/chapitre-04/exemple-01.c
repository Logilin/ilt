/****************************************************************************\
** Exemple de la formation "Temps-reel Linux et Xenomai                     **
**                                                                          **
** Christophe Blaess 2012                                                   **
** http://christophe.blaess.fr                                              **
\****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
	pid_t  p;
	fprintf(stderr, "[%d] Je suis le processus pere\n", getpid());
	p = fork();
	if (p == 0) {
		fprintf(stderr, "[%d] Je suis le processus fils, mon pere est %d\n",
		                 getpid(), getppid());
		sleep(10);
		fprintf(stderr, "[%d] Je vais me terminer...\n", 
		                 getpid());
		exit(0);
	} else {
		fprintf(stderr, "[%d] Je vais attendre la fin de mon fils %d\n",
		                 getpid(), p);
		waitpid(p, NULL, 0);
		fprintf(stderr, "[%d] Mon fils %d s'est termine\n",
		                 getpid(), p);
		fprintf(stderr, "[%d] Je vais me terminer...\n",
		                 getpid());
	}
	return 0;
}

