/****************************************************************************\
** Exemple de la formation "Temps-reel sous Linux et Xenomai"               **
**                                                                          **
** Christophe Blaess 2010-2020                                              **
** http://christophe.blaess.fr                                              **
** Licence GPLv2                                                            **
\****************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>


#define LINE_LENGTH 80


int main(void)
{
	char line [LINE_LENGTH];

	while (1) {
		fprintf(stderr, "--> ");

		if (fgets(line, LINE_LENGTH, stdin) == NULL)
			break;

		line[strlen(line)-1] = '\0';

		switch(fork()) {
			case -1:
				perror("fork");
				exit(EXIT_FAILURE);

			case 0:
				execlp(line, line, NULL);
				perror(line);
				exit(EXIT_FAILURE);

			default:
				waitpid(-1, NULL, 0);
				break;
		}
	}
	return EXIT_SUCCESS;
}
