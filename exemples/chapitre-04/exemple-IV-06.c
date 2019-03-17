/****************************************************************************\
** Exemple de la formation "Temps-reel Linux et Xenomai"                    **
**                                                                          **
** Christophe Blaess 2010-2018                                              **
** http://christophe.blaess.fr                                              **
** Licence GPLv2                                                            **
\****************************************************************************/


#include <fcntl.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#define BUFFER_SIZE 8192


int main(int argc, char * argv[])
{
	mqd_t mq;
	unsigned int priority;
	char buffer[BUFFER_SIZE];

	if (argc != 2) {
		fprintf(stderr, "usage: %s mq_name\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	mq = mq_open(argv[1], O_RDONLY);
	if (mq == -1) {
		perror(argv[1]);
		exit(EXIT_FAILURE);
	}
	if (mq_receive(mq, buffer, BUFFER_SIZE, &priority) < 0) {
		perror("mq_send");
		exit(EXIT_FAILURE);
	}
	fprintf(stdout, "[%d] %s\n", priority, buffer);

	return EXIT_SUCCESS;
}
