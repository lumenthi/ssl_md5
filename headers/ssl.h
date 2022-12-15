#ifndef SSL_H
# define SSL_H

#include "libft.h"
#include <stdio.h>

/* STDIN read */
# define STDIN_DEVICE	"/dev/stdin"
# define READ_SIZE		1024

/* Input mode types */
# define FILE		1
# define STDIN		2
# define ARGUMENT	3

/* Debug preview */
# define PREVIEW	20

struct	message {
	char *filename; /* If input mode is a file, keep the filename */
	char *content; /* Message's buffer */
	size_t len; /* Length of the message */
	uint8_t input_mode; /* Input mode for the message */
};

/* main.c */
int		read_from(struct message *message, char *file);

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
