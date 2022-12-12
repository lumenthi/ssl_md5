#ifndef SSL_H
# define SSL_H

#include "libft.h"

# define STDIN_DEVICE	"/dev/stdin"
# define READ_SIZE		1024

# define ARGUMENT	1
# define STDIN		2

/* ssl.c */
int		ft_ssl(char *message, uint64_t opt, uint8_t mode);

/* print.c */
void	print_help(void);
void	print_version(void);
void	print_usage(void);
void	verbose_summary(char *message, uint64_t opt, uint8_t mode);

/* parse_option_line.c */
int		parse_option_line(int ac, char **av, uint64_t *opt);

#endif
