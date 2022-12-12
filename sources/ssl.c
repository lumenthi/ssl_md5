#include "../headers/ssl.h"
#include "../headers/options.h"

int ft_ssl(char *message, uint64_t opt, uint8_t mode)
{
	if (opt & OPT_VERBOSE)
		verbose_summary(message, opt, mode);

	ft_putstr("Doing things\n");

	return 0;
}
