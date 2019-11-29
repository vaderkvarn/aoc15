#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    char *a;
    char *b;
    int amount;
} Pair;

Pair pairs[31];
size_t num_pairs = 0;

char* persons[31];
size_t num_persons = 0;

bool samePair(Pair a, Pair b) {
    return  (strcmp(a.a, b.a) == 0 && strcmp(a.b, b.b) == 0) ||
            (strcmp(a.a, b.b) == 0 && strcmp(a.b, b.a) == 0);
}

void addPair(char *a, char *b, int amount) {
    for (int i = 0; i < num_pairs; i++) {
        Pair o = pairs[i];
        if (samePair(o, (Pair){a, b, amount})) {
                pairs[i].amount += amount;
                return;
        }
    }
    Pair p;
    p.a = malloc(16*sizeof(char));
    p.b = malloc(16*sizeof(char));
    strcpy(p.a, a);
    strcpy(p.b, b);
    p.amount = amount;
    pairs[num_pairs++] = p;
}

Pair getPair(char *a, char *b) {
    for (int i = 0; i < num_pairs; i++) {
        if (samePair(pairs[i], (Pair){a, b, 0})) {
            return pairs[i];
        }
    }
    exit(1);
}

void addPerson(char *p) {
    for (int i = 0; i < num_persons; i++) {
        if (strcmp(p, persons[i]) == 0) return;
    }
    char *person = malloc(16*sizeof(char));
    strcpy(person, p);
    persons[num_persons++] = person;
}

int getAmount(char **persons) {
    int tot = getPair(persons[0], persons[num_persons - 1]).amount;
    for (int i = 1; i < num_persons; i++) {
        tot += getPair(persons[i], persons[i-1]).amount;
    }
    return tot;
}

int largest = 0;

int rec(char **ps, int n) {
    if (n == num_persons) {
        int amount = getAmount(ps);
        free(ps);
        return  amount;
    }
    for (int i = 0; i < num_persons; i++) {
        char **ps2 = malloc((n+1)*sizeof(char*));
        bool cont = false;
        for (int j = 0; j < n; j++) {
            if (strcmp(ps[j], persons[i]) == 0) {
                cont = true;
                break;
            }
            ps2[j] = ps[j];
        }
        if (cont) {
            free(ps2);
            continue;
        }
        ps2[n] = persons[i];
        int amount = rec(ps2, n + 1);
        if (amount > largest) {
            largest = amount;
        }
    }
    return largest;
}

int main() {
    char a[16], b[16], sign[8];
    int amount;
    while (scanf("%s would %s %d happiness units by sitting next to %s.\n", a, sign, &amount, b) != EOF) {
        b[strcspn(b, ".")] = 0;
        amount = strcmp(sign, "gain") == 0 ? amount : -amount;
        addPair(a, b, amount);
        addPerson(a);
    }
    char **ps = malloc(sizeof(char*));
    printf("%d\n", rec(ps, 0));

    return 0;
}