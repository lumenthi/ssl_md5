#include "../headers/ssl.h"
#include "../headers/options.h"
#include "../headers/md5.h"
#include "../headers/sha256.h"

int ft_ssl(struct message message, uint64_t opt)
{
	if (opt & OPT_VERBOSE)
		verbose_summary(message, opt);

	if (message.command && message.command->routine)
		message.command->routine(message, opt);

	return 0;
}
