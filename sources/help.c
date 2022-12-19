#include "../headers/ssl.h"

void print_version()
{
	ft_putstr("Version menu\n");
}

void print_usage()
{
	printf("USAGE:\n"
		"  ft_ssl [md5|sha256] [File(s)] [Options]\n"
	);
}

void print_help()
{
	print_usage();
	printf("\n");
	printf("Help menu\n");
}
