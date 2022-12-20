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

/* TODO: -p, echo STDIN to STDOUT and append the checksum to STDOUT and update help menu */
/* TODO: Check error cases leaks etc.. ? Force them */
/* TODO: Handle `echo -n "" | ./ft_ssl` */
int read_from(struct message *message, char *file)
{
	size_t i = 2;
	int ret;
	int fd;
	char *tmp;

	/* File opening */
	if (!file)
		fd = open(STDIN_DEVICE, O_NONBLOCK|O_RDONLY);
	else
		fd = open(file, O_NONBLOCK|O_RDONLY);
	if (fd == -1) {
		dprintf(STDERR_FILENO,
			"[!] Cannot read from %s, open failed\n", file ? file:"STDIN");
		return -1;
	}

	/* malloc(READ_SIZE); */
	if (!(message->content = malloc(sizeof(char) * READ_SIZE))) {
		dprintf(STDERR_FILENO,
			"[!] Cannot read from %s, malloc failed\n", file ? file:"STDIN");
		return -1;
	}
	ft_bzero(message->content, READ_SIZE);
	tmp = message->content;

	while((ret = read(fd, tmp, READ_SIZE)) > 0) {
		if (!(message->content = brealloc(message->content, i*READ_SIZE, (i-1)*READ_SIZE))) {
			dprintf(STDERR_FILENO,
				"[!] Cannot read from %s, malloc failed\n", file ? file:"STDIN");
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

int main(int ac, char **av)
{
	uint64_t	opt = 0;
	struct message message = {0};
	int ret;
	t_msg *msg_list = NULL;
	t_msg *tmp;

	if (parse_option_line(ac, av, &opt, &msg_list)) {
		free_messages(&msg_list);
		return -1;
	}

	tmp = msg_list;
	while (tmp) {
		ft_ssl(*(tmp->message), opt);
		tmp = tmp->next;
	}
	free_messages(&msg_list);

	ret = read_from(&message, NULL);
	if (ret < 0)
		return -1;
	else if (ret != 0) {
		message.input_mode = STDIN;
		ft_ssl(message, opt);
	}

	if (message.content)
		free(message.content);

	return 0;
}
