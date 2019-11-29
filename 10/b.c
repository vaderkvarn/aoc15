#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
int main() {
    char* s1;
    char* s2;
    s1 = malloc(5000000*sizeof(char));
    s2 = malloc(5000000*sizeof(char));
    strcpy(s1, "3113322113");
    s2[0] = '\0';
    for (int i = 0; i < 50; i++) {
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
        char* tmp = s1;
        s1 = s2;
        s2 = tmp;
        s2[0] = '\0';
    }
    printf("%ld\n", strlen(s1));

    return 0;
}