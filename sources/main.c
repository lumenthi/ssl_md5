#include "../headers/ssl.h"
#include "../headers/options.h"

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

/* TODO: Check error cases leaks etc.. ? Force them */
static int read_from_stdin(char **buf)
{
	size_t i = 2;
	int fd;
	char *tmp;

	fd = open(STDIN_DEVICE, O_NONBLOCK|O_RDONLY);
	if (fd == -1) {
		ft_putstr_fd("[!] Cannot read from STDIN, open failed\n", STDERR_FILENO);
		return -1;
	}

	/* malloc(READ_SIZE); */
	if (!(*buf = malloc(sizeof(char) * READ_SIZE))) {
		ft_putstr_fd("[!] Cannot read from STDIN, malloc failed\n", STDERR_FILENO);
		return -1;
	}
	ft_bzero(*buf, READ_SIZE);
	tmp = *buf;

	while((read(fd, tmp, READ_SIZE) > 0)) {
		if (!(*buf = ft_realloc(*buf, i * READ_SIZE))) {
			ft_putstr_fd("[!] Cannot read from STDIN, malloc failed\n", STDERR_FILENO);
			return -1;
		}
		tmp = *buf;
		tmp = (void*)tmp + (READ_SIZE*(i-1));
		i++;
	}

	close(fd);

	return i-2;
}

/* TODO: No printf allowed */
int main(int ac, char **av)
{
	uint64_t	opt = 0;
	char *stdin_msg = NULL;
	int ret;

	/* TODO: Remove printfs in parse_option_line */
	if (parse_option_line(ac, av, &opt))
		return -1;

	ret = read_from_stdin(&stdin_msg);
	if (ret < 0)
		return -1;
	else if (ret != 0)
		ft_ssl(stdin_msg, opt, STDIN);

	if (stdin_msg)
		free(stdin_msg);

	return 0;
}
