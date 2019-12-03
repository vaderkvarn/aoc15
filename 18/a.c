#include <stdio.h>
#include <stdlib.h>

#define W 100
#define H 100

int get_n(int **map, int i, int j) {
    int n = 0;
    if (i > 0) {
        n += map[i-1][j];
        if (j > 0) n += map[i-1][j-1];
        if (j < H - 1) n += map[i-1][j+1];
    }
    if (j > 0) n += map[i][j-1]; 
    if (j < H - 1) n += map[i][j+1]; 
    if (i < W - 1) {
        n += map[i+1][j];
        if (j > 0) n += map[i+1][j-1];
        if (j < H - 1) n += map[i+1][j+1];
    }
    return n;
}

int **run(int **map) {
    int **new_map = malloc(W*sizeof(int*));
    for (int i = 0; i < W; i++) {
        new_map[i] = malloc(H*sizeof(int));
    }
    for (int i = 0; i < W; i++) {
        for (int j = 0; j < H; j++) {
            int n_neigh = get_n(map, i, j);
            if (map[i][j]) {
                new_map[i][j] = n_neigh == 2 || n_neigh == 3 ? 1 : 0;
            } else {
                new_map[i][j] = n_neigh == 3 ? 1 : 0;
            }
        }
    }
    for (int i = 0; i < W; i++) {
        free(map[i]);
    }
    free(map);
    return new_map;
}

int getCount(int **map) {
    int count = 0;
    for (int i = 0; i < W; i++)
        for (int j = 0; j < H; j++)
            if (map[i][j]) count++;
    return count;
}

int main() {
    int **map = malloc(W*sizeof(int*));
    for (int i = 0; i < W; i++) {
        map[i] = calloc(H, sizeof(int));
    }
    char c;
    int i = 0;
    while ((c = getchar()) != EOF) {
        if (c == '\n') continue;
        map[i/W][i%H] = c == '#' ? 1 : 0;
        i++;
    }
    for (int i = 0; i < 100; i++) {
        map = run(map);
    }
    printf("%d\n", getCount(map));
    return 0;
}