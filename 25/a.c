#include <stdio.h>
#include <stdint.h>

int colf(int col) {
    if (col == 1) return 1;
    return colf(col - 1) + col;
}

int getVal(int row, int col) {
    int val = colf(col);
    for (int i = 0; i < row - 1; i++) {
        val += col + i;
    }
    return val - 1;
}

int main() {
    int row = 3010;
    int col = 3019;
    int val = getVal(row, col);
    uint64_t n = 20151125;
    uint64_t n1 = 252533;
    uint64_t n2 = 33554393;
    for (int i = 0; i < val; i++)
        n = (n*n1)%n2;
    printf("%lu\n", n);
    return 0;
}