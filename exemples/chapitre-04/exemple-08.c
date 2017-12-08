/****************************************************************************\
** Exemple de la formation "Temps-reel Linux et Xenomai                     **
**                                                                          **
** Christophe Blaess 2012                                                   **
** http://christophe.blaess.fr                                              **
\****************************************************************************/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/wait.h>

#define NB_PROCESSUS   4
#define NB_BOUCLES     3

int main(int argc, char * argv[])
{
	int i, j;
	sem_t * sem;
	pid_t pid_fils[NB_PROCESSUS];
	
	if (argc != 2) {
		fprintf(stderr, "usage: %s nom_semaphore\n",
		                 argv[0]);
		exit(EXIT_FAILURE);
	}
	
	// Lancement des processus fils
	for (i = 0; i < NB_PROCESSUS; i ++) {
	
		pid_fils[i] = fork();
		
		if (pid_fils[i] == 0) {
			// Processus fils
			sem = sem_open(argv[1], O_RDWR | O_CREAT, 0666, 1);
			if (sem == SEM_FAILED) {
				perror(argv[1]);
				exit(EXIT_FAILURE);
			}
			for (j = 0; j < NB_BOUCLES; j ++) {
				fprintf(stderr, "[%u] attend le semaphore\n", getpid());
				sem_wait(sem);
				fprintf(stderr, "     >> [%d] tient le semaphore\n", getpid());
				sleep(2);
				fprintf(stderr, "     << [%d] libere le semaphore\n", getpid());
				sem_post(sem);
				sleep(5);
			}
			sem_close(sem);
			exit(EXIT_SUCCESS);
		}
	}

	// Processus pere
	for (i = 0; i < NB_PROCESSUS; i ++)
		waitpid(pid_fils[i], NULL, 0);

	sem_unlink(argv[1]);
	
	return EXIT_SUCCESS;
}

