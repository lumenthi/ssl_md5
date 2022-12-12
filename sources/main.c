#include "../headers/ssl.h"
#include "../headers/options.h"

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

static void	*brealloc(void *ptr, size_t new_size, size_t old_size)
{
	void *new_ptr = malloc(new_size);

	if (new_ptr) {
		ft_bzero(new_ptr, new_size);
		if (ptr)
			ft_memmove(new_ptr, ptr, old_size);
	}

	if (ptr)
		free(ptr);

	return new_ptr;
}

/* TODO: Check error cases leaks etc.. ? Force them */
static int read_from_stdin(struct message *message)
{
	size_t i = 2;
	size_t ret;
	int fd;
	char *tmp;

	fd = open(STDIN_DEVICE, O_NONBLOCK|O_RDONLY);
	if (fd == -1) {
		ft_putstr_fd("[!] Cannot read from STDIN, open failed\n", STDERR_FILENO);
		return -1;
	}

	/* malloc(READ_SIZE); */
	if (!(message->content = malloc(sizeof(char) * READ_SIZE))) {
		ft_putstr_fd("[!] Cannot read from STDIN, malloc failed\n", STDERR_FILENO);
		return -1;
	}
	ft_bzero(message->content, READ_SIZE);
	tmp = message->content;

	while((ret = read(fd, tmp, READ_SIZE)) > 0) {
		if (!(message->content = brealloc(message->content, i*READ_SIZE, (i-1)*READ_SIZE))) {
			ft_putstr_fd("[!] Cannot read from STDIN, malloc failed\n", STDERR_FILENO);
			return -1;
		}
		message->len += ret;
		tmp = message->content;
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
	struct message message = {0};
	int ret;

	/* TODO: Remove printfs in parse_option_line */
	if (parse_option_line(ac, av, &opt))
		return -1;

	ret = read_from_stdin(&message);
	if (ret < 0)
		return -1;
	else if (ret != 0) {
		message.input_mode = STDIN;
		ft_ssl(message.content, opt, STDIN);
	}

	if (message.content)
		free(message.content);

	return 0;
}
