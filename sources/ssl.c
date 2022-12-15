#include "../headers/ssl.h"
#include "../headers/options.h"
#include "../headers/md5.h"
#include "../headers/sha256.h"

int ft_ssl(struct message message, uint64_t opt)
{
	if (opt & OPT_VERBOSE)
		verbose_summary(message, opt);

	if (opt & OPT_MD5)
		md5(message, opt);
	else if (opt & OPT_SHA)
		sha256(message, opt);

	return 0;
}
