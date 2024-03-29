#include "../libft/libft.h"
#include "../headers/ssl.h"
#include "options.h"
#include <stdlib.h>
#include <unistd.h>

static void push_message(t_msg **head, t_msg *new)
{
	t_msg *tmp = *head;

	if (*head == NULL)
		*head = new;
	else {
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void free_messages(t_msg **head)
{
	t_msg *current = *head;
	t_msg *next;

	while (current != NULL) {
		next = current->next;
		if (current->message) {
			if (current->message->content)
				free(current->message->content);
			free(current->message);
		}
		free(current);
		current = next;
	}

	*head = NULL;
}

static void add_message(t_msg **head, struct message message)
{
	struct message *content;
	t_msg *tmp;

	tmp = malloc(sizeof(t_msg));
	if (!tmp)
		return;
	ft_bzero(tmp, sizeof(t_msg));

	content = malloc(sizeof(struct message));
	if (!content) {
		free(tmp);
		return;
	}
	ft_bzero(content, sizeof(struct message));

	content->filename = message.filename;
	content->content = ft_strdup(message.content);
	content->len = message.len;
	content->input_mode = message.input_mode;

	tmp->message = content;
	push_message(head, tmp);
}

static int valid_cmd(char *name, struct command *cmd_list)
{
	if (!name || !cmd_list)
		return -1;

	int i = 0;

	while (cmd_list[i].name != NULL) {
		if (!(ft_strcmp(name, cmd_list[i].name)))
			return i;
		i++;
	}

	return -1;
}

int parse_option_line(int ac, char **av, uint64_t *ret, t_msg **msg_list,
		struct command *cmd_list)
{
	int opt = 0;
	int option_index = 0;
	char *optarg = NULL;
	int arg_count = 0;
	int i = 1;

	struct message message = {0};
	int read_ret;

	/* Options declaration */
	const char *optstring = "hVvs:qrp";
	static struct option long_options[] = {
		{"help",			0,					0, 'h'},
		{"version",			0,					0, 'V'},
		{"verbose",			0,					0, 'v'},
		{"string",			0,					0, 's'},
		{"quiet",			0,					0, 'q'},
		{"print",			0,					0, 'p'},
		{"reverse",			0,					0, 'r'},
		{0,					0,					0, 0}
	};

	while ((opt = ft_getopt_long(ac, av, optstring, &optarg,
			long_options, &option_index)) != -1)
	{
		switch (opt) {
			case 0:
				/* Long args only */
				break;
			case 'h':
				print_help();
				return -1;
			case 'V':
				print_version();
				return -1;
			case 'v':
				*ret |= OPT_VERBOSE;
				break;
			case 'q':
				*ret |= OPT_QUIET;
				break;
			case 'p':
				*ret |= OPT_PRINT;
				break;
			case 'r':
				*ret |= OPT_REVERSE;
				break;
			case 's':
				*ret |= STDIN_NBLOCK;
				message.filename = NULL;
				message.len = ft_strlen(optarg);
				message.content = optarg;
				message.input_mode = ARGUMENT;
				add_message(msg_list, message);
				break;
			default:
				return -1;
		}
	}

	int cmd_index = -1;
	t_msg *tmp_msg = *msg_list;

	while (i < ac) {
		if (!is_arg_an_opt(av, i, optstring, long_options)) {
			if (arg_count == 0) {
				cmd_index = valid_cmd(av[i], cmd_list);
				if (cmd_index == -1) {
					dprintf(STDERR_FILENO, "[!] Invalid command: %s\n", av[i]);
					print_usage();
					return -1;
				}
				while (tmp_msg) {
					tmp_msg->message->command = &cmd_list[cmd_index];
					tmp_msg = tmp_msg->next;
				}
			}
			else {
				*ret |= STDIN_NBLOCK;
				message.command = &cmd_list[cmd_index];
				message.len = 0;
				message.filename = av[i];
				message.input_mode = FILE;
				read_ret = read_from(&message, av[i], 0);
				if (read_ret > 0) {
					ft_ssl(message, *ret);
					if (message.content) {
						free(message.content);
						message.content = NULL;
					}
				}
			}
			arg_count++;
		}
		i++;
	}

	if (arg_count < 1) {
		print_usage();
		return -1;
	}

	return cmd_index;
}
