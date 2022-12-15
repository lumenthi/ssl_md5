#include "../headers/ssl.h"
#include "../headers/sha256.h"
#include "../headers/options.h"
#include <stdlib.h>
#include <unistd.h>

static int sha256_compute(uint8_t **chunks, size_t nb_chunks, uint32_t *digest,
	uint64_t opt)
{
	(void)chunks;
	(void)nb_chunks;
	(void)digest;
	(void)opt;
	printf("Computing things...\n");
	return 0;
}

int sha256(struct message message, uint64_t opt)
{
	size_t nb_chunks = SHA256_PADDED(message.len)/RAW_CHUNK_SIZE;
	size_t i = 0;
	size_t offset = 0;
	size_t count = 0;
	uint8_t *chunks[nb_chunks];
	uint8_t *content_bits;
	uint32_t digest[4] = {0};
	int ret;

	if (!message.content) {
		dprintf(STDERR_FILENO,
			"[!] Something that should not happen hapenned...\n");
		return -1;
	}

	ft_bzero(chunks, sizeof(chunks));

	if (opt & OPT_VERBOSE) {
		ft_putstr("[*] Dividing the message in ");
		ft_putnbr(nb_chunks);
		ft_putstr(" chunk(s) of ");
		ft_putnbr(RAW_CHUNK_SIZE*CHAR_BIT);
		ft_putstr(" bits\n");
	}

	/* Allocating chunks and populating them */
	while (i < nb_chunks) {
		chunks[i] = malloc(RAW_CHUNK_SIZE);
		if (!(chunks[i])) {
			ft_putstr_fd("[!] Malloc failed when allocating chunk ", STDERR_FILENO);
			ft_putnbr_fd(i, STDERR_FILENO);
			ft_putchar_fd('\n', STDERR_FILENO);
			break;
		}
		ft_bzero(chunks[i], RAW_CHUNK_SIZE);
		/* Last chunk */
		content_bits = (uint8_t *)(chunks[i]);
		offset = i*RAW_CHUNK_SIZE;
		count = 0;
		while (count < RAW_CHUNK_SIZE) {
			content_bits[count] = (message.content)[offset];
			if (offset >= message.len) {
				/* Setting the bit after our message to '1' */
				/* Writing bits '1000 0000' (0x80) */
				content_bits[count] = 0x80;
				break;
			}
			offset++;
			count++;
		}
		if (i+1 >= nb_chunks) {
			uint64_t *size_bits = (uint64_t *)(chunks[i]+RAW_CHUNK_SIZE-sizeof(uint64_t));
			*size_bits = message.len * CHAR_BIT;
		}
		i++;
	}

	// (void)print_chunks;
	print_chunks(chunks, nb_chunks);

	/* calculation process */
	if (opt & OPT_VERBOSE)
		ft_putstr("[*] Starting the calculation process\n");
	ret = sha256_compute(chunks, nb_chunks, digest, opt);
	if (opt & OPT_VERBOSE)
		ft_putstr("[*] Finished calculation process\n");

	/* Freeing chunks */
	if (opt & OPT_VERBOSE) {
		ft_putstr("[*] Freeing ");
		ft_putnbr(nb_chunks);
		ft_putstr(" chunk(s) of ");
		ft_putnbr(RAW_CHUNK_SIZE*CHAR_BIT);
		ft_putstr(" bits\n");
	}
	free_chunks(chunks, nb_chunks);
	/* TODO: Remove */
	(void)ret;
	return 0;
}
