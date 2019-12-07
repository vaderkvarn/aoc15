#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

int weights[32];
size_t num_weights = 0;

int tot = 0;

int min_num = INT_MAX;
uint64_t min_qe  = UINT64_MAX;

uint64_t get_qe(uint32_t is) {
    uint64_t p = 1;
    for (int i = 0; i < num_weights; i++, is >>= 1) {
        if (is & 1) {
            p *= weights[i];
        }
    }
    return p;
}

int sum(uint32_t is) {
    int s = 0;
    for (int i = 0; i < num_weights; i++, is >>= 1) {
        if (is & 1) s += weights[i];
    }
    return s;
}

void run(uint32_t is, int p) {
    size_t n = 0;
    int iss = is;
    for (int i = 0; i < num_weights; i++, iss >>= 1) {
        if (iss & 1) n++;
    }
    if (n > min_num) return;
    int s = sum(is);
    if (s > tot) return;
    if (s == tot) {
        if (n < min_num) {
            min_num = n;
            min_qe = get_qe(is);
        } else if (n == min_num) {
            uint64_t qe = get_qe(is);
            if (qe < min_qe) {
                min_qe = qe;
            }
        }
        return;
    }
        
    if (p == num_weights) return;
    int is0 = is, is1 = is;

    is1 |= 1 << p;
    run(is0, p+1);
    run(is1, p+1);
}
int main() {
    int weight;
    int sum = 0;
    while (scanf("%d", &weight) > 0) {
        weights[num_weights++] = weight;
        sum += weight;
    }
    tot = sum/3;
    int *is = calloc(num_weights, sizeof(int));
    run(0, 0);
    printf("%ld\n", min_qe);
    tot = sum/4;
    min_num = INT_MAX;
    min_qe = UINT64_MAX;
    is = calloc(num_weights, sizeof(int));
    run(0, 0);
    printf("%ld\n", min_qe);
    return 0;
}