/****************************************************************************\
** Exemple de la formation "Temps-reel Linux et Xenomai                     **
**                                                                          **
** Christophe Blaess 2012-2018                                              **
** http://christophe.blaess.fr                                              **
** Licence GPLv2                                                            **
\****************************************************************************/


#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/wait.h>


#define PROCESSES   4
#define LOOPS       3


int main(int argc, char * argv[])
{
	int i, j;
	sem_t * sem;
	pid_t pid[PROCESSES];

	if (argc != 2) {
		fprintf(stderr, "usage: %s semaphore\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	// Lancement des processus.
	for (i = 0; i < PROCESSES; i ++) {

		pid[i] = fork();

		if (pid[i] == 0) {
			sem = sem_open(argv[1], O_RDWR | O_CREAT, 0666, 1);
			if (sem == SEM_FAILED) {
				perror(argv[1]);
				exit(EXIT_FAILURE);
			}
			for (j = 0; j < LOOPS; j ++) {
				fprintf(stderr, "[%u] wait for semaphore\n", getpid());
				sem_wait(sem);
				fprintf(stderr, "     >> [%d] hold the semaphore\n", getpid());
				sleep(2);
				fprintf(stderr, "     << [%d] release the semaphore\n", getpid());
				sem_post(sem);
				sleep(5);
			}
			sem_close(sem);
			exit(EXIT_SUCCESS);
		}
	}

	// Attente de fin des processus enfants.
	for (i = 0; i < PROCESSES; i ++)
		waitpid(pid[i], NULL, 0);

	sem_unlink(argv[1]);

	return EXIT_SUCCESS;
}
