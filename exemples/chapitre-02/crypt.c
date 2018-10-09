#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

char * salt_values="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz012345679./";

int main(int argc, char * argv[])
{
	char salt[3];

	if (argc < 2) {
		fprintf(stderr, "usage: %s <password>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	srand((unsigned int) time(NULL));
	salt[0] = salt_values[rand()%64];
	salt[1] = salt_values[rand()%64];
	salt[2] = '\n';
	fprintf(stdout, "%s\n", crypt(argv[1], salt));
	return EXIT_SUCCESS;
}
