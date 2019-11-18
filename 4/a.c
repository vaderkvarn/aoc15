#include <stdio.h>
#include "md5.h"
#include <stdlib.h>
#include <string.h>

int main() {
	int i = 0;
	char msg[256];
	char* hash = calloc(33, sizeof(char));
	while (1) {
		i++;

		strcpy(msg, "yzbqklnj");
		size_t len = strlen(msg);
		sprintf(msg + len, "%d", i);
		len = strlen(msg);
		md5(msg, len, &hash);
		char* pre = "000000";
		if (strncmp(pre, hash, strlen(pre)) == 0) {
			printf("%d\n", i);
			break;
		}
	}
	return 0;
}
