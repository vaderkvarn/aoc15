#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define N 150
int num;

bool addsUp(int *set, int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += set[i];    
    }
    return sum == N;
}

bool visited(int* set, int n, int **res, int n_res) {
    if (n_res == 0) return false;
    for (int i = 0; i < n_res; i++) {
        for (int j = 0; j < n; j++) {
            if (set[j] != res[i][j]) return false;
        }
    }
    return true;
}

void run3(int *set, int n, int p, int **res, int n_res) {
    if (addsUp(set, n) && !visited(set, n, res, n_res)) {
        num++;
        res[n_res++] = set;
    }
    if (p == -1) return;
    int *w = malloc(n*sizeof(int));
    int *o = malloc(n*sizeof(int));
    for (int i = 0; i < n; i++) {
        w[i] = set[i];
        o[i] = set[i];
    }
    o[p] = 0;
    run3(w, n, p-1, res, n_res);
    run3(o, n, p-1, res, n_res);
}

int main() {
    int set[64], n = 0;
    for (; scanf("%d\n", &set[n]) != EOF; n++);
    int **res = malloc(8*sizeof(int*));
    run3(set, n, n-1, res, 0);
    printf("%d\n", num);
}