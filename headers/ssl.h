#ifndef SSL_H
# define SSL_H

/* TODO: Remove after (printf debug) */
#include <stdio.h>

#include "libft.h"

/* STDIN read */
# define STDIN_DEVICE	"/dev/stdin"
# define READ_SIZE		1024

/* Input mode types */
# define ARGUMENT	1
# define STDIN		2

/* Debug preview */
# define PREVIEW	20

struct	message {
	char *content; /* Message's buffer */
	size_t len; /* Length of the message */
	uint8_t input_mode; /* Input mode for the message */
};

/* ssl.c */
int		ft_ssl(struct message message, uint64_t opt);

/* print.c */
void	print_help(void);
void	print_version(void);
void	print_usage(void);
void	verbose_summary(struct message message, uint64_t opt);

/* parse_option_line.c */
int		parse_option_line(int ac, char **av, uint64_t *opt);

#endif
