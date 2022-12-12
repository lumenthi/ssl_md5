#include "../headers/ssl.h"
#include "../headers/options.h"

int main(int ac, char **av)
{
	uint64_t	opt;

	if (parse_option_line(ac, av, &opt))
		return -1;

	/* TODO: No printf allowed */
	ft_ssl(opt);
	return 0;
}
