/****************************************************************************\
** Exemple de la formation "Temps-reel Linux et Xenomai"                    **
**                                                                          **
** Christophe Blaess 2010-2018                                              **
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
		// Afficher le prompt
		fprintf(stderr, "--> ");

		// Lire une ligne de commande
		if (fgets(line, LINE_LENGTH, stdin) == NULL)
			break;

		// Retirer le retour-chariot final
		line[strlen(line)-1] = '\0';

		switch(fork()) {
			case -1: // Erreur dans fork
				perror("fork");
				exit(EXIT_FAILURE);

			case 0: // Processus enfant : lancer la commande.
				execlp(line, line, NULL);
				// Si on arrive ici, execlp a echoue.
				perror(line);
				exit(EXIT_FAILURE);

			default: // Processus parent : attendre la fin du processu enfant.
				waitpid(-1, NULL, 0);
				break;
		}
	}
	return EXIT_SUCCESS;
}
