#include "../headers/ssl.h"
#include "../headers/md5.h"

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

	printf("PADDED SIZE: %ld\n", MD5_PADDED(message.len));
	printf("TOTAL CHUNKS: %ld\n", MD5_PADDED(message.len)/RAW_CHUNK_SIZE);

	return 0;
}
