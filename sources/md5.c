#include "../headers/ssl.h"
#include "../headers/md5.h"
#include "../headers/options.h"
#include <stdlib.h>
#include <unistd.h>

static void print_mem(void *address, size_t size)
{
	size_t i = 1;

	while (i <= size) {
		printf("%02x ", ((char *)address)[i-1]);
		if (!(i%16))
			printf("\n");
		i++;
	}
}

static void print_chunks(uint8_t **chunks, size_t nb_chunks)
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

static void free_chunks(uint8_t **chunks, size_t nb_chunks)
{
	size_t i = 0;

	while (i < nb_chunks) {
		if (chunks[i])
			free(chunks[i]);
		i++;
	}
}

static size_t align(size_t value, size_t round)
{
	value += round;
	value &= ~(round-1);
	return value;
}

int md5(struct message message, uint64_t opt)
{
	(void)message;
	(void)opt;
	size_t nb_chunks = MD5_PADDED(message.len)/RAW_CHUNK_SIZE;
	size_t i = 0;
	uint8_t *chunks[nb_chunks];

	ft_bzero(chunks, sizeof(chunks));

	if (opt & OPT_VERBOSE) {
		ft_putstr("[*] Dividing the message in ");
		ft_putnbr(nb_chunks);
		ft_putstr(" chunk(s) of ");
		ft_putnbr(RAW_CHUNK_SIZE*CHAR_BIT);
		ft_putstr(" bits\n");
	}

	while (i < nb_chunks) {
		chunks[i] = malloc(RAW_CHUNK_SIZE);
		if (!(chunks[i])) {
			ft_putstr_fd("[!] Malloc failed when allocating chunk ", STDERR_FILENO);
			ft_putnbr_fd(i, STDERR_FILENO);
			ft_putchar_fd('\n', STDERR_FILENO);
			break;
		}
		ft_bzero(chunks[i], RAW_CHUNK_SIZE);
		i++;
	}

	(void)print_chunks;
	//print_chunks(chunks, nb_chunks);

	/* Freeing chunks */
	if (opt & OPT_VERBOSE) {
		ft_putstr("[*] Freeing ");
		ft_putnbr(nb_chunks);
		ft_putstr(" chunk(s) of ");
		ft_putnbr(RAW_CHUNK_SIZE*CHAR_BIT);
		ft_putstr(" bits\n");
	}
	free_chunks(chunks, nb_chunks);

	if (opt & OPT_VERBOSE)
		ft_putstr("[*] Done\n");

	return 0;
}
