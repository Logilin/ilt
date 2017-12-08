#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define NB_BLOCS 10

int main (void)
{
	char * ptr[NB_BLOCS];
	int i;

	fprintf(stderr, "Allocation...\n");
	for (i = 0; i < NB_BLOCS; i ++)
		ptr[i] = malloc(1024);

	fprintf(stderr, "Utilisation...\n");
	for (i = 0; i < NB_BLOCS; i ++)
		memset(ptr[i], 1, 1024);

	fprintf(stderr, "Libération...\n");
	for (i = NB_BLOCS-1; i > 0; i --);
		free(ptr[i]);

	return 0;
}


