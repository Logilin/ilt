/****************************************************************************\
** Exemple de la formation "Temps-reel sous Linux"                          **
**                                                                          **
** Christophe Blaess 2010-2023                                              **
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

	if ((fd = shm_open(argv[1], O_CREAT | O_RDWR, 0666)) < 0) {
		perror(argv[1]);
		exit(1);
	}

	ftruncate(fd, sizeof(int));

	counter = mmap(NULL, sizeof(int), PROT_READ|PROT_WRITE,
	                MAP_SHARED, fd, 0);
	for (;;) {
		fprintf(stderr, "counter = %d\n", *counter);
		sleep(1);
		(*counter) ++;
	}
	return 0;
}
