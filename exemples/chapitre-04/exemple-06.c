/****************************************************************************\
** Exemple de la formation "Temps-reel Linux et Xenomai                     **
**                                                                          **
** Christophe Blaess 2012                                                   **
** http://christophe.blaess.fr                                              **
\****************************************************************************/

#include <fcntl.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#define LG_BUFFER 8192

int main(int argc, char * argv[])
{
	mqd_t mq;
	unsigned int priorite;
	char buffer[LG_BUFFER];

	if (argc != 2) {
		fprintf(stderr, "usage: %s nom_mq\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	mq = mq_open(argv[1], O_RDONLY);
	if (mq == -1) {
		perror(argv[1]);
		exit(EXIT_FAILURE);
	}
	if (mq_receive(mq, buffer, LG_BUFFER, & priorite) < 0) {
		perror("mq_send");
		exit(EXIT_FAILURE);
	}
	fprintf(stdout, "[%d] %s\n", priorite, buffer);
	return EXIT_SUCCESS;
}

