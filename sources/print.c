#include "../headers/ssl.h"
#include "../headers/options.h"
#include <unistd.h>

void print_input(char *message)
{
	int i = 0;

	if (!message)
		return;

	while(message[i]) {
		if (message[i] != '\n')
			write(1, message+i, 1);
		i++;
	}
}

void print_end(struct message message, uint32_t *digest, uint8_t algorithm,
	uint64_t opt)
{
	if ((opt & OPT_QUIET) && (opt & OPT_PRINT)) {
		if (message.input_mode == STDIN) {
				fflush(stdout);
				print_input(message.content);
				printf("\n");
		}
	}
	if (!(opt & OPT_QUIET) && !(opt & OPT_REVERSE)) {
		if (algorithm == MD5)
			printf("MD5");
		else
			printf("SHA256");
		if (message.input_mode == STDIN) {
			printf(" stdin");
			if (opt & OPT_PRINT) {
				printf("(\"");
				fflush(stdout);
				print_input(message.content);
				printf("\")");
			}
		}
		else if (message.input_mode == FILE) {
			if (message.filename)
				printf(" file(%s)", message.filename);
		}
		else if (message.input_mode == ARGUMENT) {
			printf(" string(");
			fflush(stdout);
			if (message.len > PREVIEW) {
				ft_putchar('\"');
				write(STDOUT_FILENO, message.content, PREVIEW);
				ft_putstr("...\"");
			}
			else
				printf("\"%s\"", message.content);
			printf(")");
		}
		printf(" = ");
	}
	if (algorithm == MD5) {
		printf("%08x%08x%08x%08x",
			swap_uint32(digest[0]),
			swap_uint32(digest[1]),
			swap_uint32(digest[2]),
			swap_uint32(digest[3])
		);
	}
	else {
		printf("%08x%08x%08x%08x%08x%08x%08x%08x",
			digest[0],
			digest[1],
			digest[2],
			digest[3],
			digest[4],
			digest[5],
			digest[6],
			digest[7]
		);
	}
	if (!(opt & OPT_QUIET) && (opt & OPT_REVERSE)) {
		printf("  ");
		fflush(stdout);
		if (message.input_mode == STDIN) {
			if (opt & OPT_PRINT) {
				printf("stdin(\"");
				fflush(stdout);
				print_input(message.content);
				printf("\")");
			}
			else
				printf("-");
		}
		else if (message.input_mode == FILE) {
			if (message.filename)
				printf("%s", message.filename);
		}
		else if (message.input_mode == ARGUMENT) {
			if (message.len > PREVIEW) {
				ft_putchar('\"');
				write(STDOUT_FILENO, message.content, PREVIEW);
				ft_putstr("...\"");
			}
			else
				printf("\"%s\"", message.content);
		}
	}
	printf("\n");
}

void verbose_summary(struct message message, uint64_t opt)
{
	ft_putstr("======SUMMARY======\n");

	printf("Algorithm: ");
	if (message.command && message.command->name)
		printf("%s\n", message.command->name);
	else
		printf("UNKNOWN\n");

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

	printf("Reverse: %s\n", opt & OPT_REVERSE ? "TRUE":"FALSE");

	printf("Print: %s\n", opt & OPT_PRINT ? "TRUE":"FALSE");

	ft_putstr("===================\n");
}
