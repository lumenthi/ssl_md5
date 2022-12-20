#include "../headers/ssl.h"

static void print_art()
{
	printf(
	"\n"
	"\n"
    "     ███████╗████████╗     ███████╗███████╗██╗        \n"
    "     ██╔════╝╚══██╔══╝     ██╔════╝██╔════╝██║        \n"
    "     █████╗     ██║        ███████╗███████╗██║        \n"
    "     ██╔══╝     ██║        ╚════██║╚════██║██║        \n"
    "     ██║        ██║███████╗███████║███████║███████╗   \n"
    "     ╚═╝        ╚═╝╚══════╝╚══════╝╚══════╝╚══════╝ 1.0.1\n"
    "                                   lumenthi@student.42.fr\n"
	"\n"
	);
}

void print_version()
{
	printf("lumenthi's ft_ssl version 1.0.1 (https://github.com/lumenthi/ssl_md5)\n"
			"This program is free software; you may redistribute it\n"
			"This program has absolutely no warranty\n"
	);
}

void print_usage()
{
	printf("USAGE:\n"
		"  ft_ssl [md5|sha256] [File(s)] [Options]\n"
	);
}

void print_help()
{
	/* Header */
	print_art();
	print_usage();
	printf("\n");

	/* Content */
	printf("Help menu\n");

	/* Footer */
	printf("\n");
	print_version();
}
