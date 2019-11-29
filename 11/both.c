#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

void inc(char* s) {
    size_t len = strlen(s);
    char* p = s + len - 1;
    bool cont = true;
    while (cont) {
        (*p)++;
        if (*p == 'i' || *p == 'o' || *p == 'l') {
            (*p)++;
        } 
        if (*p > 'z') {
            *p = 'a';
            p--;
            if (p == s - 1) {
                printf("Needs shifting\n");
                exit(1);
            }
        } else {
            cont = false;
        }
    }
}

bool containsBadChars(char* s) {
    size_t len = strlen(s);
    for (char* p = s; p < s + len; p++) {
        if (*p == 'i' || *p == 'o' || *p == 'l') {
            return true;
        }
    }
    return false;
}

bool hasIncStraight(char* s) {
    size_t len = strlen(s);
    for (char *p0 = s, *p1 = s + 1, *p2 = s + 2; p2 < s + len; p0++, p1++, p2++) {
        if (*p0 == *p1 - 1 && *p1 == *p2 - 1) return true;
    }
    return false;
}

bool hasPairs(char* s) {
    size_t len = strlen(s);
    bool found_pair = false;
    for (char* p = s + 1; p < s + len; p++) {
        if (*p == *(p-1)) {
            if (found_pair) return true;
            found_pair = true;
            if (p + 2 >= s + len) return false;
            p += 1;
        }
    }
    return false;
}

bool isValid(char* s) {
    return hasIncStraight(s) && hasPairs(s) && !containsBadChars(s);
}

int main() {
    char str[32];
    strcpy(str, "vzbxkghb");
    while (!isValid(str)) inc(str);
    printf("%s\n", str);
    inc(str);
    while (!isValid(str)) inc(str);
    printf("%s\n", str);
    return 0;
}