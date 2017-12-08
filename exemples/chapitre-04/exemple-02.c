/****************************************************************************\
** Exemple de la formation "Temps-reel Linux et Xenomai                     **
**                                                                          **
** Christophe Blaess 2012                                                   **
** http://christophe.blaess.fr                                              **
\****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define LG_LIGNE 80

int main(void)
{
	char ligne [LG_LIGNE];
	while (1) {
		// Afficher le prompt
		fprintf(stderr, "--> ");
		
		// Lire une ligne de commande
		if (fgets(ligne, LG_LIGNE, stdin) == NULL)
			break;
		
		// Retirer le retour-chariot final
		ligne[strlen(ligne)-1] = '\0';
		
		switch(fork()) {
			case -1: // Erreur dans fork
				perror("fork");
				exit(EXIT_FAILURE);
				
			case 0: // Processus Fils
				execlp(ligne, ligne, NULL);
				// Si on arrive ici, execlp a echoue
				perror(ligne);
				exit(EXIT_FAILURE);
				
			default: // Processus pere
				// Attendre la fin du fils
				waitpid(-1, NULL, 0);
				break;
		}
	}
	return EXIT_SUCCESS;
}

