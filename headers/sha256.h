#ifndef SHA256_H
# define SHA256_H

#include <limits.h>

/* Blocks of 512 bits (64 Bytes) */
# define RAW_CHUNK_SIZE (512/(sizeof(char) * CHAR_BIT))

/*
 * Original length +
 * 1 (for appended '1') +
 * 64 (representing the length of the original message)
 */
# define SHA256_PADDED(len) (align(len+1+sizeof(uint64_t), RAW_CHUNK_SIZE))

/* Constants defined by the SHA256 algorithm */
#define SHA256_A 0x6a09e667
#define SHA256_B 0xbb67ae85
#define SHA256_C 0x3c6ef372
#define SHA256_D 0xa54ff53a
#define SHA256_E 0x510e527f
#define SHA256_F 0x9b05688c
#define sha256_G 0x1f83d9ab
#define sha256_H 0x5be0cd19

/* Bit-manipulation function defined by the SHA256 algorithm */
#define SHA256_S0(X) (rotate_right(X,7) ^ rotate_right(X,18) ^ shift_right(X,3))
#define SHA256_S1(X) (rotate_right(X,17) ^ rotate_right(X,19) ^ shift_right(X,10))

/* sha256.c */
int		sha256(struct message message, uint64_t opt);

#endif
