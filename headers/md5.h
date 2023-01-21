#ifndef FT_MD5_H
# define FT_MD5_H

#include <limits.h>

/* Blocks of 512 bits (64 Bytes) */
# define RAW_CHUNK_SIZE (512/(sizeof(char) * CHAR_BIT))

/*
 * Original length +
 * 64 (representing the length of the original message)
 */
# define MD5_PADDED(len) (align(len+sizeof(uint64_t), RAW_CHUNK_SIZE))

/* Constants defined by the MD5 algorithm */
#define MD5_A 0x67452301
#define MD5_B 0xefcdab89
#define MD5_C 0x98badcfe
#define MD5_D 0x10325476

/* Bit-manipulation functions defined by the MD5 algorithm */
#define MD5_F(X, Y, Z) ((X & Y) | (~X & Z))
#define MD5_G(X, Y, Z) ((X & Z) | (Y & ~Z))
#define MD5_H(X, Y, Z) (X ^ Y ^ Z)
#define MD5_I(X, Y, Z) (Y ^ (X | ~Z))

/* md5.c */
int		md5(struct message message, uint64_t opt);

#endif
