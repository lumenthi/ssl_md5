#include "../headers/ssl.h"
#include "../headers/options.h"
#include "../headers/md5.h"
#include "../headers/sha256.h"
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

int ft_ssl(struct message message, uint64_t opt)
{
	if (opt & OPT_VERBOSE)
		verbose_summary(message, opt);

	if (opt & OPT_MD5)
		md5(message, opt);
	else if (opt & OPT_SHA)
		sha256(message, opt);

	return 0;
}
