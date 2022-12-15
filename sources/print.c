#include "../headers/ssl.h"
#include "../headers/options.h"
#include <unistd.h>

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

void verbose_summary(struct message message, uint64_t opt)
{
	ft_putstr("======SUMMARY======\n");

	ft_putstr("Message: [");
	if (message.len > PREVIEW) {
		write(STDOUT_FILENO, message.content, PREVIEW);
		ft_putstr("...");
	}
	else
		ft_putstr(message.content);
	ft_putstr("]\n");

	ft_putstr("Length: ");
	ft_putnbr(message.len);
	ft_putchar('\n');

	ft_putstr("Input mode: ");
	if (message.input_mode == ARGUMENT)
		ft_putstr("ARGUMENT\n");
	else if (message.input_mode == STDIN)
		ft_putstr("STDIN\n");
	else if (message.input_mode == FILE)
		ft_putstr("FILE\n");
	else
		ft_putstr("UNKNOWN\n");

	ft_putstr("Verbose: ");
	opt & OPT_VERBOSE ? ft_putstr("TRUE\n"):ft_putstr("FALSE\n");

	printf("Quiet: %s\n", opt & OPT_QUIET ? "TRUE":"FALSE");

	ft_putstr("===================\n");
}
