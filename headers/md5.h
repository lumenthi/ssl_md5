#ifndef MD5_H
# define MD5_H

#include <limits.h>

/*
 * The padding works as follows: first, a single bit, 1, is appended to the end of the message.
 * This is followed by as many zeros as are required to bring the length of the message up to 64 bits fewer than a multiple of 512.
 * The remaining bits are filled up with 64 bits representing the length of the original message, modulo 264
*/

/* Blocks of 512 bits (64 Bytes) */
# define RAW_CHUNK_SIZE (512/(sizeof(char) * CHAR_BIT))

/*
 * Original length +
 * 1 (for appended '1') +
 * 64 (representing the length of the original message)
 */
# define MD5_PADDED(len) (align(len+1+sizeof(uint64_t), RAW_CHUNK_SIZE))

/* Add the size of the original message in a 64 bits format */

/* md5.c */
int		md5(struct message message, uint64_t opt);

#endif
