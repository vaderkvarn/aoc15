#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

typedef struct {
    char *from;
    char *to;
} Replacement;

Replacement replacements[256];
size_t num_replacements = 0;

char *visited[4096];
size_t num_visited = 0;

char str[1024];

bool isVisited(char *str) {
    for (int i = 0; i < num_visited; i++) {
        if (strcmp(str, visited[i]) == 0) return true;
    }
    return false;
}

void getCombs() {
    size_t str_length = strlen(str);
    for (char *c = str; *c != '\0'; c++) {
        for (int i = 0; i < num_replacements; i++) {
            Replacement r = replacements[i];
            char *c2 = c;
            size_t from_length = strlen(r.from);
            for(int j = 0; j < from_length; j++) {
                if (*c2 != r.from[j]) {
                    break;
                }
                c2++;
            }
            if (c2-c == from_length) {
                char *replaced = malloc(1024*sizeof(char));
                sprintf(replaced, "%.*s%s%.*s", (int)(c - str), str, r.to, (int)(str + str_length - c2), c2);
                if (!isVisited(replaced)) {
                    visited[num_visited++] = replaced;
                }
            }
        }
    }
}

int main() {
    char from[1024], to[16];
    int num_read;
    while((num_read = scanf("%s => %s\n", from, to)) > 0) {
        if (num_read > 1) {
            Replacement r;
            r.from = malloc(16*sizeof(char));
            r.to = malloc(16*sizeof(char));
            strcpy(r.from, from);
            strcpy(r.to, to);
            replacements[num_replacements++] = r;
        }
        else {
            strcpy(str, from);
        }
    }
    getCombs();
    printf("%ld\n", num_visited);

    return 0;
}