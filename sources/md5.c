#include "../headers/ssl.h"
#include "../headers/md5.h"
#include "../headers/options.h"
#include <stdlib.h>
#include <unistd.h>

static int md5_compute(uint8_t **chunks, size_t nb_chunks, uint32_t *digest,
	uint64_t opt)
{
	/* Constants defined by the MD5 algorithm */
	uint32_t S[] = {
		7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
		5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20,
		4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
		6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
	};
	uint32_t K[] = {
		0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
		0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
		0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
		0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
		0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
		0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
		0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
		0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
		0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
		0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
		0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
		0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
		0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
		0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
		0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
		0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
	};

	uint32_t A,B,C,D,E,f; /* MD5 Processing variables */
	uint32_t *cur_chunk;
	size_t i = 0, k = 0; /* Counters */

	/* Digest inititalisation */
	digest[0] = MD5_A;
	digest[1] = MD5_B;
	digest[2] = MD5_C;
	digest[3] = MD5_D;

	/* Break chunk into sixteen 32-bit words */
	while (i < nb_chunks) {
		if (opt & OPT_VERBOSE) {
			ft_putstr("[*] MD5 Computing chunk ");
			ft_putnbr(i);
			ft_putstr("\n");
		}
		if (!chunks[i]) {
			ft_putstr_fd("[!] An error hapenned during the calculation process\n",
				STDERR_FILENO);
			return -1;
		}
		cur_chunk = (uint32_t *)chunks[i];
		/* For each uint32_t blocks, do */
		/* Init hash variables for this chunk */
		A = digest[0];
		B = digest[1];
		C = digest[2];
		D = digest[3];
		k = 0;
		/* Main loop */
		while (k < 64) {
			if (k < 16) {
				E = MD5_F(B, C, D);
				f = k;
			}
			else if (k < 32) {
				E = MD5_G(B, C, D);
				f = ((5*k)+1) % 16;
			}
			else if (k < 48) {
				E = MD5_H(B, C, D);
				f = ((3*k)+5) % 16;
			}
			else {
				E = MD5_I(B, C, D);
				f = (7*k) % 16;
			}
			E = E + A + K[k] + cur_chunk[f];
			A = D;
			D = C;
			C = B;
			B = B + rotate_left(E, S[k]);
			k++;
		}

		/* Add the compressed chunk to the current hash value */
		digest[0] += A;
		digest[1] += B;
		digest[2] += C;
		digest[3] += D;

		/* Next chunk */
		i++;
	}

	return 0;
}

int md5(struct message message, uint64_t opt)
{
	size_t nb_chunks = MD5_PADDED(message.len)/RAW_CHUNK_SIZE;
	size_t i = 0;
	size_t offset = 0;
	size_t count = 0;
	uint8_t *chunks[nb_chunks];
	uint8_t *content_bits;
	uint32_t digest[4] = {0};
	uint8_t end = 0;
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
		content_bits = (uint8_t *)(chunks[i]);
		offset = i*RAW_CHUNK_SIZE;
		count = 0;
		while (count < RAW_CHUNK_SIZE) {
			content_bits[count] = (message.content)[offset];
			if (offset >= message.len && !end) {
				/* Setting the bit after our message to '1' */
				/* Writing bits '1000 0000' (0x80) */
				content_bits[count] = 0x80;
				end = 1;
				break;
			}
			offset++;
			count++;
		}
		/* Last chunk */
		if (i+1 >= nb_chunks) {
			uint64_t *size_bits = (uint64_t *)(chunks[i]+RAW_CHUNK_SIZE-sizeof(uint64_t));
			*size_bits = message.len * CHAR_BIT;
		}
		i++;
	}

	(void)print_chunks;
	/* print_chunks(chunks, nb_chunks); */

	/* calculation process */
	if (opt & OPT_VERBOSE)
		ft_putstr("[*] Starting the calculation process\n");
	ret = md5_compute(chunks, nb_chunks, digest, opt);
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

	if (ret == 0)
		print_end(message, digest, MD5, opt);

	if (opt & OPT_VERBOSE)
		ft_putstr("[*] MD5 Done\n");

	return 0;
}
