#ifndef SSL_H
# define SSL_H

#include "libft.h"

/* ssl.c */
int		ft_ssl(void);

/* print.c */
void	print_help(void);
void	print_version(void);
void	print_usage(void);

/* parse_option_line.c */
int		parse_option_line(int ac, char **av);

#endif
