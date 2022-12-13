#include "../headers/ssl.h"
#include "../headers/md5.h"
#include "../headers/options.h"

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

	if (opt & OPT_VERBOSE) {
		ft_putstr("[*] Dividing the message in ");
		ft_putnbr(nb_chunks);
		ft_putstr(" chunk(s) of ");
		ft_putnbr(RAW_CHUNK_SIZE*CHAR_BIT);
		ft_putstr(" bits\n");
	}

	return 0;
}
