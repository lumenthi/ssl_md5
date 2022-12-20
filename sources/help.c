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

static void algorithms()
{
	printf("ALGORITHMS:\n"
		"  MD5: MD5 Digest\n"
		"  SHA256: SHA-2 256 Digest\n"
	);
}

static void description()
{
	printf("DESCRIPTION:\n"
		"  Calculation of Message Digests\n"
	);
}

static void input()
{
	printf("INPUT:\n"
		"  Can pass files as well as strings\n"
		"  FILES:\n"
		"    ft_ssl md5 [file(s)]\n"
		"    Exemple: ft_ssl md5 file1 file2\n"
		"  STRINGS:\n"
		"    -s --string <string>\n"
		"    Exemple: ft_ssl md5 -s \"Im the message to digest\"\n"
		"  STDIN:\n"
		"    ft_ssl reads the STDIN file descriptor, you can use it to pass message to digest\n"
		"    Exemple: echo -n \"Im the message to digest\" | ft_ssl md5\n"
	);
}

static void options()
{
	printf("OPTIONS:\n"
			"  -s --string: Print the sum of the given string\n"
			"  -r --reverse: Reverse the format of the output\n"
			"  -q --quiet: Quiet mode\n"
			"  -v --verbose: Display informations about what ft_ssl is doing\n"
			"  -h --help: Display the help menu\n"
			"  -V --version: Output the current version of this software\n"
	);
}

void print_help()
{
	/* Header */
	print_art();
	print_usage();
	printf("\n");

	/* Content */
	description();
	algorithms();
	input();
	options();

	/* Footer */
	printf("\n");
	print_version();
}
