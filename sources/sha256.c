#include "../headers/ssl.h"
#include "../headers/sha256.h"
#include "../headers/options.h"

int sha256(struct message message, uint64_t opt) {
	(void)message;
	(void)opt;
	printf("SHA256\n");
	return 0;
}
