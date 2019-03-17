/****************************************************************************\
** Exemple de la formation "Temps-reel Linux et Xenomai"                    **
**                                                                          **
** Christophe Blaess 2010-2018                                              **
** http://christophe.blaess.fr                                              **
** Licence GPLv2                                                            **
\****************************************************************************/


#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>


int main(int argc, char * argv[])
{
	int fd;
	int * counter;

	if (argc != 2) {
		fprintf(stderr, "usage: %s shm_name\n", argv[0]);
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
	counter = mmap(NULL, sizeof(int), PROT_READ|PROT_WRITE,
	                MAP_SHARED, fd, 0);
	// Utilisation
	for (;;) {
		fprintf(stderr, "counter = %d\n", *counter);
		sleep(1);
		(*counter) ++;
	}
	return 0;
}
