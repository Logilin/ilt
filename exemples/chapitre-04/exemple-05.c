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
#include <string.h>
#include <unistd.h>


int main(int argc, char * argv[])
{
	mqd_t mq;
	int priorite;

	if ((argc != 4) || (sscanf(argv[2], "%d", & priorite) != 1)) {
		fprintf(stderr, "usage: %s nom_mq priorite message\n",
		                 argv[0]);
		exit(EXIT_FAILURE);
	}
	
	mq = mq_open(argv[1], O_CREAT | O_WRONLY, 0666, NULL);
	if (mq == -1) {
		perror(argv[1]);
		exit(EXIT_FAILURE);
	}
	
	if (mq_send(mq, argv[3], strlen(argv[3]), priorite) != 0) {
		perror("mq_send");
		exit(EXIT_FAILURE);
	}
	return EXIT_SUCCESS;
}

