#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


int main() {
    size_t size = 256;
    char *buf = malloc(size*sizeof(char));
    int tot = 0;
    int chars = 0;
    while (getline(&buf, &size, stdin) != -1) {
        buf[strcspn(buf, "\n")] = 0;
        size_t len = strlen(buf);
        tot += len;
        for (int i = 0; i < len; i++) {
            if (buf[i] == '"') chars++;
            if (buf[i] == '\\') chars++;
            chars++;
        }
        chars += 2;
    }
    printf("%d\n", chars-tot);
    return 0;
}