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

/* sha256.c */
int		sha256(struct message message, uint64_t opt);

#endif
