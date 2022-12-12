#include "../headers/ssl.h"
#include "../headers/options.h"

int main(int ac, char **av)
{
	if (parse_option_line(ac, av))
		return -1;

	/* TODO: No printf allowed */
	ft_ssl();
	return 0;
}
