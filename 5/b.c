#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool has_double_inner(char *s, int start, int end, char p1, char p2) {
    for (int i = start; i < end; i++) {
        if (s[i] == p1 && s[i+1] == p2) return true;
    }
    return false;
}

bool has_double(char *s, int pos) {
    size_t len = strlen(s);
    if (pos >= len - 2) return false;

    for (int i = pos + 2; i < len; i++) {
        if (s[i] == s[pos] && s[i+1] == s[pos + 1]) return true;
    }
    return false;
}

bool is_nice(char* s) {
    size_t len = strlen(s);
    bool hb = false;
    bool xyx = false;
    for (int i = 0; i < len; i++) { 
        if (has_double(s, i)) {
            hb = true;
            break;
        }
    }
    char s0 = s[0];
    for (char* s2 = s + 2 ; *s2 != '\0'; s2++) { 
        if (s0 == *s2) {
            xyx = true; 
            break;
        }
        s0 = *(s2 - 1);
    }
    return hb && xyx;
}

int main() {
    char s[256];
    int num_nice = 0;
	while (scanf("%s\n", s) != EOF) {
        if (is_nice(s)) num_nice++;
    }
    printf("%d\n", num_nice);
    return 0;
}