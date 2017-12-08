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
#include <sys/mman.h>

int main(int argc, char * argv[])
{
	int fd;
	int * compteur;
	if (argc != 2) {
		fprintf(stderr, "usage: %s nom_shm\n", argv[0]);
		exit(1);
	}
	// Ouverture (ou creation) d'une zone de memoire partagee
	if ((fd = shm_open(argv[1], O_CREAT | O_RDWR, 0666)) < 0) {
		perror(argv[1]);
		exit(1);
	}
	// Dimensionnement (seulement a la creation initiale)
	ftruncate(fd, sizeof(int));
	// Projection en memoire virtuelle
	compteur = mmap(NULL, sizeof(int), PROT_READ|PROT_WRITE,
	                MAP_SHARED, fd, 0);
	// Utilisation
	while (1) {
		fprintf(stderr, "compteur = %d\n", * compteur);
		sleep(1);
		(* compteur) ++;
	}
	return 0;
}

