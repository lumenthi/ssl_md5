#include "../libft/libft.h"
#include "../headers/ssl.h"
#include "options.h"

int		parse_option_line(int ac, char **av, uint64_t *ret)
{
	int opt = 0;
	int option_index = 0;
	char *optarg = NULL;
	int arg_count = 0;
	int i = 1;

	/* Options declaration */
	const char *optstring = "hVv";
	static struct option long_options[] = {
		{"help",			0,					0, 'h'},
		{"version",			0,					0, 'V'},
		{"verbose",			0,					0, 'v'},
		{0,					0,					0, 0}
	};

	while ((opt = ft_getopt_long(ac, av, optstring, &optarg,
			long_options, &option_index)) != -1)
	{
		switch (opt) {
			case 0:
				/* Long args only */
				break;
			case 'h':
				print_help();
				return 1;
			case 'V':
				print_version();
				return 1;
			case 'v':
				*ret |= OPT_VERBOSE;
				break;
			default:
				return 1;
		}
	}

	while (i < ac) {
		if (!is_arg_an_opt(av, i, optstring, long_options)) {
			ft_ssl(av[i], *ret, ARGUMENT);
			arg_count++;
		}
		i++;
	}

	return 0;
}
