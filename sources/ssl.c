#include "../headers/ssl.h"
#include "../headers/options.h"
#include "../headers/md5.h"

int ft_ssl(struct message message, uint64_t opt)
{
	if (opt & OPT_VERBOSE)
		verbose_summary(message, opt);

	md5(message);

	return 0;
}
