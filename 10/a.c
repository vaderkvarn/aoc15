#include <stdio.h>
#include <string.h>
#include <limits.h>
int main() {
    char s1[500000];
    strcpy(s1, "3113322113");
    char s2[500000];
    s2[0] = '\0';
    for (int i = 0; i < 40; i++) {
        for (char* c  = s1; *c != '\0'; c++) {
            int num = 1;
            while (*c == *(c+1)) {
                num++; 
                c++;
            }
            char ns[8];
            sprintf(ns, "%d%c", num, *c);
            strcat(s2, ns);
        }
        strcpy(s1, s2);
        s2[0] = '\0';
    }
    printf("%ld\n", strlen(s1));

    return 0;
}