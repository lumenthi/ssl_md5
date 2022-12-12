#include "../headers/ssl.h"
#include "../headers/options.h"

int ft_ssl(uint64_t opt)
{
	ft_putstr("ft_ssl\n");

	if (opt & OPT_VERBOSE)
		ft_putstr("verbose\n");

	return 0;
}
