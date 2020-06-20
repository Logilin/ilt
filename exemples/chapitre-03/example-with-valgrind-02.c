#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main (int argc, char * argv[])
{
	char * ptr;

	if (argc < 2) {
		fprintf(stderr, "usage: %s <string>\n", argv[0]);
		exit(1);
	}

	fprintf(stderr, "Allocating. string...\n");
	ptr = malloc(strlen(argv[1]));
	if (ptr == NULL)
		exit(EXIT_FAILURE);

	fprintf(stderr, "Using string...\n");
	strcpy(ptr, argv[1]);

	fprintf(stderr, "Freeing string...\n");
	free(ptr);

	return 0;
}
