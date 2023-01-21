#include "../headers/ssl.h"
#include "../headers/sha256.h"
#include "../headers/options.h"
#include <stdlib.h>
#include <unistd.h>

static int sha256_compute(uint8_t **chunks, size_t nb_chunks, uint32_t *digest,
	uint64_t opt)
{
	/* Constants defined by the SHA256 algorithm */
	uint32_t K[] = {
		0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
		0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
		0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
		0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
		0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
		0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
		0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
		0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
		0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
		0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
		0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
		0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
		0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
		0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
		0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
		0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
	};
	uint32_t *cur_chunk;
	uint32_t split_chunk[64] = {0};
	uint32_t A,B,C,D,E,F,G,H; /* SHA256 Processing variables */
	uint32_t tmp1, tmp2; /* Temporary variables used in the main loop */
	size_t i = 0, j = 0, k = 0; /* Counters */

	/* Digest inititalisation */
	digest[0] = SHA256_A;
	digest[1] = SHA256_B;
	digest[2] = SHA256_C;
	digest[3] = SHA256_D;
	digest[4] = SHA256_E;
	digest[5] = SHA256_F;
	digest[6] = sha256_G;
	digest[7] = sha256_H;

	while (i < nb_chunks) {
		if (opt & OPT_VERBOSE) {
			ft_putstr("[*] SHA256 Computing chunk ");
			ft_putnbr(i);
			ft_putstr("\n");
		}
		if (!chunks[i]) {
			ft_putstr_fd("[!] An error hapenned during the calculation process\n",
				STDERR_FILENO);
			return -1;
		}
		/* Set counters to 0 */
		j = 0;
		k = 0;

		/* Prepare chunks */
		cur_chunk = (uint32_t *)chunks[i];
		while (k < 64) {
			if (k < 16)
				split_chunk[k] = swap_uint32(cur_chunk[k]); /* Swap bits */
			else {
				split_chunk[k] =
					split_chunk[k-16] + SHA256_S0(split_chunk[k-15]) +
					split_chunk[k-7] + SHA256_S1(split_chunk[k-2]);
			}
			/* Debug */
			/* printf("Split Chunk [%ld]\n", k);
			print_mem(split_chunk+k, sizeof(*split_chunk));
			printf("\n"); */
			k++;
		}

		/* Init hash variables for this chunk */
		A = digest[0];
		B = digest[1];
		C = digest[2];
		D = digest[3];
		E = digest[4];
		F = digest[5];
		G = digest[6];
		H = digest[7];

		/* Compression function main loop */
		while (j < 64) {
			tmp1 = H + SHA256_SIG1(E) + SHA256_CH(E, F, G) + K[j] + split_chunk[j];
			tmp2 = SHA256_SIG0(A) + SHA256_MD(A, B, C);
			H = G;
			G = F;
			F = E;
			E = D + tmp1;
			D = C;
			C = B;
			B = A;
			A = tmp1 + tmp2;
			/* Debug */
			/*printf("Values for chunk [%ld]\n", j);
			printf("A[%d] B[%d] C[%d] D[%d] E[%d] F[%d] G[%d] H[%d]\n",
				A,B,C,D,E,F,G,H);*/
			j++;
		}
		/* Add the compressed chunk to the current hash value */
		digest[0] += A;
		digest[1] += B;
		digest[2] += C;
		digest[3] += D;
		digest[4] += E;
		digest[5] += F;
		digest[6] += G;
		digest[7] += H;

		/* Next chunk */
		i++;
	}

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
	uint32_t digest[8] = {0};
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
			*size_bits = swap_uint64(*size_bits);
		}
		i++;
	}

	// (void)print_chunks;
	/* print_chunks(chunks, nb_chunks); */

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

	if (ret == 0)
		print_end(message, digest, SHA, opt);

	if (opt & OPT_VERBOSE)
		ft_putstr("[*] SHA256 Done\n");

	return 0;
}
