#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BLOCKS_COUNT 10
#define BLOCKS_SIZE  1024

int main (void)
{
	char *blocks[BLOCKS_COUNT];
	int i;

	fprintf(stderr, "Allocating blocks...\n");
	for (i = 0; i < BLOCKS_COUNT; i ++)
		blocks[i] = malloc(BLOCKS_SIZE);
	sleep(1);

	fprintf(stderr, "Using blocks...\n");
	for (i = 0; i < BLOCKS_COUNT; i ++)
		memset(blocks[i], 1, BLOCKS_SIZE);
	sleep(1);

	fprintf(stderr, "Freeing block...\n");
	for (i = BLOCKS_COUNT - 1; i > 0; i --);
		free(blocks[i]);

	return 0;
}

