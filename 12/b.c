#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

int main() {
    char *str = NULL;
    size_t n = 0;
    getline(&str, &n, stdin);
    char *p = str;
    while (*p) { 
        if (strncmp(p, "red", 3) == 0) {
            char *start = p;
            char *end = p;
            int match1 = 1, match2 = 1;
            while (match1 != 0 && match2 != 0) {
                start--;
                if (*start == '}') match1++;
                if (*start == ']') match2++;
                if (*start == '{') match1--;
                if (*start == '[') match2--;
            }
            match1 = -1, match2 = -1;
            while (match1 != 0 && match2 != 0) {
                end++;
                if (*end == '}') match1++;
                if (*end == ']') match2++;
                if (*end == '{') match1--;
                if (*end == '[') match2--;
            }
            if (*start == '{') {
                for (char* p0 = start + 1; p0 < end; p0++) *p0 = '|';
            }
        } 
        p++;
    }
    printf("%s\n", str);
    return 0;
}