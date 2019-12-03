#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "heap.h"

typedef struct {
    char *from;
    char *to;
} Replacement;

Replacement replacements[256];
size_t num_replacements = 0;

char str[1024];

int iter() {
    Heap h;
    initHeap(&h, 200000);
    Elem e;
    e.val = str;
    e.n = 0;
    hPush(&h, e);

    while (h.length > 0) {
        Elem e = hPop(&h);
        char *s = e.val;
        int n = e.n;
        size_t s_length = strlen(s);
        if (strcmp("e", s) == 0) {
            return n;
        }
        for (char *c = s; *c != '\0'; c++) {
            for (int i = 0; i < num_replacements; i++) {
                Replacement r = replacements[i];
                char *c2 = c;
                size_t to_length = strlen(r.to);
                for(int j = 0; j < to_length; j++) {
                    if (*c2 != r.to[j]) {
                        break;
                    }
                    c2++;
                }
                if (c2-c == to_length) {
                    char *new_s = malloc(1024*sizeof(char));
                    sprintf(new_s, "%.*s%s%.*s", (int)(c - s), s, r.from, (int)(s + s_length - c2), c2);
                    Elem e;
                    e.val = new_s;
                    e.n = n + 1;     
                    hPush(&h, e);
                }
            }
        }
    }
}

int compare(const void *a, const void *b) {
    return strlen((* (Replacement *)b).to) - strlen((* (Replacement *)a).to);
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
    char *start = malloc(2*sizeof(char));
    start[0] = 'e';
    start[1] = '\0';
    qsort(replacements, num_replacements, sizeof(Replacement), compare);
    printf("%d\n", iter());
    return 0;
}