#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>


//215620 too high

int main() {
    char *str = NULL;
    size_t n = 0;
    getline(&str, &n, stdin);
    int tot = 0;
    char *p = str;
    while (*p) { 
        if ( isdigit(*p) || (*p == '-' && isdigit(*(p+1)) )) {
            tot += strtol(p, &p, 10); 
        } else {
            p++;
        }
    }
    printf("%d\n", tot);
    return 0;
}