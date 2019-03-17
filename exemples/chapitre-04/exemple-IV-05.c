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
#include <string.h>
#include <unistd.h>


int main(int argc, char * argv[])
{
	mqd_t mq;
	int priority;

	if ((argc != 4)
	 || (sscanf(argv[2], "%d", &priority) != 1)) {
		fprintf(stderr, "usage: %s mq_name priority message\n",
		                 argv[0]);
		exit(EXIT_FAILURE);
	}

	mq = mq_open(argv[1], O_CREAT | O_WRONLY, 0666, NULL);
	if (mq == -1) {
		perror(argv[1]);
		exit(EXIT_FAILURE);
	}

	if (mq_send(mq, argv[3], strlen(argv[3]), priority) != 0) {
		perror("mq_send");
		exit(EXIT_FAILURE);
	}
	return EXIT_SUCCESS;
}
