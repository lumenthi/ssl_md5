#ifndef SSL_H
# define SSL_H

#include "libft.h"
#include "options.h"
#include <stdio.h>

/* STDIN read */
# define STDIN_DEVICE	"/dev/stdin"
# define READ_SIZE		1024

/* Input mode types */
# define FILE		1
# define STDIN		2
# define ARGUMENT	3

/* Algorithms */
# define MD5		1
# define SHA		2

/* Debug preview */
# define PREVIEW	40

/* Rotate macros used in hashing algorithms */
#define rotate_left(x, n) ((x << n) | (x >> (32 - n)))
#define rotate_right(x, n) ((x >> n) | (x << (32 - n)))
/* Shift macros used in hashing algorithms */
#define shift_left(x, n) (x << n)
#define shift_right(x, n) (x >> n)

struct	message {
	char *filename; /* If input mode is a file, keep the filename */
	char *content; /* Message's buffer */
	size_t len; /* Length of the message */
	uint8_t input_mode; /* Input mode for the message */
};

/* main.c */
int		read_from(struct message *message, char *file, uint8_t non_block);

/* chunk.c */
void	print_mem(void *address, size_t size);
void	print_chunks(uint8_t **chunks, size_t nb_chunks);
void	free_chunks(uint8_t **chunks, size_t nb_chunks);
size_t	align(size_t value, size_t round);

/* ssl.c */
int		ft_ssl(struct message message, uint64_t opt);

/* help.c */
void	print_help(void);
void	print_version(void);
void	print_usage(void);

/* print.c */
void	verbose_summary(struct message message, uint64_t opt);
void print_end(struct message message, uint32_t *digest, uint8_t algorithm,
	uint64_t opt);

/* options.c */
void	free_messages(t_msg **head);

/* parse_option_line.c */
int		parse_option_line(int ac, char **av, uint64_t *opt, t_msg **msg_list);

#endif
