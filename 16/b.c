#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <stdint.h>


int getIdx(char *key) {
    if (strcmp("children:", key) == 0) return 0;
    if (strcmp("cats:", key) == 0) return 1;
    if (strcmp("samoyeds:", key) == 0) return 2;
    if (strcmp("pomeranians:", key) == 0) return 3;
    if (strcmp("akitas:", key) == 0) return 4;
    if (strcmp("vizslas:", key) == 0) return 5;
    if (strcmp("goldfish:", key) == 0) return 6;
    if (strcmp("trees:", key) == 0) return 7;
    if (strcmp("cars:", key) == 0) return 8;
    if (strcmp("perfumes:", key) == 0) return 9;
}

int main() {
    int sue[] = {3,7,2,3,0,0,5,3,2,1}, vals[3], num; 
    char *keys[3];
    for (int i = 0; i < 3; i++) keys[i] = malloc(16*sizeof(char));
    while (scanf("Sue %d: %s %d, %s %d, %s %d\n", &num, keys[0], &vals[0], keys[1], &vals[1], keys[2], &vals[2]) != EOF) {
        for (int i = 0; i < 3; i++) {
            int idx = getIdx(keys[i]);
            switch (idx) {
                case 1: case 7:
                    if (sue[idx] >= vals[i]) goto cont;
                    break;
                case 3: case 6:
                    if (sue[idx] <= vals[i]) goto cont;
                    break;
                default:
                    if (sue[idx] != vals[i]) goto cont;
            }
        }
        printf("%d\n", num);
        cont: continue;
    }
    return 0;
}