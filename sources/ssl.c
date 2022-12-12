#include "../headers/ssl.h"
#include "../headers/options.h"

int ft_ssl(char *message, uint64_t opt)
{
	if (opt & OPT_VERBOSE)
		verbose_summary(message, opt);

	ft_putstr("Doing things\n");

	return 0;
}
