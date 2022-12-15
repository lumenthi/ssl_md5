#include "../libft/libft.h"
#include "../headers/ssl.h"
#include "options.h"
#include <stdlib.h>

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

	struct message message = {0};
	int read_ret;

	while (i < ac) {
		if (!is_arg_an_opt(av, i, optstring, long_options)) {
			/* TODO: Do this when input is a string */
			/* message.len = ft_strlen(av[i]); */
			/* message.content = av[i]; */
			message.len = 0;
			message.filename = av[i];
			message.input_mode = FILE;
			read_ret = read_from(&message, av[i]);
			if (read_ret > 0) {
				ft_ssl(message, *ret);
				if (message.content) {
					free(message.content);
					message.content = NULL;
				}
			}
			arg_count++;
		}
		i++;
	}

	return 0;
}
