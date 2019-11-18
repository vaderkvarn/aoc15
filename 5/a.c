#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool is_nice(char* s) {
    bool has_duplicate = false;
    char lc = *s;
    int num_vowels = strchr("aeiou", lc) != NULL ? 1 : 0;
    char* bad[] = {"ab", "cd", "pq", "xy"};
    for (char* c = s + 1; *c != '\0'; c++) {
        char sb[2];
        sb[0] = lc;
        sb[1] = *c;
        for (size_t i = 0; i < 4; i++) {
            if (strcmp(sb, bad[i]) == 0) {
                return false;
            }
        }
        if (strchr("aeiou", *c) != NULL) num_vowels++;
        if (*c == lc) has_duplicate = true;
        lc = *c;
    }
    return num_vowels >= 3 && has_duplicate;
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