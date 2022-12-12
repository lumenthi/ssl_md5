#include "../headers/ssl.h"
#include "../headers/options.h"

void print_help()
{
	ft_putstr("Help menu\n");
}

void print_version()
{
	ft_putstr("Version menu\n");
}

void print_usage()
{
	ft_putstr("Usage menu\n");
}

void verbose_summary(char *message, uint64_t opt)
{
	ft_putstr("======SUMMARY======\n");

	/* TODO: Display a shoten version if string is too big */
	ft_putstr("Message: ");
	ft_putstr(message);
	ft_putchar('\n');

	ft_putstr("Verbose: ");
	opt & OPT_VERBOSE ? ft_putstr("TRUE\n"):ft_putstr("FALSE\n");

	ft_putstr("===================\n");
}
