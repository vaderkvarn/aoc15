#include <stdio.h>
#include <stdint.h>

#define NUM 1000000

uint64_t values[NUM];

int main() {
    uint64_t input = 34000000;
    for (int i = 1; i < NUM; i++) {
        for (int j = i; j < NUM; j += i) {
            values[j] += 10*i;
        }
    }
    for (uint64_t i = 0; i < NUM; i++) {
        if (values[i] >= input) {
            printf("%ld\n", i);
            break;
        }
    }
    return 0;
}