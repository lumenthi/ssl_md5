#include "../headers/ssl.h"
#include "../headers/md5.h"
#include <stdlib.h>

void print_mem(void *address, size_t size)
{
	size_t i = 1;

	while (i <= size) {
		printf("%02x ", ((unsigned char *)address)[i-1]);
		if (!(i%16))
			printf("\n");
		i++;
	}
}

/*
 * TODO: Beware, RAW_CHUNK_SIZE can vary depending of algorithms.
 *   Here, only the RAW_CHUNK_SIZE from the MD5 algorithm is imported,
 *   it works for SHA256 since they share the same block size.
*/
void print_chunks(uint8_t **chunks, size_t nb_chunks)
{
	size_t i = 0;

	printf("CHUNKS:\n");

	while (i < nb_chunks) {
		if (chunks[i]) {
			printf("[%ld]\n", i);
			print_mem(chunks[i], RAW_CHUNK_SIZE);
		}
		i++;
	}
}

void free_chunks(uint8_t **chunks, size_t nb_chunks)
{
	size_t i = 0;

	while (i < nb_chunks) {
		if (chunks[i])
			free(chunks[i]);
		i++;
	}
}

size_t align(size_t value, size_t round)
{
	value += round;
	value &= ~(round-1);
	return value;
}
